
#include <iostream>
#include <string>
#include <list>
#include "Util.h"
#include "Pointers/GameWithPointers.h"
#include "Objects/GameWithObjects.h"
#include "SmartPointers/GameWithSmartPointers.h"


void CallGameWithObjects()
{
	std::cout << "GameWithObjects constructed" << std::endl;
	GameWithObjects game1;
	std::cout << "Now Run Game" << std::endl;
	game1.RunGame();
}


void CallGameWithPointers()
{
	std::cout << "GameWithPointers constructed" << std::endl;
	GameWithPointers game2;
	std::cout << "Now Run Game" << std::endl;
	game2.RunGame();
}


void CallGameWithSmartPointers()
{
	std::cout << "GameWithSmartPointers constructed" << std::endl;
	GameWithSmartPointers game3;
	std::cout << "Now Run Game" << std::endl;
	game3.RunGame();
}

void CallGameWithCheating()
{
	std::cout << "GameWithSmartPointers constructed" << std::endl;
	GameWithObjects game3;
	std::cout << "Now Run Game" << std::endl;
	game3.RunCheatGame();
}


int main()
{

	Util::Welcome();

	std::cout << "Choose Data Structure to Play" << std::endl;

	std::cout << "1 - Objects" << std::endl;
	std::cout << "2 - Smart Pointers" << std::endl;

	int gameType;
	std::cin >> gameType;

	switch(gameType){
		case 1:
			CallGameWithObjects();
			break;
		case 2:
			CallGameWithSmartPointers();
			break;
		case 3:
			CallGameWithPointers();
			break;
		default:
			std::cout << "Invalid Data Structure" << std::endl;
			break;
	}
	
	std::cout << "End" << std::endl;
    return 0;
}

