//
// Created by eli goodwin on 2/9/18.
//

using namespace std;
#include "ClientManager.h"
ClientManager::ClientManager(std::string username, std::string targethostName, int targetHostPort) {
    this->username = username;
    serverHostInfo = gethostbyname(targethostName.c_str());
    this->targetHostPort = targetHostPort;
}

void ClientManager::addMessageToQueue(std::string message){
    messagesToSend.push(message);
    sendMessage();
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

bool ClientManager::sendMessage(){
    if(!messagesToSend.empty()){
        string message = messagesToSend.front();
        messagesToSend.pop();
        //prepare the buffer
        memset(buffer, '\0', BUFFER_SIZE * sizeof(char));
        strcpy(buffer, message.c_str());
        //send message and get response
        send(socketFD, buffer, strlen(buffer), 0);
        //recv(socketFD, buffer, sizeof(buffer) - 1, 0);
        //cout << "RESPONSE: " << buffer << endl;


        return true;
    }
    return false;
};

bool ClientManager::connectToTargetHost(){
    return (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0);
}

void ClientManager::endConnection() {
    close(socketFD);
}

void ClientManager::printIncomingMessage(){

        memset(threadBuffer, '\0', BUFFER_SIZE * sizeof(char));
       int  size = recv(socketFD, buffer, sizeof(buffer) - 1, 0);
        if(size > 0)
            cout << "Received: " << threadBuffer << endl;
    }
}

void ClientManager::createRecievingThread() {
    thread receive(&ClientManager::printIncomingMessage, this);
}