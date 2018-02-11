/*********************************************************************
 ** Program Filename: Helper.h
 ** Author: Eli Goodwin
 ** Date: 2018/02/05
 ** Description: Helpers for the chat client
 ** Input: none
 ** Output: none
 *********************************************************************/

#ifndef CLIENTSERVER_HELPER_H
#define CLIENTSERVER_HELPER_H
#include <iostream>
#include "Colors.h"
/*********************************************************************
    ** Function: Error()
    ** Description: used for printing errors in the program
    ** Parameters: const char* msg = messsage to display user
    ** Pre-Conditions: error must have occurred
    ** Post-Conditions: none
    ** Return: none
    *********************************************************************/
void error(const char* msg);

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
int getPortFromArgs(char *argv[], int argc);

/*********************************************************************
    ** Function: getUsername()
    ** Description: gets and validates username from user
    ** Parameters: none
    ** Pre-Conditions: none
    ** Post-Conditions: none
    ** Return: string representing username of client
    *********************************************************************/
std::string getUsername();

#endif //CLIENTSERVER_HELPER_H
