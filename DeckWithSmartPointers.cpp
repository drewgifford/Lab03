#include "DeckWithSmartPointers.h"
#include "Card.h"
#include "PersonWithSmartPointers.h"
#include "DeckWithSmartPointers.h"
#include <iostream>

DeckWithSmartPointers::DeckWithSmartPointers()
{

    for(int i = 1 ; i <=13; i++)
    {
        this->m_deck.push_back(std::make_shared<Card>(i,0));
        this->m_deck.push_back(std::make_shared<Card>(i,1));
        this->m_deck.push_back(std::make_shared<Card>(i,2));
        this->m_deck.push_back(std::make_shared<Card>(i,3));
    }

}
DeckWithSmartPointers::~DeckWithSmartPointers()
{
    std::cout<<"DeckWithSmartPointers Destructor Called"<<std::endl;	
    m_deck.clear();
}

std::shared_ptr<Card> DeckWithSmartPointers::DrawCard()
{   
    std::shared_ptr<Card> retVal = nullptr;

    if(!m_deck.empty())
    {
        retVal = m_deck.front();
        m_deck.pop_front();
    }
    return retVal;
}

void DeckWithSmartPointers::ReturnCard(std::shared_ptr<Card> c)
{
    if(c != nullptr)
    {
        m_deck.push_back(c);
        return;
    }
    else
    {
        throw "Attempting to add a nullptr in DeckWithSmartPointers::ReturnCard";
    }

}

