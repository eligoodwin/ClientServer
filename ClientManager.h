/*********************************************************************
 ** Program Filename: ClientManager.hpp
 ** Author: Eli Goodwin
 ** Date: 2018/02/05
 ** Description: Manages the TCP connection to the server
 ** Input: none
 ** Output: none
 *********************************************************************/

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
    /*********************************************************************
     ** Function: ClientManager()
     ** Description: constructor for the TCP socket
     ** Parameters: requires a target host name and a target host port
     ** Pre-Conditions: port and hostname must be valid
     ** Post-Conditions: to complete initilization of of connection
     *      1. createSocket must be ran
     *      2. connectToTargetHost must be ran
     ** Return: none
     *********************************************************************/
    ClientManager(std::string targethostName, int targetHostPort);

    /*********************************************************************
     ** Function: createSocket()
     ** Description: inits the TCP socket
     ** Parameters: none
     ** Pre-Conditions: client object must be constructed first
     ** Post-Conditions: to complete initilization
     *      1. connectToTargetHost must be ran
     ** Return: flag if socket was initialized correctly
     *********************************************************************/
    bool createSocket();

    /*********************************************************************
     ** Function: sendMessage(string message)
     ** Description: sends message to targethost
     ** Parameters: string messsage -- message to send
     ** Pre-Conditions: connection with target host must be created
     ** Post-Conditions: none
     ** Return: none
     *********************************************************************/
    void sendMessage(std::string message);

    /*********************************************************************
     ** Function: connectToTargteHost()
     ** Description: creates initial connection to target host
     ** Parameters: none
     ** Pre-Conditions:
     *      1. ClientManager must be created
     *      2. sockset must be initialized
     ** Post-Conditions: to use the socket for sending data you must use sendmessage
     ** Return: none
     *********************************************************************/
    bool connectToTargetHost();

    /*********************************************************************
     ** Function: receiveMessage()
     ** Description: recieves response from server after sending a message
     ** Parameters: none
     ** Pre-Conditions:
     *      1. ClientManager must be created
     *      2. socket must be initialized
     *      3. message must be sent before recieving
     ** Post-Conditions: to receive a message you must have sent one prior to the server
     ** Return: message from server
     *********************************************************************/
    std::string receiveMessage();


    /*********************************************************************
     ** Function: endConnection()
     ** Description: frees the created socket and terminates connection with target server
     ** Parameters: none
     ** Pre-Conditions:
     *      1. ClientManager must be created
     *      2. socket must be initialized
     *      3. must be connected to target host server
     ** Post-Conditions: once the connection is severed with server, to communicate with the
     *      server again a new connection and client object needs to be made
     ** Return: none
     *********************************************************************/
    void endConnection();
    //void createRecievingThread();



private:
    //targethost port for socket
    int targetHostPort;
    //current host socket
    struct sockaddr_in serverAddress;
    struct hostent* serverHostInfo;
    int socketFD;
    //connection buffer
    char buffer[BUFFER_SIZE];
};

#endif //CLIENTSERVER_CLIENTMANAGER_H
