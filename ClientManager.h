//
// Created by eli goodwin on 2/9/18.
//

#ifndef CLIENTSERVER_CLIENTMANAGER_H
#define CLIENTSERVER_CLIENTMANAGER_H

#include <thread>
#include <iostream>
#include <queue>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

const int BUFFER_SIZE = 500;
class ClientManager {
public:
    ClientManager(std::string username, std::string targethostName, int targetHostPort);
    void addMessageToQueue(std::string message);
    bool createSocket();
    bool connectToTargetHost();
    void endConnection();
    void createRecievingThread();
    void printIncomingMessage();
private:
    //targethost port for socket
    int targetHostPort;
    std::string username;
    //used to store entered messages
    std::queue<std::string> messagesToSend;
    //current host socket
    struct sockaddr_in serverAddress;
    struct hostent* serverHostInfo;
    int socketFD;
    //connection buffer
    char buffer[BUFFER_SIZE];
    //send message
    bool sendMessage();

};

#endif //CLIENTSERVER_CLIENTMANAGER_H
