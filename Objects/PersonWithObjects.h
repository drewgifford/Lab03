#pragma once

#include "../Card.h"
#include <string>
#include <list>
#include <vector>

class PersonWithObjects
{
public:
	PersonWithObjects(std::string name) ;

	PersonWithObjects() = delete;

	PersonWithObjects(const PersonWithObjects &p) ;

	PersonWithObjects(PersonWithObjects && obj) noexcept;


	std::string GetName() const;

	virtual ~PersonWithObjects();

	bool AddCardToHand(Card  c);
	bool AddCardToHand(Card& c);
	Card RemoveCardFromHand(int i);
	void PrintOutHand();

	int GetHandSize() const;

	bool AddCardToStack(Card c);
	Card & GetTopCardOnStack();

    private: 
        std::string m_name;
        std::list< Card > m_stackOfCards;
        std::list< Card > m_listOfCards;

};