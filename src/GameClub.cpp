#include"GameClub.h"
//добавть больше regex
void GameClub::GetInfo(string filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cerr << "Can not open file"<<std::endl;
		throw new ClubException(ClubException::GameClubExceptionType::FileNotFound);
	}
	std::string line;
	std::getline(file, line);
	int tables;
	try {
		tables = std::stoi(line);
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << line << std::endl;
		throw ClubException(ClubException::GameClubExceptionType::WrongValue);
	}
	if (tables < 1)
	{
		std::cerr << line << tables << std::endl;
		throw ClubException(ClubException::GameClubExceptionType::WrongValue);
	}
	this->SetTables(tables);
	int startHours;
	int startMinutes;
	int closeHours;
	int closeMinutes;
	std::getline(file, line);
	std::regex timePatter("\\d{2}:\\d{2}\\s\\d{2}:\\d{2}");
	if (!std::regex_match(line,timePatter))
	{
		std::cerr << line.length() << std::endl;
		std::cerr << line << std::endl;
		throw ClubException(ClubException::GameClubExceptionType::WrongTime);
	}
	std::istringstream iss(line);
	char dbDot;
	iss >> startHours >> dbDot >> startMinutes;
	if (startHours >= 24 || startMinutes >= 60 || startHours<0 || startMinutes<0)
	{
		std::cerr << line << std::endl;
		throw ClubException(ClubException::GameClubExceptionType::WrongTime);
	}
	iss >> closeHours >> dbDot >> closeMinutes;
	if (closeHours >= 24 || startMinutes >= 60 || closeHours<0 || closeMinutes<0)
	{
		std::cerr << line << std::endl;
		throw ClubException(ClubException::GameClubExceptionType::WrongTime);
	}
	this->SetOpenTime(startHours, startMinutes);
	this->SetCloseTime(closeHours, closeMinutes);
	std::getline(file, line);
	int price;
	try 
	{
		price=std::stoi(line);
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << line << std::endl;
		throw ClubException(ClubException::GameClubExceptionType::WrongValue);
	}
	if (price < 1)
	{
		std::cerr << line <<  std::endl;
		throw ClubException(ClubException::GameClubExceptionType::WrongValue);
	}
	this->SetPrice(price);
	std::regex pattern("^[a-z0-9_-]+$");
	while (std::getline(file, line))
	{
		iss = std::istringstream(line);
		int prevTime=0;
		int hours;
		int minutes;
		int table;
		std::string name;
		Action::Events idType;
		Action action;
		iss >> hours >> dbDot >> minutes;
		if (hours >= 24 || minutes >= 60 || dbDot != ':')
		{
			std::cerr << line << std::endl;
			throw ClubException(ClubException::GameClubExceptionType::WrongFormat);
		}
		if (prevTime > hours * 60 + minutes)
		{
			std::cerr << line << std::endl;
			throw ClubException(ClubException::GameClubExceptionType::WrongTime);
		}
		prevTime = hours * 60 + minutes;
		try
		{
			int id;
			iss >> id;
			idType = static_cast<Action::Events>(id);
		}
		catch (std::exception e)
		{
			cerr << line << std::endl;
			throw ClubException(ClubException::GameClubExceptionType::WrongId);
		}
		iss >> name;
		if (!std::regex_match(name, pattern))
		{
			cerr << line << std::endl;
			throw ClubException(ClubException::GameClubExceptionType::WrongName);
		}
		if (idType == 2)
		{
			try
			{
				iss >> table;
			}
			catch (std::exception e)
			{
				cerr << line << std::endl;
				throw ClubException(ClubException::GameClubExceptionType::WrongTableNum);
			}
			if (table < 0 || table > this->Tables())
			{
				cerr << line << std::endl;
				throw ClubException(ClubException::GameClubExceptionType::WrongTableNum);
			}
			action.SetTable(table);
		}
		action.SetId(idType);
		action.SetTime(prevTime);
		action.SetName(name);
		this->_actions.push(action);
	}
	file.close();
}
void GameClub::HandleEvents()
{
	utils::print_time(this->OpenTime());
	std::cout << std::endl;
	std::queue<Action> actions(this->_actions);
	Action current;
	while (!actions.empty())
	{
		current = actions.front();
		switch (current.Id())
		{
		case Action::Events::ClientCome:
			std::cout << current << std::endl;
			if (current.Time() < this->OpenTime() || current.Time() > this->CloseTime())
			{
				Action* newAction = new Action(current.Time(), Action::Events::Error, 0, NOTYET);
				std::cout << *newAction << std::endl;
				delete newAction;
				break;
			}
			if (this->_clients.find(current.Name()) != this->_clients.end())
			{
				Action* newAction = new Action(current.Time(), Action::Events::Error, 0, NOTPASS);
				std::cout << *newAction << std::endl;
				delete newAction;
				break;
			}
			else
			{
				this->_clients.insert(current.Name());
			}
			break;
		case Action::Events::ClientSitIn:
			std::cout << current << std::endl;
			if (this->_clients.find(current.Name()) == this->_clients.end())
			{
				Action* newAction = new Action(current.Time(), Action::Events::Error, 0, UNKNOWN);
				std::cout << *newAction << std::endl;
				delete newAction;
				break;
			}
			if (this->_tableClient[current.Table() - 1] == "")
			{
				this->_tableClient[current.Table() - 1] = current.Name();
				this->_clients.insert(current.Name());
				this->_tableTime[current.Table() - 1] = current.Time();
			}
			else 
			{
				Action* newAction = new Action(current.Time(), Action::Events::Error, 0, BUSY);
				std::cout << *newAction << std::endl;
				delete newAction;
			}
			break;
		case Action::Events::ClientWait:
			std::cout << current << std::endl;
			this->_clients.insert(current.Name());
			if (std::find(this->_tableClient.begin(), this->_tableClient.end(), "") != this->_tableClient.end())
			{
				Action* newAction = new Action(current.Time(), Action::Events::Error, 0, NOWAIT);
				std::cout << *newAction << std::endl;
				delete newAction;
				break;
			}
			else
			{
				if (this->_queue.size() > this->Tables())
				{
					this->_clients.erase(current.Name());
					Action* newAction = new Action(current.Time(), Action::Events::ClientGoneOut, 0, current.Name());
					std::cout << *newAction << std::endl;
					delete newAction;
					break;
				}
				else 
				{
					this->_queue.push(current.Name());
				}
			}
			break;
		case Action::Events::ClientGoneIn:
			std::cout << current << std::endl;
			if (this->_clients.find(current.Name()) == this->_clients.end())
			{
				Action* newAction = new Action(current.Time(), Action::Events::Error, 0, UNKNOWN);
				std::cout << *newAction << std::endl;
				delete newAction;
				break;
			}
			int currentTable=0;
			for (int i = 0; i < this->_tableClient.size(); i++)
			{
				if (this->_tableClient[i] == current.Name())
				{
					currentTable = i + 1;
					break;
				}
			}
			if (currentTable != 0)
			{
				int time = current.Time() - this->_tableTime[currentTable-1];
				this->_report[currentTable-1].second += time;
				int revenue = std::ceil(time / 60.0) * this->Price();
				this->_report[currentTable-1].first += revenue;

				this->_clients.erase(current.Name());
				this->_tableClient[currentTable-1] = "";
				if (!this->_queue.empty())
				{
					this->_tableTime[currentTable-1] = current.Time();
					this->_tableClient[currentTable-1] = _queue.front();

					Action* newAction = new Action(current.Time(), Action::Events::ClientSitOut, currentTable , _queue.front());
					std::cout << *newAction << std::endl;
					delete newAction;

					this->_queue.pop();
				}
			}
			break;
		}
		actions.pop();
	}
	while (!this->_queue.empty())
	{
		this->_clients.erase(this->_queue.front());
		Action* newAction = new Action(this->CloseTime(), Action::Events::ClientGoneOut, 0, current.Name());
		std::cout << *newAction << std::endl;
		delete newAction;
		this->_queue.pop();
	}
	for (const std::string& client : this->_clients)
	{
		int currentTable = 0;
		for (int i = 0; i < this->_tableClient.size(); i++)
		{
			if (client == this->_tableClient[i])
				currentTable = i + 1;
		}
		if (currentTable != 0)
		{
			int time = this->CloseTime() - this->_tableTime[currentTable - 1];
			this->_report[currentTable - 1].second += time;
			int revenue = std::ceil(time / 60.0) * this->Price();
			this->_report[currentTable - 1].first += revenue;
			this->_tableClient[currentTable - 1] = "";

			Action* newAction = new Action(this->CloseTime(), Action::Events::ClientGoneOut, 0, client);
			std::cout << *newAction << std::endl;
			delete newAction;
		}
	}
	utils::print_time(this->CloseTime());
	std::cout << std::endl;
}
void GameClub::PrintReport()
{
	for (int i = 0; i < this->_report.size(); i++)
	{
		std::cout << i + 1 << ' ' << this->_report[i].first << ' ';
		utils::print_time(this->_report[i].second);
		std::cout << std::endl;
	}
}