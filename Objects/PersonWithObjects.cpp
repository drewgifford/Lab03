
#include "PersonWithObjects.h"
#include <iostream>
#include <iomanip>

PersonWithObjects::~PersonWithObjects( )
{
    //std::cout << "Deleting PersonWithObjects" << m_name << std::endl;
}

PersonWithObjects::PersonWithObjects(std::string name) :m_name(name)
{

}

PersonWithObjects::PersonWithObjects( const PersonWithObjects &p)
{
    std::cout<<"    BAD!!!! Copy Person Constructor being called.  I shouldn't really be callled!!!"<<std::endl;
    m_name = p.m_name;
}

PersonWithObjects::PersonWithObjects(PersonWithObjects && obj) noexcept
{
    //std::cout <<"    Calling Person Move Constructor"<<std::endl;
    this->m_name = std::move(obj.m_name);
    this->m_listOfCards = std::move(obj.m_listOfCards);
    this->m_stackOfCards = std::move(obj.m_stackOfCards);
}


std::string PersonWithObjects::GetName() const
{
    return m_name;
}

bool PersonWithObjects::AddCardToHand( Card  c)
{
    //std::cout<<"   AddCardToHandObject :"<<c.GetValue()<<" "<<c.GetSuit() << " " << c.GetGuid() << std::endl;
    m_listOfCards.push_front(std::move(c));
    return true;
}

bool PersonWithObjects::AddCardToHand(Card & c)
{
    //std::cout << "   AddCardToHandObject (by ref) :" << c.GetValue() << " " << c.GetSuit() << " " << c.GetGuid() << std::endl;
    m_listOfCards.push_front(std::move(c));
    return true;
}

Card & PersonWithObjects::GetCardFromHand(int i)
{
    auto it = m_listOfCards.begin();
    
    if(i < 0 ||  i +1 > m_listOfCards.size())
    {
        throw "Position doesn't exist in hand";
    }
    advance(it, i);
    Card & c = *it;
    return c;
}

Card PersonWithObjects::RemoveCardFromHand(int i)
{
    auto it = m_listOfCards.begin();
    
    if(i < 0 ||  i +1 > m_listOfCards.size())
    {
        throw "Position doesn't exist in hand";
    }
    advance(it, i);
    Card c = std::move(*it);
    m_listOfCards.erase(it);
    return std::move(c);
}

void PersonWithObjects::PrintOutHand()
{
    std::cout << std::setw(7) << std::left << "ID";
    std::cout << std::setw(7) << std::left << "Suit";
    std::cout << std::setw(7) << std::left << "Value";
    std::cout << std::endl;

    int id = 0;
    for (auto it = m_listOfCards.begin(); it != m_listOfCards.end(); it++)
    {
        // Print ID
        std::cout << std::setw(7) << std::left << std::to_string(id);
        // Print Suit
        std::cout << std::setw(7) << std::left << (*it).GetSuit();
        // Print Value
        std::cout << std::setw(7) << std::left << (*it).GetValue();

        std::cout << std::endl;

        id++;
    }

    if (m_stackOfCards.empty()){
        std::cout << "Stack top value: N/A" << std::endl;
    } else {
        Card & topCard = GetTopCardOnStack();
        std::cout << "Stack top value: " << std::to_string(topCard.GetValue()) << std::endl;
    }

    std::cout << std::endl;

}

bool PersonWithObjects::CanAddCardToStack(Card c){
    bool stackHasCards = !m_stackOfCards.empty();

    // Get the top card stored in the stack. If it's empty, make it 0.
    int topCardValue = 0;
    if (stackHasCards){
        topCardValue = GetTopCardOnStack().GetValue();
    }

    // 3 can only go on top of 2, J on top of 10, etc.
    bool topCardCanAccept = topCardValue == c.GetValue()-1;

    return topCardCanAccept;
}

bool PersonWithObjects::AddCardToStack(Card c)
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

Card & PersonWithObjects::GetTopCardOnStack()
{
    // if the list is empty, throw an exception
    while(!m_stackOfCards.empty())
    {
        Card & topCard = m_stackOfCards.back();
        return topCard;
    }
    throw "There are no cards in the stack";
}

int PersonWithObjects::GetHandSize() const {
    return m_listOfCards.size();
}