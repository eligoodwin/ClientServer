//
// Created by eli goodwin on 2/9/18.
//

#include "ClientManager.h"


using namespace std;

ClientManager::ClientManager(std::string targethostName, int targetHostPort, RingBuffer* rb) {
    serverHostInfo = gethostbyname(targethostName.c_str());
    this->targetHostPort = targetHostPort;
    killWorkerThread = false;
    this->createSocket();
    this->connectToTargetHost();
    ringBuffer = rb;
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
        send(socketFD, buffer, strlen(buffer), 0);
        ringBuffer->push(buffer, true);
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

void ClientManager::incomingListener() {
    char tempBuffer[BUFFER_SIZE];
    memset(tempBuffer, '\0', BUFFER_SIZE * sizeof(char));
    while(!killWorkerThread){
        int result = recv(socketFD, tempBuffer, BUFFER_SIZE, 0);
        if(result > 0){
            ringBuffer->push(tempBuffer, false);
            memset(buffer, '\0', BUFFER_SIZE * sizeof(char));
        }
    }
}

void ClientManager::killListener() {
    killWorkerThread = true;
}