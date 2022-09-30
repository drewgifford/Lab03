
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

    // Give them 5 cards at the start of the game
    // Only setting it to 4 because it will automatically add 1 during each turn
    int initialCards = 4;
    for(int i = 0; i < initialCards; i++){
        for(int p = 0; p < numPlayers; p++){
            Card drawnCard = m_deck.DrawCard();
            players.at(p)->AddCardToHand(std::move(drawnCard));
        }
    }

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
        std::string message = "";

        // Grab the player at this turn
        PersonWithObjects & player = * players.front();

        while (turnOver == false){
            
            system("clear");
            PrintTurnHeader(player, turn, message);

            // This will only run if the user needs to draw cards
            // It will draw as many cards that are specified in the int drawCards
            // If they need to draw 3 cards, then set drawCards = 3
            while (drawCards > 0){
                //Draw the top card from the deck
                Card drawnCard = m_deck.DrawCard();
                
                // Show the player which card they drew
                //std::cout << "Drawn card: " << std::to_string(drawnCard.GetSuit()) << " " << std::to_string(drawnCard.GetValue()) << " " << std::to_string(drawnCard.GetGuid()) << std::endl;
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


            //Present options after original draw to 6 cards:
            std::cout << "Type # of action you want to take: " << std::endl;
            std::cout << "1 - Draw 1 Card" << std::endl;
            std::cout << "2 - Add Card to Stack" << std::endl;
            std::cout << "3 - Discard 1 Card" << std::endl;
            std::cout << "4 - Discard Hand" << std::endl;
            std::cout << "5 - End Turn" << std::endl;
            
            int option;
            std::cin >> option;


            // CLEAR THE TERMINAL TO ALLOW THE PLAYER TO SEE THEIR HAND MORE CLEARLY, WITHOUT CLUTTER.
            system("clear");
            PrintTurnHeader(player, turn, " ");
            player.PrintOutHand();

            // 1 - Draw card if less than 6 cards
            
            if (option == 1){
                // Set the number of cards to draw to 1
                if (int i = player.GetHandSize(); i < 6){
                    drawCards = 1;
                    message = "Drawn 1 card.";
                    continue;
                }
                else
                {
                    message = "ERROR : CANNOT HAVE MORE THAN 6 CARDS IN YOUR HAND";
                    continue;
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


                Card & checkCard = * new Card(0, 0);
                try {
                    checkCard = player.GetCardFromHand(cardId);
                } catch (...) {
                    message = "ERROR : CANNOT FIND CARD WITH ID " + std::to_string(cardId);
                    continue;
                }

                bool canAdd = player.CanAddCardToStack(checkCard);

                if (canAdd) {
                    Card cardToAdd = player.RemoveCardFromHand(cardId);
                    player.AddCardToStack(std::move(cardToAdd));
                    message = "Added Card with value " + std::to_string(cardToAdd.GetValue()) + " to the stack";

                    // CHECK FOR THE WIN CONDITION
                    if (player.GetTopCardOnStack().GetValue() == 13){
                        // Player has won, since the top card is a King (13)
                        gameOver = true;
                        turnOver = true;

                        system("clear");
                        std::cout << "=========================================" << std::endl;
                        std::cout << "Congratulations, " << player.GetName() << ". You won!" << std::endl;
                        std::cout << "An arrest warrant has been sent out for all other participating players." << std::endl;
                        std::cout << "=========================================" << std::endl;
                        break;
                    }


                    continue;
                }
                if (!canAdd){
                    message = "ERROR : CANNOT ADD CARD " + std::to_string(cardId) + " TO THE STACK.";
                    continue;
                }
                
            }

            // 3 - Discard one card from Hand back into the Community Pile
            else if (option == 3){

                if (player.GetHandSize() != 6){
                    message = "ERROR : CANNOT DISCARD WHEN YOUR HAND IS LESS THAN 6 CARDS.";
                    continue;
                }

                int cardId;
                std::cout << "Select card in hand you want to remove: " << std::endl;
                std::cin >> cardId;                
            
                try{
                    Card returnCard = player.RemoveCardFromHand(cardId);
                    m_deck.ReturnCard(std::move(returnCard));
                    message = "Discarded card with value " + std::to_string(returnCard.GetValue());
                    continue;
                } catch (...){
                    message = "ERROR : CANNOT FIND CARD WITH ID " + std::to_string(cardId);
                    continue;
                }
                
            }
            
            // 4 - Discard entire hand
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
                    message = "ERROR : CANNOT END YOUR TURN WITH MORE THAN 5 CARDS";
                    continue;
                }
                    
            }
            message = "";
            
        }

        // Put this person at the end of the vector, and move everybody else over by one.
        players.erase(players.begin());
        players.push_back(&player);
    }

    std::cout << "Game has ended." << std::endl;

}

void GameWithObjects::PrintTurnHeader(PersonWithObjects & player, int turn, std::string message){
    std::cout << "=========================================" << std::endl;
    std::cout << "Turn " << std::to_string(turn) << " - " << player.GetName() << " : " << message << std::endl;
    std::cout << "=========================================" << std::endl;
}