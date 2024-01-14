#include "mbed.h"
#include <string>

//constructors for the semaphores
Semaphore displayFinleySemaphore(0, 1);
Semaphore displayRowlesSemaphore(0, 1);
//constructors for the mutex
Mutex displayLock;

//thread for displaying Finley signal detection
Thread displayFinleyThread;
//thread for displaying Rowles signal detection
Thread displayRowlesThread;

// Initialise Pins D9 & D8 as Didital inputs for the two push buttons
InterruptIn pb1(D9, PullUp);
InterruptIn pb2(D8, PullUp);

//  Initialise Pins D1 to D7 as Digital outputs for the segments of the Displaly, not including the DP
DigitalOut segA(D4);
DigitalOut segB(D5);
DigitalOut segC(D6);
DigitalOut segD(D1);
DigitalOut segE(D0);
DigitalOut segF(D3);
DigitalOut segG(D2);

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
            displayLock.lock();
            
            // iterate over each char in the string
            for (char c : stringToDisplay)
            {
                displayChar(c);         // display the char
                thread_sleep_for(700);  // wait for 700ms
                displayClear();         // clear the display
            }
            
            displayLock.unlock();
        }

};

//  Initialise an object sg of class SegmentDisplay
segmentDisplay sg;

// function is called when the pb1 button is pressed
void displayFinleyCallback()
{
    // allows the displayFinleyThread to run
    displayFinleySemaphore.release();
}

// function is called when the pb2 button is pressed
void displayRowlesCallback()
{
    // allows the displayRowlesThread to run
    displayRowlesSemaphore.release();
}

//function executed by the displayFinleyThread
void displayFinleyThreadFn()
{
    while(1)
    {
        //waits for the Semaphore to be acquired, then calls the displayString function 
        displayFinleySemaphore.acquire();
        sg.displayString("Finley");
    }
}

//function executed by the displayRowlesThread
void displayRowlesThreadFn()
{
    while(1)
    {
        //waits for the Semaphore to be acquired, then calls the displayString function 
        displayRowlesSemaphore.acquire();
        sg.displayString("Rowles");
    }
}

// main() runs in its own thread in the OS
int main()
{   
    //start the threads that run the display functions
    displayRowlesThread.start(displayFinleyThreadFn);
    displayFinleyThread.start(displayRowlesThreadFn);
    
    //call the appropriate fupressed when the buttons are pressed
    pb1.rise(displayFinleyCallback);
    pb2.rise(displayRowlesCallback);

    // when the program has completed, do nothing forever
    while (true)
    {
        sleep();
    }
}