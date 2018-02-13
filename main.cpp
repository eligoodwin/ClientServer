#include <iostream>
#include "WindowManager.h"
#include <thread>
#include "ClientManager.h"
#include <functional>
using namespace std;

int main(int argc, char* argv[]) {
    //make windows
    WindowManager windowManager;
    //make ring buffer
    RingBuffer ringBuffer(windowManager.getMessageWindowRows() - 1);
    //make client
    ClientManager clientManager("localhost", 20040, &ringBuffer);
    //set the ring buffer for the window manager
    windowManager.setRingBuffer(&ringBuffer);
    //make thread for incoming messages
    thread incomingMessageListener(&ClientManager::incomingListener,
                                   ref(clientManager),
                                   bind(&WindowManager::updateMessageWindow, ref(windowManager)));
    //start getting user input
    windowManager.getUserInput(bind(&ClientManager::sendMessage,
                                    ref(clientManager),
                                    placeholders::_1));
    //kill the listener
    clientManager.killListener();
    incomingMessageListener.join();
    clientManager.endConnection();

    //clean uo windows
    windowManager.killWindowManager();

    return 0;
}
