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
        void PrintTurnHeader(std::unique_ptr<PersonWithSmartPointers> & person, int turn, std::string message);

        bool ActionDrawCard       (std::unique_ptr<PersonWithSmartPointers> & person, std::string & message);
        bool ActionAddCardToStack (std::unique_ptr<PersonWithSmartPointers> & person, std::string & message);
        bool ActionDiscardOne     (std::unique_ptr<PersonWithSmartPointers> & person, std::string & message);
        bool ActionDiscardAll     (std::unique_ptr<PersonWithSmartPointers> & person, std::string & message);
        bool ActionEndTurn        (std::unique_ptr<PersonWithSmartPointers> & person, std::string & message);
        bool ActionInvalid        (std::unique_ptr<PersonWithSmartPointers> & person, std::string & message, int actionId);

        void DrawCard(std::unique_ptr<PersonWithSmartPointers> & person, int numCards);

        void ClearScreen();

        bool CLEAR_TERMINAL;

};