/*********************************************************************
 ** Program : chatClient
 ** Author: Eli Goodwin
 ** Date: 2018/02/05
 ** Description: program is used to chat with a server
 ** Operation:
 *      1. make clientChat
 *      2. ./clientChat <hostname> <hostport>
 *      3. Corresponding server must be running for the program to work
 *********************************************************************/


#include <iostream>
#include "ClientManager.h"
#include "Helper.h"


using namespace std;
int main(int argc, char* argv[]) {
    //get first argument == hostname
    cout << YELLOW << "Welcome to the client program. If you wish to quit while chatting with the server enter: '/quit' into the terminal" << RESET <<endl;
    //get second argumetn == portnumber
    int targetHostport = getPortFromArgs(argv, argc);
    string targetHostname = argv[1];
    //get username
    string username = getUsername();
    cout << YELLOW << "...Attempting to init client..." << endl;
    cout  << "\tPort number: " << targetHostport << endl;
    cout << "\tTarget host: " << targetHostname << RESET << endl;


    //init clientmanager
    ClientManager clientManager = ClientManager(targetHostname, targetHostport);
    bool socketCreated = clientManager.createSocket();
    bool clientConnected = clientManager.connectToTargetHost();

    if(!socketCreated && !clientConnected){
        error(RED "ERROR: could not init socket or connect to client" RESET);
    }

    username += "> ";
    //set up for input loop
    bool quitFlag = false;

    while (!quitFlag) {
        string inputString;
        cout << GREEN << "MESSAGE TO SEND: " << RESET;
        getline(cin, inputString);
        //prepend useranem to inputstring
        string messageOut= username + inputString;
        //send message
        clientManager.sendMessage(messageOut);
        //retrieve response from server
        string incomingMessage = clientManager.receiveMessage();
        int found = incomingMessage.find("/quit");
        if(found != string::npos){
            quitFlag = true;
            incomingMessage = "***SERVER HAS TERMINATED CONNECTION***";
        }
        //print message from server
        cout << MAGENTA << "MESSAGE RECEIVED: " << incomingMessage << RESET << endl;
        if(inputString == "/quit")
            quitFlag = true;
    }

    clientManager.endConnection();
    cout << RED << "ENDING PROGRAM" << RESET << endl;
    return 0;
}