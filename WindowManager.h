//
// Created by eli goodwin on 2/12/18.
//

#ifndef CLIENTSERVER_WINDOWMANAGER_H
#define CLIENTSERVER_WINDOWMANAGER_H
#include <iostream>
#include <ncurses.h>



class WindowManager {
public:
    WindowManager();
    void killWindowManager();
    int getMessageWindowRows();
    void getUserInput();

private:
    WINDOW* messageDisplayWindow;
    WINDOW* userInputWindow;
};


#endif //CLIENTSERVER_WINDOWMANAGER_H
