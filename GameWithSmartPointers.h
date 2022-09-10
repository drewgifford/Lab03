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
        std::shared_ptr<PersonWithSmartPointers> m_p1;
        std::shared_ptr<PersonWithSmartPointers> m_p2;
        std::shared_ptr<PersonWithSmartPointers> m_p3;
        std::shared_ptr<DeckWithSmartPointers> m_deck;
        std::list<std::shared_ptr<PersonWithSmartPointers>> stackOfPeople;
        std::list<std::shared_ptr<PersonWithSmartPointers>> queueOfPeople;
        void PrintOutQueueOfPeople();
        void PrintOutStackOfPeople();

};