#include <iostream>
#include "WindowManager.h"

using namespace std;

int main(int argc, char* argv[]) {
    //make windows
    WindowManager windowManager;
    //make ring buffer
    RingBuffer ringBuffer(windowManager.getMessageWindowRows() - 1);
    //make client

    //set the ring buffer for the window manager
    windowManager.setRingBuffer(&ringBuffer);
    //start getting user input
    windowManager.getUserInput();

    //make thread for incoming messages

    //clean uo windows
    windowManager.killWindowManager();

    return 0;
}
