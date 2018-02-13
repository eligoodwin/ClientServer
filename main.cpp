#include <iostream>
#include "WindowManager.h"
#include <thread>
#include "ClientManager.h"

using namespace std;

int main(int argc, char* argv[]) {
    //make windows
    WindowManager windowManager;
    //make ring buffer
    RingBuffer ringBuffer(windowManager.getMessageWindowRows() - 1);
    //make client
    ClientManager clientManager("localhost", 20000, &ringBuffer);
    //set the ring buffer for the window manager
    windowManager.setRingBuffer(&ringBuffer);
    //make thread for incoming messages
    thread incomingMessageListener()
    //start getting user input
    windowManager.getUserInput();


    //clean uo windows
    windowManager.killWindowManager();

    return 0;
}
