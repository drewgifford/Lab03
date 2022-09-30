
#include "GameWithObjects.h"
#include <iostream>
#include <vector>

GameWithObjects::GameWithObjects(): m_p1("Huey 1"), m_p2("Louie 2"), m_p3("Dewey 3"), m_deck()
{

}

GameWithObjects::~GameWithObjects()
{
    std::cout<<"GameWithObjects Destructor Called"<<std::endl;	
}

void GameWithObjects::CheatingAdd(Card c)
{
    // Blah blah
    std::cout<<"I am cheating"<<std::endl;	
}



void GameWithObjects::RunCheatGame()
{
    // pointless comment

    Card card1Object = Card(11,1);

    CheatingAdd(card1Object);
    std::cout<<"End Calling AddCardToHandObject"<<std::endl;
    std::cout<<std::endl<<std::endl;
}

void GameWithObjects::RunGame()
{
    // Create a vector of players we can easily modify, make sure we don't duplicate any of the objects with references
    std::vector<PersonWithObjects *> players;
    players.push_back(&m_p1);
    players.push_back(&m_p2);
    players.push_back(&m_p3);

    int numPlayers = players.size();

    // Game over condition we can modify
    bool gameOver = false;

    // Loop through each turn
    int turn = 0;
    while (gameOver == false){

        // Increment the turn so we can reference it
        turn++;

        bool turnOver = false;
        bool breakAfterDrawing = false;
        int drawCards = 1;

        // This will only run on each player's first turn
        if (turn <= numPlayers){
            // Each player needs to draw 5 cards on their first turn
            drawCards = 5;
        }

        // Grab the player at this turn
        PersonWithObjects & player = * players.front();

        system("clear");

        std::cout << "Turn " << std::to_string(turn) << " - " << player.GetName() << std::endl;

        while (turnOver == false){
            

            // This will only run if the user needs to draw cards
            // It will draw as many cards that are specified in the int drawCards
            // If they need to draw 3 cards, then set drawCards = 3
            while (drawCards > 0){
                //Draw the top card from the deck
                Card drawnCard = m_deck.DrawCard();
                
                // Show the player which card they drew
                std::cout << "Drawn card: " << std::to_string(drawnCard.GetSuit()) << " " << std::to_string(drawnCard.GetValue()) << " " << std::to_string(drawnCard.GetGuid()) << std::endl;
                player.AddCardToHand(std::move(drawnCard));

                // Move to the next card
                drawCards--;
            }

            // Print out hand with added cards
            player.PrintOutHand();

            // Some functions may require we draw cards at the end of a turn, this will handle that without modifying the player class
            if (breakAfterDrawing) {
                turnOver = true;
                break;
            }

            // Show which card is on top of their stack
            try {
                Card & topCard = player.GetTopCardOnStack();
                std::cout << "Stack top value: " << std::to_string(topCard.GetValue()) << std::endl;
            } catch (...){
                std::cout << "No cards in stack" << std::endl;
            }


            //Present options after original draw to 6 cards:
            std::cout << "Type # of action you want to take: " << std::endl;
            std::cout << "1 - Draw 1 Card" << std::endl;
            std::cout << "2 - Add Card to Stack" << std::endl;
            std::cout << "3 - Discard 1 Card" << std::endl;
            std::cout << "4 - Discard Hand" << std::endl;
            std::cout << "5 - End Turn" << std::endl;
            
            int option;
            std::cin >> option;

            // 1 - Draw card if less than 6 cards
            
            if (option == 1){
                // Set the number of cards to draw to 1
                if (int i = player.GetHandSize(); i < 6){
                    drawCards = 1;
                    continue;
                }
                else
                {
                    std::cout << "Cannot have more than 6 cards" << std::endl;
                }

            }
            
            // 2 - Add card to stack
            else if (option == 2){
                
                // Get user input for the Card ID
                int cardId;
                std::cout << "Select card in hand to add to stack: ";
                std::cin >> cardId;
                //Drew GO TO BED
                if (cardId == 69){
                    m_deck.SpecialFunction();
                    return;
                }


                if (cardId >= player.GetHandSize()) {
                    std::cout << "ERROR : Cannot find card with ID " << std::to_string(cardId) << std::endl;
                    continue;
                }

                Card addCard = player.RemoveCardFromHand(cardId);

                bool canAdd = player.AddCardToStack(std::move(addCard));
                if (!canAdd){
                    std::cout << "Cannot add card to stack." << std::endl;
                }
                
            }

            // 3 - Discard one card from Hand back into the Community Pile
            else if (option == 3){

                int cardId;
                std::cout << "Select card in hand you want to remove: " << std::endl;
                std::cin >> cardId;                
            
                try{
                    Card returnCard = player.RemoveCardFromHand(cardId);
                    m_deck.ReturnCard(std::move(returnCard));
                } catch (...){
                    std::cout << "ERROR : Cannot find card with ID " << std::to_string(cardId) << std::endl;
                    continue;
                }
                
            }
            
            // 4 - Discard entire 
            else if (option == 4){
                
                // Loop through every card in the hand and remove 
                for (int i = 0; i < player.GetHandSize(); i++){
                    Card card = player.RemoveCardFromHand(i);

                    // Add it back to the deck like a loser >:(
                    m_deck.ReturnCard(std::move(card));
                }

                // Not explicitly breaking 
                // we need to draw 5 cards before we're done! That's all handled in the beginning of the turn,
                // we use a special variable to handle this for 
                drawCards = 5;
                breakAfterDrawing = true;
                continue;
                                      
            }

            // 5 - End Turn
            else {
                //Add check for 5 cards
                int handSize = player.GetHandSize();

                // Players can only end their turn if they have less than or equal to 5 cards in their hand
                if (handSize <= 5){
                    turnOver = true;
                    break;
                }

                else {
                    std::cout << "Cannot end turn with over 5 cards" << std::endl;
                    continue;
                }
                    
            }
            
        }

        // Put this person at the end of the vector, and move everybody else over by one.
        players.erase(players.begin());
        players.push_back(&player);
    }


    Card card1Object = Card(11,1);
    std::cout<<"Calling AddCardToHandObject"<<std::endl;
    m_p1.AddCardToHand(std::move(card1Object));
    std::cout<<"End Calling AddCardToHandObject"<<std::endl;
    std::cout<<std::endl<<std::endl;

    std::cout<<"Start Drawing Cards"<<std::endl;
    std::cout<<"Drawing Cards 1"<<std::endl;
    m_p1.AddCardToHand(std::move(m_deck.DrawCard()));
    std::cout<<"Drawing Cards 2"<<std::endl;
    m_p1.AddCardToHand(std::move(m_deck.DrawCard()));
    std::cout<<"Drawing Cards 3"<<std::endl;
    m_p2.AddCardToHand(std::move(m_deck.DrawCard()));
    std::cout<<"Drawing Cards 4"<<std::endl;
    m_p2.AddCardToHand(std::move(m_deck.DrawCard()));
    std::cout<<"Drawing Cards 5"<<std::endl;
    m_p3.AddCardToHand(std::move(m_deck.DrawCard()));
    std::cout<<"Drawing Cards 6"<<std::endl;
    m_p3.AddCardToHand(std::move(m_deck.DrawCard()));

    std::cout << "P1 Player::PrintOutHand" << std::endl;
    m_p1.PrintOutHand();
    std::cout << "P2 Player::PrintOutHand" << std::endl;
    m_p2.PrintOutHand();
    std::cout << "P4 Player::PrintOutHand" << std::endl;
    m_p3.PrintOutHand();
    std::cout << "End Player::PrintOutHand" << std::endl;

    std::cout << "PrintDeck" << std::endl;
    m_deck.PrintDeck();

    m_deck.ReturnCard(std::move(m_p1.RemoveCardFromHand(2)));
    m_deck.ReturnCard(std::move(m_p1.RemoveCardFromHand(1)));

    m_deck.ReturnCard(std::move(m_p2.RemoveCardFromHand(0)));
    m_deck.ReturnCard(std::move(m_p3.RemoveCardFromHand(1)));

    std::cout << "PrintDeck" << std::endl;
    m_deck.PrintDeck();
    std::cout << "P1 Player::PrintOutHand" << std::endl;
    m_p1.PrintOutHand();
    std::cout << "P2 Player::PrintOutHand" << std::endl;
    m_p2.PrintOutHand();
    std::cout << "P3 Player::PrintOutHand" << std::endl;
    m_p3.PrintOutHand();
    std::cout << "End Player::PrintOutHand" << std::endl;

}

