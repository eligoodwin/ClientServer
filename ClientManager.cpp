/*********************************************************************
 ** Program Filename: ClientManager.hpp
 ** Author: Eli Goodwin
 ** Date: 2018/02/05
 ** Description: Manages the TCP connection to the server
 ** Input: none
 ** Output: none
 *********************************************************************/

#include "ClientManager.h"
#include <string.h>


using namespace std;

ClientManager::ClientManager(std::string targethostName, int targetHostPort) {
    serverHostInfo = gethostbyname(targethostName.c_str());
    this->targetHostPort = targetHostPort;
}


//client created successfully
bool ClientManager::createSocket() {
    memset((char*)&serverAddress, '\0', sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(this->targetHostPort);

    if(serverHostInfo == NULL){
        return false;
    }

    memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length );
    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if(socketFD < 0)
        return false;
    return true;
}

void ClientManager::sendMessage(string message){
        //prepare the buffer
        memset(buffer, '\0', BUFFER_SIZE * sizeof(char));
        strcpy(buffer, message.c_str());
        //send message and get response
        write(socketFD, buffer, strlen(buffer));

};

string ClientManager::receiveMessage(){
    memset(buffer, '\0', BUFFER_SIZE * sizeof(char));
    recv(socketFD, buffer, BUFFER_SIZE, 0);

    return buffer;
}


bool ClientManager::connectToTargetHost(){
    return (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0);
}

void ClientManager::endConnection() {
    close(socketFD);
}

