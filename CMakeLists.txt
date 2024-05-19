cmake_minimum_required(VERSION 3.2)
project(TestTaskYadro)

set(CMAKE_CXX_STANDARD 20)

add_executable( TestTaskYadro
	src/main.cpp
	src/GameClub.cpp
	src/utils.cpp
	
	src/GameClub.h
	src/utils.h
	src/Action.h
	src/ClubExceptions.h
)