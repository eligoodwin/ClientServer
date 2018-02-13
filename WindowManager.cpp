//
// Created by eli goodwin on 2/12/18.
//

#include "WindowManager.h"
using namespace std;
WindowManager::WindowManager(){
    //init
    initscr();
    ringBuffer = nullptr;
    //get dimensions of windows
    int parentX = 0;
    int parentY = 0;
    int messageWindowHeight = 2;
    getmaxyx(stdscr, parentY, parentX);
    //make the windows
    messageDisplayWindow = newwin(parentY - messageWindowHeight, parentX, 0, 0);
    userInputWindow = newwin(messageWindowHeight, parentX, parentY - messageWindowHeight, 0);
    //init windows
    keypad(userInputWindow, true);

    //display fist message to windows
    mvwprintw(messageDisplayWindow, 0,0, "MESSAGES:");
    mvwprintw(userInputWindow, 0, 0, "MESSAGE INPUT:");
    wrefresh(messageDisplayWindow);
    wrefresh(userInputWindow);

}

void WindowManager::killWindowManager() {
    wclear(userInputWindow);
    wclear(messageDisplayWindow);
    delwin(userInputWindow);
    delwin(messageDisplayWindow);
    endwin();
}
/
//used to set the size of the ring buffer
int WindowManager::getMessageWindowRows() {
    return getmaxy(this->messageDisplayWindow);
}

void WindowManager::getUserInput() {
    int rows = getmaxy(this->userInputWindow);
    char inputBuffer[500];

    while(strcmp(inputBuffer, "/quit") != 0){
        curs_set(1);
        memset(inputBuffer, '\0', 500 * sizeof(char));
        wmove(userInputWindow, rows - 1, 0);
        wclrtobot(userInputWindow);
        wprintw(userInputWindow, "SEND >> ");
        wgetstr(userInputWindow, inputBuffer);
        wclrtoeol(userInputWindow);
        ringBuffer->push(inputBuffer, true);

        this->updateMessageWindow();
    }
}

void WindowManager::setRingBuffer(RingBuffer *ringBuffer) {
    this->ringBuffer = ringBuffer;
}

void WindowManager::updateMessageWindow() {
    curs_set(0);
    int bufferCapacity = ringBuffer->getCapacity();
    wclear(messageDisplayWindow);
    mvwprintw(messageDisplayWindow, 0, 0, "MESSAGES:");
    Data* messageData = nullptr;
    for(int i = 0; i < bufferCapacity; ++i){
        messageData = ringBuffer->iterateObject(i);
        if(!messageData->message.empty() && messageData->fromClinet){
            mvwprintw(messageDisplayWindow, i + 1, 0, "SERVER SAYS: %s", messageData->message.c_str());
        }
        else if(!messageData->message.empty() && messageData->fromClinet){
            mvwprintw(messageDisplayWindow, i + 1, 0, "YOU SAID: %s", messageData->message.c_str());
        }
    }

    curs_set(1);
    wrefresh(messageDisplayWindow);
}