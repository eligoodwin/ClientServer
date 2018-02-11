#include <iostream>
#include "ClientManager.h"
#include "Helper.h"
#include <thread>

using namespace std;
int main(int argc, char* argv[]) {
    //get first argument == hostname
    int targetHostport = getPortFromArgs(argv, argc);
    //get second argumetn == portnumber
    string targetHostname = argv[1];
    //get username
    cout << "Targethost name: " << targetHostname << endl;
    cout << "Targethost port: " << targetHostport << endl;

    string username = "steve";//getUsername();
    //init clientmanager
    ClientManager clientManager = ClientManager(username, targetHostname, targetHostport);
    clientManager.createSocket();
    clientManager.connectToTargetHost();
    //set up for input loop

    bool quitFlag = false;
    while (!quitFlag) {
        string inputString;
        cout << "MESSAGE TO SEND: ";
        getline(cin, inputString);
        clientManager.addMessageToQueue(inputString);
        if(inputString == "/quit")
            quitFlag = true;
    }

    clientManager.endConnection();

    return 0;
}