/**
 * @file GameWithObjects.cpp
 * @author Drew Gifford, Jake Millsaps, Ethan Purcell
 * @brief Runs the game "13" as described in Lab 3 using the Object data structure.
 * @version 1
 * @date 2022-09-30
 * 
 * @copyright Copyright (c) 2022
 */

#include "GameWithObjects.h"
#include "../Util.h"
#include <iostream>
#include <vector>

GameWithObjects::GameWithObjects(): m_p1("Drew (1)"), m_p2("Ethan (2)"), m_p3("J.T. (3)"), m_deck(), CLEAR_TERMINAL(true)
{
    // I hope you enjoy the amount of comments that are in this file. I enjoy writing them,
    // even if they are boring and pointless I feel like I'm telling a story.
    // Also, adds some personality to the code, I hope.
    
    // I'll just make myself feel better by convincing myself this is how I get paid six figures.
}

GameWithObjects::~GameWithObjects()
{
    // HULK SMASHH!!!
    // Sorry... this, uh.. calls when the game is deleted.
    std::cout<<"GameWithObjects Destructor Called"<<std::endl;	
}

void GameWithObjects::CheatingAdd(Card c)
{
    // Blah blah
    // ^ I didn't write that one, actually
    std::cout<<"I am cheating"<<std::endl;	
}

void GameWithObjects::RunCheatGame()
{
    // pointless comment
    // ^ That one either

    // I'm really not sure what this is supposed to do, it's not defined in the lab.
    Card card1Object = Card(11,1);
    
    // It's cheating? I think? Cheating is bad. Unless you are a multibillion dollar company, then cheating is just corporate policy.
    // Am I allowed to say that?
    CheatingAdd(card1Object);
    std::cout<<"End Calling AddCardToHandObject"<<std::endl;
    std::cout<<std::endl<<std::endl;
}

/**
 * @brief Prints a small box that contains information about the current turn.
 * 
 * @param player Reference to the player whose turn it is
 * @param turn The turn number
 * @param message Message to display, usually set by the previous turn
 */
void GameWithObjects::PrintTurnHeader(PersonWithObjects & player, int turn, std::string message){
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
bool GameWithObjects::ActionDrawCard(PersonWithObjects & player, std::string & message){

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
bool GameWithObjects::ActionAddCardToStack(PersonWithObjects & player, std::string & message){
    // Get user input for the Card ID
    int cardId;
    int cardsInHand = player.GetHandSize();
    std::cout << "Select card in hand to add to stack: ";
    std::cin >> cardId;

    //Drew GO TO BED
    // NO

    // I was up until 2:30 AM making this. I've got my priorities straight.
    if (cardId == 69){
        Util::Enlighten();
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
            if (CLEAR_TERMINAL) Util::ClearScreen();
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
bool GameWithObjects::ActionDiscardOne(PersonWithObjects & player, std::string & message){

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
bool GameWithObjects::ActionDiscardAll(PersonWithObjects & player, std::string & message){

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
bool GameWithObjects::ActionEndTurn(PersonWithObjects & player, std::string & message){

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
bool GameWithObjects::ActionInvalid(PersonWithObjects & player, std::string & message, int option){
    message = "ERROR : INVALID OPTION " + std::to_string(option);
    return true;
}

/**
 * @brief Draws a specified amount of cards from the top of the deck, and handles change of ownership
 * 
 * @param player Reference to the target player
 * @param numCardsToDraw The number of cards to draw from the top of the deck
 */
void GameWithObjects::DrawCard(PersonWithObjects & player, int numCardsToDraw){

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

/**
 * @brief Runs the game. This function will break once the game ends.
 */
void GameWithObjects::RunGame()
{
    // It's go time!

    // Set this to true to clear the terminal whenever given the opportunity to keep the screen clear.
    // It's a nice QoL feature, but set to false if you're debugging.

    // Create a vector of players we can easily modify, make sure we don't duplicate any of the objects with references
    std::vector<PersonWithObjects *> players;
    players.push_back(&m_p1); // Player 1
    players.push_back(&m_p2); // Player 2
    players.push_back(&m_p3); // Player 3
    // These all seem like nice guys, I'd be friends.
    // If this were production code, the players would need to be added via input, not explicitly defined.


    // Get the number of players for calculations
    int numPlayers = players.size();

    // Give them 5 cards at the start of the game
    int initialCards = 5;


    // Loop through the amount of cards we need to give the player.
    // I chose to start with the card index, because at the point of writing it, the deck is unshuffled. This is so the
    // values of the cards each player has varies.
    for(int i = 0; i < initialCards; i++){

        // Loop through each player and give them a card.
        for(int p = 0; p < numPlayers; p++){
            DrawCard(*players.at(p), 1);
        }
    }

    // Game over condition we can modify
    bool gameOver = false;

    // Loop through each turn
    int turn = 0;

    // GAME LOOP
    // This will loop once for every player's turn.
    // The turn counter is tracked with the integer turn.
    // The current player is equal to the front of the vector, and
    // can be accessed via PersonWithObjects & player = * players.front().
    while (gameOver == false){
    
        // Increment the turn so we can reference it
        turn++;

        // Set some default variables for this turn.
        bool turnOver = false; // Checks whether the turn is over, if true, it will break the action loop.
        bool breakAfterDrawing = false; // Tells the game to break the action loop after drawing cards.
        int drawCards = 1; // The amount of cards to draw on the next action.
        std::string message = ""; // The message to display before the next action.
        PersonWithObjects & player = * players.front(); // The current player


        // At the beginning of each turn, draw a card.
        DrawCard(player, 1);

        // ACTION LOOP
        // This will loop once for every action a player takes during their turn.
        // You can set the variables defined above during an action, and they will be stored for
        // use in the next action. We use this for drawing cards and displaying messages, mainly.
        while (turnOver == false){
            
            // Clear the terminal and print the turn header defined at the bottom of this file.
            // Keeps everything looking nice and pretty.
            if (CLEAR_TERMINAL) Util::ClearScreen();
            PrintTurnHeader(player, turn, message);

            // Storing the number of cards in hand, for use in calculations.
            int cardsInHand = player.GetHandSize();

            // Print out hand with added cards
            player.PrintOutHand();

            // Some functions may require we draw cards at the end of a turn, this will handle that without modifying the player class
            if (breakAfterDrawing) {
                turnOver = true;
                break;
            }


            //Present options after original draw to 6 cards:
            std::cout << "Type # of action you want to take: " << std::endl;

            //   Not all options are valid at any point in a turn, we will indicate this to the
            // player by only showing the options they may choose.
            //   As to not have any gaps in the option IDs, (i.e., 1 - is followed by 3 - which is strange), we
            // dynamically set each option ID

            // List of option GUI IDs
            // 0: Add card to stack
            // 1: Draw 1 Card
            // 2: Discard 1
            // 3: Discard Hand
            // 4: Force End Turn
            int options[5] = {0, 0, 0, 0, 0};

            int currOption = 1;

            // Option to select a card from your hand to add to the stack
            // Always available
            std::cout << currOption << " - Add Card to Stack" << std::endl;
            options[0] = currOption++;

            // Only one of these will be active. You are not allowed to have both options at the same time.
            if (cardsInHand == 6){
        
                // Option to discard one card from your hand and end your turn.
                // This is only allowed if you have too many cards (>=6)
                std::cout << currOption << " - Discard 1 Card (Ends turn)" << std::endl;
                options[2] = currOption++;

            } else {

                // Option to draw one card and continue your turn.
                // This is only allowed if you have less than the maximum amount of cards (<6)
                std::cout << currOption << " - Draw 1 Card" << std::endl;
                options[1] = currOption++;

            }

            // Option to discard your entire hand in favor of a new one and ends your turn
            // Always available
            std::cout << currOption << " - Discard Hand (Ends turn)" << std::endl;
            options[3] = currOption++;

            // Option to end your turn immediately without discarding
            // Always available
            std::cout << currOption << " - Give Up (Ends Turn)" << std::endl;
            options[4] = currOption++;
            
            // Get user input for the option
            int option;
            std::cin >> option;

            // If the option is 0, send the invalid action message.
            // We have this before all of our other cases because the default value for all actions is 0,
            // even if they are not valid currently.
            if (option <= 0) {
                turnOver = !ActionInvalid(player, message, option);
                continue;
            }


            // Clear the terminal to allow the player to read their hand, without the options in the way.
            // This is somewhat unnecessary but I found it easier to test and play with.
            // I spend way too much time making things look pretty anyways...
            if (CLEAR_TERMINAL) Util::ClearScreen();
            PrintTurnHeader(player, turn, " ");
            player.PrintOutHand();

            // If the option is 0, send the invalid action message.
            // We have this before all of our other cases because the default value for all actions is 0,
            // even if they are not valid currently.
                 if (option == 0 || option >= currOption) turnOver = !ActionInvalid(player, message, option);
                
            // Run all of our other actions if they are valid
            else if (option == options[0]) turnOver = !ActionAddCardToStack(player, message);
            else if (option == options[1]) turnOver = !ActionDrawCard(player, message);
            else if (option == options[2]) turnOver = !ActionDiscardOne(player, message);
            else if (option == options[3]) turnOver = !ActionDiscardAll(player, message);
            else if (option == options[4]) turnOver = !ActionEndTurn(player, message);

            // Unsure how this would ever hit, but it's here just in case.
            else turnOver = !ActionInvalid(player, message, option);
        }

        // Put this person at the end of the vector, and move everybody else over by one.
        // (Drew) (Ethan) (J.T.) becomes...
        // (Ethan) <- (J.T.) <- (Drew) <-
        players.erase(players.begin()); // Remove first element
        players.push_back(&player); // Add to end of list
    }

    // Finally, the nightmare is over.
    std::cout << "Game has ended." << std::endl;

}


// If you're reading this, it is 12:46 PM on September 30, 2022. I have not started writing the Smart Pointers game.
// Please wish us luck.

// Well, I felt the need to separate out each action into their own class. It's 1:31PM now and I still haven't started the
// Smart Pointers game. However, I should have made it easier for me and my lab partners to go in and change all of the
// code for it. So that's nice!