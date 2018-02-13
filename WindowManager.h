//
// Created by eli goodwin on 2/12/18.
//

#ifndef CLIENTSERVER_WINDOWMANAGER_H
#define CLIENTSERVER_WINDOWMANAGER_H
#include <iostream>
#include <ncurses.h>
#include "RingBuffer.h"


class WindowManager {
public:
    WindowManager();
    void killWindowManager();
    void setRingBuffer(RingBuffer *ringBuffer);
    int getMessageWindowRows();
    void updateMessageWindow();
    void getUserInput(std::function < void(std::string) > theFunction);


private:
    WINDOW* messageDisplayWindow;
    WINDOW* userInputWindow;
    RingBuffer* ringBuffer;
};


#endif //CLIENTSERVER_WINDOWMANAGER_H
