#pragma once
#include "PersonWithObjects.h"
#include "DeckWithObjects.h"
#include "../Card.h"



class GameWithObjects
{
	public:
		GameWithObjects();

		virtual ~GameWithObjects();

		void RunGame();
		void RunCheatGame();
		void CheatingAdd(Card c);

    private:

		void PrintOutQueueOfPeople();
		void PrintOutStackOfPeople();
		void PrintTurnHeader(PersonWithObjects & player, int turn, std::string message);

		bool ActionDrawCard       (PersonWithObjects & player, std::string & message);
		bool ActionAddCardToStack (PersonWithObjects & player, std::string & message);
		bool ActionDiscardOne     (PersonWithObjects & player, std::string & message);
		bool ActionDiscardAll     (PersonWithObjects & player, std::string & message);
		bool ActionEndTurn        (PersonWithObjects & player, std::string & message);
		bool ActionInvalid        (PersonWithObjects & player, std::string & message, int actionId);

		void DrawCard(PersonWithObjects & player, int numCards);

        PersonWithObjects m_p1;
        PersonWithObjects m_p2;
        PersonWithObjects m_p3;
        DeckWithObjects m_deck;
		bool CLEAR_TERMINAL;
};