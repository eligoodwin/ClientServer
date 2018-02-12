#include <iostream>
#include "ClientManager.h"
#include "Helper.h"
#include "WindowManager.h"

using namespace std;

int main(int argc, char* argv[]) {
    //make windows
    WindowManager windowManager;
    //make ring buffer
    RingBuffer ringBuffer(windowManager.getMessageWindowRows());
    //make client
    ClientManager clientManager("localhost", 15000, &ringBuffer);
    //set the ring buffer for the window manager
    windowManager.setRingBuffer(&ringBuffer);

    windowManager.getUserInput();

    //make thread for incoming messages

    //clean uo windows
    windowManager.killWindowManager();

    return 0;
}
