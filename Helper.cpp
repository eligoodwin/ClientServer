/*********************************************************************
 ** Program Filename: Helper.h
 ** Author: Eli Goodwin
 ** Date: 2018/02/05
 ** Description: Manages the TCP connection to the server
 ** Input: none
 ** Output: none
 *********************************************************************/

#include "Helper.h"
using namespace std;

/*********************************************************************
    ** Function: Error()
    ** Description: used for printing errors in the program
    ** Parameters: const char* msg = messsage to display user
    ** Pre-Conditions: error must have occurred
    ** Post-Conditions: none
    ** Return: none
    *********************************************************************/
void error(const char* msg){
    perror(msg);
    exit(0);
}

/*********************************************************************
    ** Function: getPortFromArgs()
    ** Description: gets command line arguments and validates them
    ** Parameters:
    *       char* argv[] array of arguments
    *       int argc number of arguments
    ** Pre-Conditions: none
    ** Post-Conditions: terminate program if arguments are incorrect
    ** Return: none
    *********************************************************************/
int getPortFromArgs(char *argv[], int argc ){
    if(argc != 3){
        error("ERROR: too few arguments. input should be './chatClient <hostname> <port>'");
    }
    return atoi(argv[2]);
}

/*********************************************************************
    ** Function: getUsername()
    ** Description: gets and validates username from user
    ** Parameters: none
    ** Pre-Conditions: none
    ** Post-Conditions: none
    ** Return: string representing username of client
    *********************************************************************/
string getUsername(){
    string username;
    string response;
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