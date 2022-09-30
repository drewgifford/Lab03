
#include "PersonWithSmartPointers.h"
#include <iostream>

PersonWithSmartPointers::PersonWithSmartPointers(std::string name) :m_name(name)
{

}




std::string PersonWithSmartPointers::GetName() const
{
    return m_name;
}

PersonWithSmartPointers::~PersonWithSmartPointers()
{
    std::cout << "Deleting PersonWithSmartPointers" << m_name << std::endl;
    
}

bool PersonWithSmartPointers::AddCardToHand(std::shared_ptr<Card> c)  
{
    std::cout<<"   AddCardToHandPointer :"<<c->GetValue()<<" "<<c->GetSuit()<<" "<<c->GetGuid()<<std::endl;
    m_listOfCards.push_front(c);
    return true;
}



std::shared_ptr<Card> PersonWithSmartPointers::RemoveCardFromHand(int i)  
{
    auto it = m_listOfCards.begin();
    if(i < 0 ||  i +1 > m_listOfCards.size())
    {
        throw "Position doesn't exist in hand";
    }
    advance(it, i);
    std::shared_ptr<Card> retVal = *it;
    m_listOfCards.erase(it);
    return retVal;
}


void PersonWithSmartPointers::PrintOutHand()  
{
    
    for(auto it = m_listOfCards.begin(); it != m_listOfCards.end(); it++)
    {
        std::cout<<"   AddCardToHandPointer :"<<(*it)->GetValue()<<" "<<(*it)->GetSuit()<<" "<<(*it)->GetGuid()<<std::endl;
    }
}


bool PersonWithSmartPointers::CanAddCardToStack(std::shared_ptr<Card> c){
    bool stackHasCards = !m_stackOfCards.empty();

    // Get the top card stored in the stack. If it's empty, make it 0.
    int topCardValue = 0;
    if (stackHasCards){
        topCardValue = GetTopCardOnStack()->GetValue();
    }

    // 3 can only go on top of 2, J on top of 10, etc.
    bool topCardCanAccept = topCardValue == c->GetValue()-1;

    return topCardCanAccept;
}

bool PersonWithSmartPointers::AddCardToStack(std::shared_ptr<Card> c)
{

    // 3 can only go on top of 2, J on top of 10, etc.
    bool topCardCanAccept = CanAddCardToStack(c);

    if (!topCardCanAccept) return false;
    else {
        // Adds a card to the players stack from their hand
        //std::cout<<"   AddCardToStackObject :"<<c.GetValue()<<" "<<c.GetSuit() << " " << c.GetGuid() << std::endl;
        m_stackOfCards.push_back(std::move(c));
        return true;
    }
}

std::shared_ptr<Card> PersonWithSmartPointers::GetTopCardOnStack()
{
    // if the list is empty, throw an exception
    while(!m_stackOfCards.empty())
    {
        std::shared_ptr<Card> topCard = m_stackOfCards.back();
        return topCard;
    }
    throw "There are no cards in the stack";
}