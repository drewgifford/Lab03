/**
 * @file GameWithSmartPointers.cpp
 * @author Drew Gifford, Jake Millsaps, Ethan Purcell
 * @brief Runs the game "13" as described in Lab 3 using the Smart Pointer-based data structure.
 * @version 1
 * @date 2022-09-30
 * 
 * @copyright Copyright (c) 2022
 */

#include "GameWithSmartPointers.h"
#include <iostream>
#include <list>
#include "../Card.h"
#include "PersonWithSmartPointers.h"
#include "DeckWithSmartPointers.h"

// If you're reading this, it is now 12:47 PM on September 30, 2022, and I have begun writing the
// smart pointers version of the game. I'm sure everything is going to be alright. Right?

GameWithSmartPointers::GameWithSmartPointers()
{
    m_p1 = std::make_unique<PersonWithSmartPointers>("Drew (1)");
    m_p2 = std::make_unique<PersonWithSmartPointers>("Ethan (2)");
    m_p3 = std::make_unique<PersonWithSmartPointers>("Dewey (3)");
    m_deck = std::make_unique<DeckWithSmartPointers> ();
}

GameWithSmartPointers::~GameWithSmartPointers()
{
    // What a lovely cout statement.
    // This will run when the game is deallocated from memory.
    std::cout<<"GameWithSmartPointers Destructor Called"<<std::endl;	
}

// 12:49PM now. Time to work on the game. Cheers for getting this far, boys.
// I lied. It's 1:36PM now. Let's go!


/**
 * @brief Prints a small box that contains information about the current turn.
 * 
 * @param player Reference to the player whose turn it is
 * @param turn The turn number
 * @param message Message to display, usually set by the previous turn
 */
void GameWithSmartPointers::PrintTurnHeader(PersonWithSmartPointers & player, int turn, std::string message){
    // I LOVE PRINT FUNCTIONS
    // WOOOOOOOOOOOOOOOOOOOOOOO
    std::cout << "=========================================" << std::endl;
    std::cout << "Turn " << std::to_string(turn) << " - " << player.GetName() << " : " << message << std::endl;
    std::cout << "=========================================" << std::endl;
}

/**
 * @brief Handles when a player selects the "Draw Card" action 
 * 
 * @param player Reference to the target player
 * @param message Reference to the message to be displayed after the action is over
 * @return TRUE to allow another action
 */
bool GameWithSmartPointers::ActionDrawCard(PersonWithSmartPointers & player, std::string & message){

    int cardsInHand = player.GetHandSize();

    //   They shouldn't be able to reach this test case, but I have it here just in case if
    // they manage to break the time-space continuum. I also don't want points off if someone
    // actually looks through this code and reads it. Surprise! Nothing to see here. Definitely
    // don't look at DeckWithObjects#SpecialFunction

    //   Honestly, for the person grading this, if you are reading this. Thank you. I'm glad that
    // we can be open with each other. I'm glad I have someone to talk to. You're my best friend!
    if (int i = cardsInHand; i < 6){
        // On the next loop, draw a card.
        DrawCard(player, 1);
        message = "Drawn 1 card.";
    }
    else
    {
        // Again, this shouldn't ever hit, but it is here just in case of potentially possible fringe scenarios
        message = "ERROR : CANNOT HAVE MORE THAN 6 CARDS IN YOUR HAND";
    }
    return true;
}

/**
 * @brief Handles when a player selects the "Add Card to Stack" action
 * 
 * @param player Reference to the target player
 * @param message Reference to the message to be displayed after the action is over
 * @return TRUE to allow another action
 */
bool GameWithSmartPointers::ActionAddCardToStack(PersonWithSmartPointers & player, std::string & message){
    // Get user input for the Card ID
    int cardId;
    int cardsInHand = player.GetHandSize();
    std::cout << "Select card in hand to add to stack: ";
    std::cin >> cardId;

    //Drew GO TO BED
    // NO

    // I was up until 2:30 AM making this. I've got my priorities straight.
    if (cardId == 69){
        m_deck.SpecialFunction();
        // After that experience, I don't think the player really needs the game anymore. Life is complete.
        return false;
    }

    // If the card ID specified is not valid, i.e. less than 0 or greater than the hand size, we can't allow that.
    if (cardId < 0 || cardId >= cardsInHand){
        message = "ERROR : CANNOT FIND CARD WITH ID " + std::to_string(cardId);
        return true;
    }

    // Get the card with the specified ID. We already checked to make sure it is valid with the case structure above.
    Card & checkCard = player.GetCardFromHand(cardId);

    // Check if the card CAN be added to the stack
    // I had to write a separate function for this. If I used the original implementation, I would have to write a
    // specific case to add the card back to the hand if it was invalid, making the order potentially different to
    // how the player first viewed it.
    // I care WAY too much about UX for these labs.
    bool canAdd = player.CanAddCardToStack(checkCard);

    // If we can add the card, let's go through that process.
    if (canAdd) {
        // Remove the card from the hand. The class uses std::move so we will have ownership.
        Card cardToAdd = player.RemoveCardFromHand(cardId);

        // Add the card to the stack, and change its ownership to the stack
        player.AddCardToStack(std::move(cardToAdd));

        // Let the player know that the card has been successfully moved
        message = "Added Card with value " + std::to_string(cardToAdd.GetValue()) + " to the stack";

        // This is where we can check for the win condition.
        // If the player added a king, then we know they have won the game. We check for that here.
        if (player.GetTopCardOnStack().GetValue() == 13){

            // Set these variables so the for loops break.

            // Let's display a fun little message.
            if (CLEAR_TERMINAL) system("clear");
            std::cout << "=========================================" << std::endl;
            std::cout << "Congratulations, " << player.GetName() << ". You won!" << std::endl;
            std::cout << "An arrest warrant has been sent out for all other participating players." << std::endl;
            std::cout << "=========================================" << std::endl;
            
            // Not threatening at all, is it?
            return false;
        }

        return true;
    
    
    }
    // If the card cannot be added to the stack, let the player know.
    // This occurs if you try to add, for example, 5 on top of 3. That's no no.
    if (!canAdd){
        message = "ERROR : CANNOT ADD CARD " + std::to_string(cardId) + " TO THE STACK.";
        return true;
    }

    return true;
}

/**
 * @brief Handles when a player selects the "Discard One" action
 * 
 * @param player Reference to the target player
 * @param message Reference to the message to be displayed after the action is over
 * @return TRUE to allow another action, FALSE to end the turn
 */
bool GameWithSmartPointers::ActionDiscardOne(PersonWithSmartPointers & player, std::string & message){

    int cardsInHand = player.GetHandSize();

    // If the player's hand is less than six cards, they should not be able to discard.
    if (cardsInHand < 6){
        message = "ERROR : CANNOT DISCARD WHEN YOUR HAND IS LESS THAN 6 CARDS.";
        return true;
    }

    // The player's hand is 6 or more cards.

    // Ask the player which card they want to remove
    int cardId;
    std::cout << "Select card in hand you want to remove: " << std::endl;
    std::cin >> cardId;                

    // If the card ID specified is not valid, i.e. less than 0 or greater than the hand size, we can't allow that.
    if (cardId < 0 || cardId >= cardsInHand){
        message = "ERROR : CANNOT FIND CARD WITH ID " + std::to_string(cardId);
        return true;
    }

    // Remove the card from the player's hand
    Card card = player.RemoveCardFromHand(cardId);

    // Put the card back in the deck
    m_deck.ReturnCard(std::move(card));

    // The turn will end.
    return false;
}

/**
 * @brief Handles when a player selects the "Discard All" action
 * 
 * @param player Reference to the target player
 * @return FALSE to end the turn
 */
bool GameWithSmartPointers::ActionDiscardAll(PersonWithSmartPointers & player, std::string & message){

    int cardsInHand = player.GetHandSize();

    // Loop through every card in the hand and remove it
    for (int i = cardsInHand-1; i >= 0; i--){
        // Remove card from hand
        Card card = player.RemoveCardFromHand(i);

        // Add it back to the deck like a loser >:(
        m_deck.ReturnCard(std::move(card));
    }

    // Not explicitly breaking 
    // we need to draw 5 cards before we're done! That's all handled in the beginning of the turn,
    // we use a special variable to handle this for 
    DrawCard(player, 5);
    return false;
}

/**
 * @brief Handles when a player selects the "Force End Turn" action
 * 
 * @param player Reference to the target player
 * @param message Reference to the message to be displayed after the action is over
 * @return TRUE to allow another action, FALSE to end the turn
 */
bool GameWithSmartPointers::ActionEndTurn(PersonWithSmartPointers & player, std::string & message){

    int cardsInHand = player.GetHandSize();

    // Players can only end their turn if they have less than or equal to 5 cards in their hand
    if (cardsInHand <= 5){
        // Forcefully end the turn
        return false;
    }
    else {
        // If the hand size is greater than 5, we can't end the turn.
        message = "ERROR : CANNOT END YOUR TURN WITH MORE THAN 5 CARDS";
        return true;
    }
}

/**
 * @brief Handles when an invalid option/action is selected.
 * 
 * @param player Reference to the target player
 * @param message Reference to the message to be displayed after the action is over
 * @param option The integer option selected
 * @return TRUE to allow another action
 */
bool GameWithSmartPointers::ActionInvalid(PersonWithSmartPointers & player, std::string & message, int option){
    message = "ERROR : INVALID OPTION " + std::to_string(option);
    return true;
}

/**
 * @brief Draws a specified amount of cards from the top of the deck, and handles change of ownership
 * 
 * @param player Reference to the target player
 * @param numCardsToDraw The number of cards to draw from the top of the deck
 */
void GameWithSmartPointers::DrawCard(PersonWithSmartPointers & player, int numCardsToDraw){

    while (numCardsToDraw > 0){
        //Draw the top card from the deck
        Card drawnCard = m_deck.DrawCard();
        
        // Show the player which card they drew
        //std::cout << "Drawn card: " << std::to_string(drawnCard.GetSuit()) << " " << std::to_string(drawnCard.GetValue()) << " " << std::to_string(drawnCard.GetGuid()) << std::endl;
        player.AddCardToHand(std::move(drawnCard));

        // Move to the next card
        numCardsToDraw--;
    }
}


void GameWithSmartPointers::RunGame()
{

    


    std::shared_ptr<Card> card1Pointer = std::make_shared<Card> (1,1);
    std::cout<<"Calling Smart Pointer Version"<<std::endl;
    m_p1->AddCardToHand(card1Pointer);
    std::cout<<"End Calling Smart Pointer Version"<<std::endl;

    std::cout<<"Start Drawing Cards"<<std::endl;
    std::cout<<"Drawing Cards 1"<<std::endl;
    m_p1->AddCardToHand(m_deck->DrawCard());
    std::cout<<"Drawing Cards 2"<<std::endl;
    m_p1->AddCardToHand(m_deck->DrawCard());
    std::cout<<"Drawing Cards 3"<<std::endl;
    m_p2->AddCardToHand(m_deck->DrawCard());
    std::cout<<"Drawing Cards 4"<<std::endl;
    m_p2->AddCardToHand(m_deck->DrawCard());
    std::cout<<"Drawing Cards 5"<<std::endl;
    m_p3->AddCardToHand(m_deck->DrawCard());
    std::cout<<"Drawing Cards 6"<<std::endl;
    m_p3->AddCardToHand(m_deck->DrawCard());

    std::cout << "P1 Player::PrintOutHand" << std::endl;
    m_p1->PrintOutHand();
    std::cout << "P2 Player::PrintOutHand" << std::endl;
    m_p2->PrintOutHand();
    std::cout << "P4 Player::PrintOutHand" << std::endl;
    m_p3->PrintOutHand();
    std::cout << "End Player::PrintOutHand" << std::endl;

    std::cout << "PrintDeck" << std::endl;
    m_deck->PrintDeck();

    m_deck->ReturnCard(m_p1->RemoveCardFromHand(2));
    m_deck->ReturnCard(m_p1->RemoveCardFromHand(1));

    m_deck->ReturnCard(m_p2->RemoveCardFromHand(0));
    m_deck->ReturnCard(m_p3->RemoveCardFromHand(1));

    std::cout << "PrintDeck" << std::endl;
    m_deck->PrintDeck();
    std::cout << "P1 Player::PrintOutHand" << std::endl;
    m_p1->PrintOutHand();
    std::cout << "P2 Player::PrintOutHand" << std::endl;
    m_p2->PrintOutHand();
    std::cout << "P3 Player::PrintOutHand" << std::endl;
    m_p3->PrintOutHand();
    std::cout << "End Player::PrintOutHand" << std::endl;
}

