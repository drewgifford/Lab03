#pragma once

#include "../Card.h"
#include <string>
#include <list>
#include <memory>

class PersonWithSmartPointers
{
public:
	explicit PersonWithSmartPointers();
	PersonWithSmartPointers(std::string name);

	PersonWithSmartPointers( const PersonWithSmartPointers &p) = delete;
	PersonWithSmartPointers(PersonWithSmartPointers && obj) = delete;
	virtual ~PersonWithSmartPointers();


	std::string GetName() const;

	//virtual ~PersonWithSmartPointers();

	bool AddCardToHand(std::shared_ptr<Card> c);
	std::shared_ptr<Card> RemoveCardFromHand(int i);
	std::shared_ptr<Card> GetCardFromHand(int i);

	void PrintOutHand();
	void PrintOutStack();

	int GetHandSize() const;

	bool AddCardToStack(std::shared_ptr<Card> c);
	bool CanAddCardToStack(std::shared_ptr<Card> c);
	std::shared_ptr<Card> GetTopCardOnStack();

	

    private: 
        std::string m_name;

        std::list<std::shared_ptr<Card>> m_stackOfCards;
        std::list<std::shared_ptr<Card>> m_listOfCards;

};