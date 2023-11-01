#include "mbed.h"
#include <string>

// Initialise Pins D9 & D8 as Didital inputs for the two push buttons
DigitalIn pb1(D9);
DigitalIn pb2(D8);

//  Initialise Pins D1 to D7 as Digital outputs for the segments of the Displaly, not including the DP
DigitalOut segA(D1);
DigitalOut segB(D0);
DigitalOut segC(D4);
DigitalOut segD(D5);
DigitalOut segE(D6);
DigitalOut segF(D2);
DigitalOut segG(D3);

class segmentDisplay
{

    // Private array storing the state of each segement requierd to display each letter of the alphabet
    // column 0-7 as segments a-g
    int letters[26][7] = 
    {
        {1,1,1,1,1,0,1}, //a
        {0,0,1,1,1,1,1}, //b
        {0,0,0,1,1,0,1}, //c
        {0,1,1,1,1,0,1}, //d
        {1,0,0,1,1,1,1}, //e
        {1,0,0,0,1,1,1}, //f
        {1,0,1,1,1,1,0}, //g
        {0,0,1,0,1,1,1}, //h
        {1,0,0,0,1,0,0}, //i
        {1,0,1,1,0,0,0}, //j
        {1,0,1,0,1,1,1}, //k
        {0,0,0,1,1,1,0}, //l
        {1,0,1,0,1,0,1}, //m
        {0,0,1,0,1,0,1}, //n
        {0,0,1,1,1,0,1}, //o
        {1,1,0,0,1,1,1}, //p
        {1,1,1,0,0,1,1}, //q
        {0,0,0,0,1,0,1}, //r
        {1,0,1,1,0,1,0}, //s
        {0,0,0,1,1,1,1}, //t
        {0,0,1,1,1,0,0}, //u
        {0,1,0,1,0,1,0}, //v
        {0,1,0,1,0,1,1}, //w
        {0,0,1,0,1,0,0}, //x
        {0,1,1,1,0,1,1}, //y
        {1,1,0,1,1,0,0}, //z
    };

    public:

        // function to turn off all of the segments of the display
        void displayClear()
        {
            // set all of the segments pins to 0
            segA = segB = segC = segD = segF = segG = 0;
        }

        // function to display a single letter on the display
        void displayChar(char charToDisplay)
        {
            //Convets the character to display into its zero indexed position in the alphabet
            int charRow = (int)(charToDisplay % 32) - 1;

            // Set each segment to the correct state as in the letters array
            segA = (letters[charRow][0]);
            segB = (letters[charRow][1]);
            segC = (letters[charRow][2]);
            segD = (letters[charRow][3]);
            segE = (letters[charRow][4]);
            segF = (letters[charRow][5]);
            segG = (letters[charRow][6]);
        }

        // function to display a string letter by letter on the display
        void displayString(const std::string stringToDisplay)
        {
            // iterate over each char in the string
            for (char c : stringToDisplay)
            {
                displayChar(c);         // display the char
                thread_sleep_for(700);  // wait for 700ms
                displayClear();         // clear the display
            }
        }


};


// main() runs in its own thread in the OS
int main()
{   

    //  Initialise an object sg of class SegmentDisplay
    segmentDisplay sg;
    // atempt to display a string on the display
    sg.displayString("Finley");

    // when the program has completed, do nothing forever
    while (true) {
        sleep();
    }
}