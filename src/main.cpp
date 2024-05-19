#include <iostream>
#include "GameClub.h"
#include"ClubExceptions.h"

int main(int argc, char* argv[])
{
	try
	{
		GameClub gameClub;
		gameClub.GetInfo(argv[1]);
		gameClub.HandleEvents();
		gameClub.PrintReport();
	}
	catch (const ClubException& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	catch (const std::exception e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}