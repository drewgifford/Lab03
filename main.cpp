
#include <iostream>
#include <string>
#include <list>
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
	std::cout << "Start" << std::endl;
	//CallGameWithCheating();
	CallGameWithObjects();
	//CallGameWithPointers();
	//CallGameWithSmartPointers();
	
	std::cout << "End" << std::endl;
    return 0;
}

