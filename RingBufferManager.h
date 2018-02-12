//
// Created by eli goodwin on 2/12/18.
//

#ifndef CLIENTSERVER_RINGBUFFERMANAGER_H
#define CLIENTSERVER_RINGBUFFERMANAGER_H

/*
 * interface for the the
 * -client manager
 * -the ringbuffer
 * -the window manager
 *
 * manager will interact with the window object in question
 * when we push to the buffer this will cause the window to update.
 * This means that when the message from the server is inserted into
 * ring buffer manager it will also update the window.
 *
 * */

#include "RingBuffer.h"
#include <iostream>
class RingBufferManager {
public:
    void pushToBuffer(std::string message, bool origin);
    void updateWindow();
    RingBufferManager(int capacity);
    RingBuffer* ringBuffer;
};


#endif //CLIENTSERVER_RINGBUFFERMANAGER_H
