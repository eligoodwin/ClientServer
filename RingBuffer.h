//
// Created by eli goodwin on 2/7/18.
//

#ifndef TESTINGTHREADING_RINGBUFFER_H
#define TESTINGTHREADING_RINGBUFFER_H
#include <mutex>
#include <iostream>
#include <vector>
typedef struct Data{
    std::string message;
    bool fromClinet;
    Data(bool origin, std::string mess){
        message = mess;
        fromClinet = origin;
    }
}MessageData;

class RingBuffer {
public:
    RingBuffer(int capacity);
    void push(std::string mess, bool fromClient);
    MessageData* getTopMessage();
    MessageData* iterateObject(int i);
    int getSize();
    int getCapacity();
    int getStart();

private:
    std::mutex protectBuffer;
    int size;
    int capacity;
    int currentIndex;
    std::vector<MessageData> storage;
};


#endif //TESTINGTHREADING_RINGBUFFER_H
