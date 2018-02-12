//
// Created by eli goodwin on 2/12/18.
//


#include "RingBufferManager.h"
using namespace std;

RingBufferManager::RingBufferManager(int capacity) {
    this->ringBuffer = new RingBuffer(capacity);
}

void RingBufferManager::pushToBuffer(string message, bool origin) {
    ringBuffer->push(message, origin);
}

void RingBufferManager::updateWindow(){}