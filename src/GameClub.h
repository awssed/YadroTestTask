#pragma once
#include<iostream>
#include<sstream>
#include<vector>
#include<set>
#include<queue>
#include<map>
#include<math.h>
#include<fstream>
#include<regex>
#include"ClubExceptions.h"
#include"Action.h"
#define NOTYET "NotOpenYet"
#define NOTPASS "YouShallNotPass"
#define UNKNOWN "ClientUnknown"
#define BUSY "PlaceIsBusy"
#define NOWAIT "ICanWaitNoLonger!" 

class GameClub {
private:
	int _tables;
	int _price;
	int _open;
	int _close;
	std::queue<Action> _actions;
	std::set<std::string> _clients;
	std::vector<std::string> _tableClient;
	std::map<int, int> _tableTime;
	std::queue<std::string> _queue;
	std::vector<std::pair<int, int>> _report;

public:

	GameClub() 
	{
		this->_open = 0;
		this->_close = 0;
		this->_price = 0;
		this->_tables = 0;
	};


	GameClub(int _tables, int _price, int _open, int _close)
		: _tables(_tables), _price(_price), _open(_open), _close(_close)
	{
	}
	int Tables() const { return this->_tables; }
	int Price() const { return this->_price; }
	int OpenTime() const { return this->_open; }
	int CloseTime() const { return this->_close; }


	void SetTables(int tables)
	{
		if (this->_tableClient.size() > 0)
		{
			this->_tableClient.clear();
		}
		this->_tableClient.resize(tables, "");
		if (this->_tableTime.size() > 0) 
		{
			_tableTime.clear();
		}
		this->_tableTime = std::map<int, int>();
		for (int i = 0; i < tables; i++) {
			this->_tableTime[i] = this->OpenTime();
			this->_report.push_back(std::make_pair(0, 0));
		}
		this->_tables = tables;
	}
	void SetOpenTime(int hours, int minutes)
	{
		this->_open = hours*60+minutes;
	}
	void SetCloseTime(int hours, int minutes)
	{
		this->_close = hours * 60 + minutes;
	}
	void SetPrice(int price)
	{
		this->_price = price;
	}
	void GetInfo(std::string filename);
	void HandleEvents();
	void PrintReport();
};