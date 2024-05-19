#pragma once
#include<exception>

class ClubException :public std::exception {

public:
	enum GameClubExceptionType
	{
        FileNotFound,
        WrongFormat,
        WrongValue,
        WrongName,
        WrongOrder,
        WrongId,
        WrongTime,
        WrongTableNum
	};
    const char* what() const noexcept override {
        switch (type) {
        case GameClubExceptionType::FileNotFound:
            return "There is no such file";
        case GameClubExceptionType::WrongFormat:
            return "Wrong input format";
        case GameClubExceptionType::WrongValue:
            return "Value should be > 1 for number of tables and > 0 for cost for an hour.";
        case GameClubExceptionType::WrongName:
            return "Wrong name";
        case GameClubExceptionType::WrongOrder:
            return "Wrong order of actions";    
        case GameClubExceptionType::WrongId:
            return "Wrong Id";
        case GameClubExceptionType::WrongTime:
            return "Unccorect time input.";        
        case GameClubExceptionType::WrongTableNum:
            return "There are no such table";
        default:
            return "Unknown exception";
        }
    }

private:
    GameClubExceptionType type;
public:

    ClubException(const GameClubExceptionType& type)
        : type(type)
    {
    }
};