#pragma once
#include <list>
#include <memory>

class DeckWithSmartPointers;
class PersonWithSmartPointers;

class GameWithSmartPointers
{
	public:


		GameWithSmartPointers();

		virtual ~GameWithSmartPointers();

		void RunGame();
    private:
        std::unique_ptr<PersonWithSmartPointers> m_p1;
        std::unique_ptr<PersonWithSmartPointers> m_p2;
        std::unique_ptr<PersonWithSmartPointers> m_p3;
        std::unique_ptr<DeckWithSmartPointers> m_deck;

        void PrintOutQueueOfPeople();
        void PrintOutStackOfPeople();
        void PrintTurnHeader(PersonWithSmartPointers & player, int turn, std::string message);

        bool ActionDrawCard       (PersonWithSmartPointers & player, std::string & message);
        bool ActionAddCardToStack (PersonWithSmartPointers & player, std::string & message);
        bool ActionDiscardOne     (PersonWithSmartPointers & player, std::string & message);
        bool ActionDiscardAll     (PersonWithSmartPointers & player, std::string & message);
        bool ActionEndTurn        (PersonWithSmartPointers & player, std::string & message);
        bool ActionInvalid        (PersonWithSmartPointers & player, std::string & message, int actionId);

        void DrawCard(PersonWithSmartPointers & player, int numCards);

};