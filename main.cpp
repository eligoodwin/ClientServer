#include <iostream>
#include "ClientManager.h"
#include "Helper.h"
#include <thread>

using namespace std;

void printBuffer(RingBuffer& ringBuffer);

int main(int argc, char* argv[]) {
    //get first argument == hostname
    cout << YELLOW << "Welcome to the client program. If you wish to quit while chatting with the server enter: '/quit' into the terminal" << RESET <<endl;

    int targetHostport = getPortFromArgs(argv, argc);
    //get second argumetn == portnumber
    string targetHostname = argv[1];
    //get username
    string username = getUsername();
    cout << YELLOW << "...Attempting to init client..." << endl;
    cout  << "\tPort number: " << targetHostport << endl;
    cout << "\tTarget host: " << targetHostname << RESET << endl;

    RingBuffer ringBuffer(20);
    //init clientmanager
    ClientManager clientManager = ClientManager(targetHostname, targetHostport, &ringBuffer);

    username += "> ";
    //set up for input loop

    thread incomingMessage(&ClientManager::incomingListener, ref(clientManager));
    bool quitFlag = false;
    while (!quitFlag) {
        string inputString;
        cout << GREEN << "MESSAGE TO SEND: " << RESET;
        getline(cin, inputString);
        //prepend useranem to inputstring
        string messageOut = username + inputString;
        //send message
        clientManager.sendMessage(messageOut);
        printBuffer(ringBuffer);

        if(inputString == "/quit") {
            quitFlag = true;
            clientManager.killListener();
            incomingMessage.join();
            clientManager.endConnection();
        }
    }


    cout << RED << "ENDING PROGRAM" << RESET << endl;
    return 0;
}

void printBuffer(RingBuffer& ringBuffer){
    int bufferStart = ringBuffer.getStart();
    int bufferCapacity = ringBuffer.getCapacity();
    //clear the window
    Data* messageData = nullptr;
    //start writing to screen
    for(int i = 0; i < bufferCapacity; ++i){
        if(bufferStart == 0){
            messageData =  ringBuffer.iterateObject(i);
        }
        else{
            messageData = ringBuffer.iterateObject((i + bufferStart) % bufferCapacity);
        }

        if(!messageData->message.empty() && !messageData->fromClinet){
            //print client info to screen
            cout << MAGENTA << "SERVER SAID: " << messageData->message << RESET << endl;
        }
        else if(!messageData->message.empty() && messageData->fromClinet){
            //print message to screen from server
            cout << GREEN << "YOU SAID: " <<  messageData->message << RESET << endl;
        }
    }
}