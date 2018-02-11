//
// Created by eli goodwin on 2/9/18.
//

#ifndef CLIENTSERVER_HELPER_H
#define CLIENTSERVER_HELPER_H
#include <iostream>
#include "Colors.h"

void error(const char* msg);
int getPortFromArgs(char *argv[], int argc);
std::string getUsername();
std::string getHostname(char* hostname);

#endif //CLIENTSERVER_HELPER_H
