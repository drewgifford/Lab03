
#include <iostream>
#include <string>
#include <list>
#include "Pointers/GameWithPointers.h"
#include "Objects/GameWithObjects.h"
#include "SmartPointers/GameWithSmartPointers.h"


void CallGameWithObjects()
{
	std::cout << "=========================================" << std::endl;
	std::cout << "GameWithObjects constructed" << std::endl;
	GameWithObjects game1;
	std::cout << "Now Run Game" << std::endl;
	game1.RunGame();
	std::cout << "=========================================" << std::endl;
}


void CallGameWithPointers()
{
	std::cout << "=========================================" << std::endl;
	std::cout << "GameWithPointers constructed" << std::endl;
	GameWithPointers game2;
	std::cout << "Now Run Game" << std::endl;
	game2.RunGame();
	std::cout << "=========================================" << std::endl;
}


void CallGameWithSmartPointers()
{
	std::cout << "=========================================" << std::endl;
	std::cout << "GameWithSmartPointers constructed" << std::endl;
	GameWithSmartPointers game3;
	std::cout << "Now Run Game" << std::endl;
	game3.RunGame();
	std::cout << "=========================================" << std::endl;
}

void CallGameWithCheating()
{
	std::cout << "=========================================" << std::endl;
	std::cout << "GameWithSmartPointers constructed" << std::endl;
	GameWithObjects game3;
	std::cout << "Now Run Game" << std::endl;
	game3.RunCheatGame();
	std::cout << "=========================================" << std::endl;
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

