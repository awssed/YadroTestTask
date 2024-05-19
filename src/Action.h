#pragma once
#include <string>
#include "utils.h"
using namespace std;

class Action {
public:
	enum Events {
		ClientCome = 1,
		ClientSitIn = 2,
		ClientWait = 3,
		ClientGoneIn = 4,
		ClientGoneOut = 11,
		ClientSitOut = 12,
		Error = 13
	};
	Action()
	{
		this->_id = Events::ClientCome;
		this->_name = "";
		this->_time = NULL;
		this->_table = NULL;
	}
	Action(int time, Events actionId, int table, const string& name)
		: _time(time), _id(actionId), _table(table), _name(name)
	{
	}
	void SetTable(int table) { this->_table = table; }
	void SetTime(int time) { this->_time = time; }
	void SetId(Events id) { this->_id = id; }
	void SetName(std::string name) { this->_name = name; }

	int Time() const { return this->_time; }
	Events Id() const { return this->_id; }
	int Table() const { return this->_table; }
	string Name() const  { return this->_name; }

	friend std::ostream& operator << (std::ostream& os, const Action& action) {
		utils::print_time(action.Time());
		os << " " << action.Id() << " " << action.Name();
		if (action.Id()== ClientSitIn || action.Id() == ClientSitOut)
		{
			os << " " << action.Table();
		}
		return os;
	}
private:
	int _time;
	Events _id;
	int _table;
	string _name;
};