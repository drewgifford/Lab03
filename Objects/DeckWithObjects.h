#pragma once
#include <list>
#include "../Card.h"

class DeckWithObjects
{
    public:
        DeckWithObjects();
        virtual ~DeckWithObjects();

        Card DrawCard();
        bool ReturnCard(Card c);

        void PrintDeck();

    private:

        std::list<Card> m_deck;

};