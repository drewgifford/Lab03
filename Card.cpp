#include "Card.h"
#include <iostream>
static int guid = 0;


Card::Card(int value, int suit):m_value(value), m_suit(suit)
{
    m_guid = guid;
    //std::cout<<"Card Constructor Called "<< m_value << " " << m_suit<< " " << m_guid <<std::endl;
    guid++;
}
Card::~Card() 
{
    //std::cout<<"Card Destructor Called "<< m_value << " " << m_suit<< " " << m_guid <<std::endl;	
}

Card::Card( const Card &c)
{
    //std::cout<<"    BAD!!!! Copy Constructor being called.  I shouldn't really be callled!!!"<<std::endl;
    m_value = c.m_value;
    m_suit = c.m_suit;
    m_guid = guid;
    guid++;
}

Card& Card::operator=(const Card& c)
{
    //std::cout << "    Calling Assignment Operator" << std::endl;
    Card tempOther{ c };
    *this = std::move(tempOther);
    return *this;
}

Card::Card(Card&& obj) noexcept
{
    //std::cout << "    Calling Move Constructor" << std::endl;
    *this = std::move(obj);
}

Card& Card::operator=(Card&& obj) noexcept
{
    //std::cout << "    Calling Move Assignment Operator" << std::endl;
    this->m_value = std::move(obj.m_value);
    this->m_suit = std::move(obj.m_suit);
    m_guid = std::move(obj.m_guid);
    return *this;
}



int Card::GetValue() const {return m_value;}
int Card::GetSuit() const {return m_suit;}
int Card::GetGuid() const {return m_guid;}




