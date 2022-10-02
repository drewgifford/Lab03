// tests.cpp
#include "Card.h"

#include "Objects/GameWithObjects.h"
#include "SmartPointers/GameWithSmartPointers.h"

#include "Objects/PersonWithObjects.h"
#include "SmartPointers/PersonWithSmartPointers.h"

#include "Objects/DeckWithObjects.h"
#include "SmartPointers/DeckWithSmartPointers.h"


#include <queue>
#include <stack>

#include <gtest/gtest.h>
				
		
		TEST(PersonWithObjects,TestAddCard)
		{
			PersonWithObjects p("Test");
			Card c = Card(1,2);
			
			bool success = p.AddCardToHand(std::move(c));

			EXPECT_TRUE(success);

		}
 		TEST(PersonWithObjects,TestCanAddCardToStack)
		{
			PersonWithObjects p("Test");
			Card c = Card(1,2);
			bool success = p.CanAddCardToStack(std::move(c));

			EXPECT_TRUE(success);
		}
		TEST(PersonWithObjects,TestAddCardToStack)
		{
			PersonWithObjects p("Test");
			Card c = Card(1,2);
			bool success = p.AddCardToStack(std::move(c));

			EXPECT_TRUE(success);
		}
		
		//GameWithObjects - DeckWithObjects Tests:

		TEST(DeckWithObjects,TestReturnCard)
		{
			DeckWithObjects p;
			Card c = Card(1,2);
			
			bool success = p.ReturnCard(std::move(c));

			EXPECT_TRUE(success);

		}
 		TEST(DeckWithObjects,TestReturnCard2)
		{
			DeckWithObjects p;
			Card c = Card(4,1);
			
			bool success = p.ReturnCard(std::move(c));

			EXPECT_TRUE(success);

		}
		TEST(DeckWithObjects,TestReturnCard3)
		{
			DeckWithObjects p;
			Card c = Card(8,3);
			
			bool success = p.ReturnCard(std::move(c));

			EXPECT_TRUE(success);
		}

		//GameWithObjects - GameWithObjects Tests:
		
		TEST(GameWithObjects,TestActionDrawCard)
		{
			
			GameWithObjects game;
			std::string message;
			bool success = game.ActionDrawCard(game.m_p1,message);
			EXPECT_TRUE(success);
			
		}
 		TEST(GameWithObjects,TestPlayerQueue)
		{
			GameWithObjects game;
			std::string message;
			
			std::queue<PersonWithObjects> outputQueue = game.GetQueueOfPeople();
			std::queue<PersonWithObjects> playerQueue;

			playerQueue.push(std::move(game.m_p3));
			playerQueue.push(std::move(game.m_p2));
			playerQueue.push(std::move(game.m_p1));

			EXPECT_EQ(playerQueue.size(), outputQueue.size());
		}
		TEST(GameWithObjects,TestPlayerStack)
		{
			GameWithObjects game;
			std::string message;
			
			std::stack<PersonWithObjects> outputQueue = game.GetStackOfPeople();
			std::stack<PersonWithObjects> playerQueue;

			playerQueue.push(std::move(game.m_p3));
			playerQueue.push(std::move(game.m_p2));
			playerQueue.push(std::move(game.m_p1));

			EXPECT_EQ(playerQueue.size(), outputQueue.size());
		}





		//SMARTPOINTERS UNIT CASES
					
		TEST(PersonWithSmartPointers,TestAddCard)
		{

			PersonWithSmartPointers p("Drew");
			std::shared_ptr<Card> c = std::make_shared<Card>(1, 2);
			
			bool success = p.AddCardToHand(std::move(c));

			EXPECT_TRUE(success);

		}
 		TEST(PersonWithSmartPointers,TestCanAddCardToStack)
		{
			PersonWithSmartPointers p("Test");

			std::shared_ptr<Card> c = std::make_shared<Card>(1, 2);

			bool success = p.CanAddCardToStack(std::move(c));

			EXPECT_TRUE(success);
		}
		TEST(PersonWithSmartPointers,TestAddCardToStack)
		{
			PersonWithSmartPointers p("Test");

			std::shared_ptr<Card> c = std::make_shared<Card>(1, 2);

			bool success = p.AddCardToStack(std::move(c));

			EXPECT_TRUE(success);
		}
		
		//GameWithSmartPointers - DeckWithSmartPointers Tests:

		TEST(DeckWithSmartPointers,TestReturnCard)
		{
			DeckWithSmartPointers p;

			std::shared_ptr<Card> c = std::make_shared<Card>(1, 2);
			
			bool success = p.ReturnCard(std::move(c));

			EXPECT_TRUE(success);

		}
 		TEST(DeckWithSmartPointers,TestReturnCard2)
		{
			DeckWithSmartPointers p;

			std::shared_ptr<Card> c = std::make_shared<Card>(4, 1);
			
			bool success = p.ReturnCard(std::move(c));

			EXPECT_TRUE(success);

		}
		TEST(DeckWithSmartPointers,TestReturnCard3)
		{
			DeckWithSmartPointers p;

			std::shared_ptr<Card> c = std::make_shared<Card>(8, 3);
			
			bool success = p.ReturnCard(std::move(c));

			EXPECT_TRUE(success);
		}

		//GameWithSmartPointers - GameWithSmartPointers Tests:
		
		TEST(GameWithSmartPointers,TestActionDrawCard)
		{
			
			GameWithSmartPointers game;
			std::string message;
			bool success = game.ActionDrawCard(game.m_p1,message);
			EXPECT_TRUE(success);
			
		}
 		TEST(GameWithSmartPointers,TestPlayerQueue)
		{
			GameWithSmartPointers game;
			std::string message;
			
			std::queue<std::unique_ptr<PersonWithSmartPointers>> outputQueue = game.GetQueueOfPeople();
			std::queue<std::unique_ptr<PersonWithSmartPointers>> playerQueue;

			playerQueue.push(std::move(game.m_p3));
			playerQueue.push(std::move(game.m_p2));
			playerQueue.push(std::move(game.m_p1));

			EXPECT_EQ(playerQueue.size(), outputQueue.size());
		}
		TEST(GameWithSmartPointers,TestPlayerStack)
		{
			GameWithSmartPointers game;
			std::string message;
			
			std::stack<std::unique_ptr<PersonWithSmartPointers>> outputQueue = game.GetStackOfPeople();
			std::stack<std::unique_ptr<PersonWithSmartPointers>> playerQueue;

			playerQueue.push(std::move(game.m_p3));
			playerQueue.push(std::move(game.m_p2));
			playerQueue.push(std::move(game.m_p1));

			EXPECT_EQ(playerQueue.size(), outputQueue.size());
		}



		//Extra Credit Tests for Card.cpp?



		
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
