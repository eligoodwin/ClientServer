//
// Created by eli goodwin on 2/9/18.
//

#include "Helper.h"
using namespace std;

void error(const char* msg){
    perror(msg);
    exit(0);
}

int getPortFromArgs(char *argv[], int argc ){
    if(argc != 3){
        return -1;
    }
    return atoi(argv[2]);
}


string getUsername(){
    string username = "";
    string response = "";
    cout << GREEN <<"Enter a username: " << RESET;
    do{
        getline(cin, username);
        if(username.size() > 10){
            cout << RED << "Please specify a username less than 10 characters long: " << RESET;
        }
        else{
            cout << GREEN << "You selected: " << username << " do you wish to keep (yes/no)?" << RESET;
            getline(cin, response);
            if(response != "yes"){
                cout << YELLOW << "please select a new username: " << RESET;
            }
        }
    }while(username.size() > 10 || response != "yes");
    return username;
}