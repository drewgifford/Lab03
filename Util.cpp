#include "Util.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>
#include <time.h>
using namespace std::this_thread;
using namespace std::chrono;

void Util::ClearScreen(){
    std::cout << "\033[2J\033[1;1H";
}

void Util::Welcome(){
    Util::ClearScreen();

    std::string welcome = R"V0G0N(.___________. __    __   __  .______     .___________. _______  _______ .__   __. 
|           ||  |  |  | |  | |   _  \    |           ||   ____||   ____||  \ |  | 
`---|  |----`|  |__|  | |  | |  |_)  |   `---|  |----`|  |__   |  |__   |   \|  | 
    |  |     |   __   | |  | |      /        |  |     |   __|  |   __|  |  . `  | 
    |  |     |  |  |  | |  | |  |\  \----.   |  |     |  |____ |  |____ |  |\   | 
    |__|     |__|  |__| |__| | _| `._____|   |__|     |_______||_______||__| \__| 
                                                                                  )V0G0N";


    std::cout << std::endl << "Welcome to....." << std::endl;

    std::istringstream iss(welcome);
    for (std::string line; std::getline(iss, line); ){

        std::cout << line << std::endl;

    }
    std::cout << std::endl << std::endl;


}


void Util::Enlighten(){

    ClearScreen();

    std::cout << "Alexa, " << std::endl;
    sleep_for(seconds(1));
    std::cout << "Play Sultans of Swing on Unix Command Line." << std::endl;
    sleep_for(seconds(3));
    std::cout << std::endl;
    std::cout << "GOOD CHOICE. NOW PLAYING SULTANS OF SWING BY THE DIRE STRAITS ON COMMAND LINE" << std::endl;
    sleep_for(seconds(3));

    std::cout << std::endl;

    std::string theSongOfGod = R"V0G0N(You get a shiver in the dark
It's a raining in the park but meantime-
South of the river you stop and you hold everything
A band is blowing Dixie, double four time
You feel alright when you hear the music ring
Well now you step inside but you don't see too many faces
Coming in out of the rain they hear the jazz go down
Competition in other places
Uh but the horns they blowin' that sound
Way on down south
Way on down south
London town
You check out guitar George, he knows-all the chords
Mind, it's strictly rhythm he doesn't want to make it cry or sing
They said an old guitar is all, he can afford
When he gets up under the lights to play his thing
And Harry doesn't mind, if he doesn't, make the scene
He's got a daytime job, he's doing alright
He can play the Honky Tonk like anything
Savin' it up, for Friday night
With the Sultans
We're the Sultans of Swing
Then a crowd a young boys they're a foolin' around in the corner
Drunk and dressed in their best brown baggies and their platform soles
They don't give a damn about any trumpet playin' band
It ain't what they call Rock and Roll
And the Sultans
Yeah, the Sultans, they play Creole
Creole
And then the man he steps right up to the microphone
And says at last just as the time bell rings
"Goodnight, now it's time to go home"
Then he makes it fast with one more thing
"We are the Sultans
We are the Sultans of Swing"
)V0G0N";

    std::istringstream iss(theSongOfGod);

    std::string notes[4] = {"♩", "♪", "♫", "♬"};

    srand(time(NULL));

    for (std::string line; std::getline(iss, line); ){

        std::string note = notes[rand() % 3];
        std::cout << note << " " << line << " " << note << std::endl;

        int millis = line.length() * 80;
        sleep_for(milliseconds(millis));

    }
    throw "your computer has died after hearing the greatest song ever produced by mankind";
    
}