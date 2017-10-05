#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>

class Client
{
public:

    Client();
    Client(int);
    Client(int,int);
    ~Client();

    int getDifficulty(){return difficulty;}
    void setDifficulty(int _difficulty){ difficulty= _difficulty; }

    int getArrivalTime(){return arrivalTime;}
    void setArrivalTime(int _arrivalTime){ arrivalTime = _arrivalTime; }

    int getWaitingTime(){return waitingTime;}
    void setWaitingTime(int _waitingTime){ waitingTime = _waitingTime; }

    void printData();

private:
    int difficulty;     // a random integer, generated in the constructor
    int arrivalTime;
    int waitingTime;    // the time it took for the client to realize his transaction or whatever
};

Client::Client()
{
    difficulty = 1;
}

Client::Client(int _arrivalTime )
{
    difficulty = 1;
    arrivalTime = _arrivalTime;
}

Client::Client(int _difficulty, int _arrivalTime )
{
    difficulty = _difficulty;
    arrivalTime = _arrivalTime;
}

Client::~Client()
{
    difficulty = 0;
}

void Client::printData()
{
    std::cout << "Arrival time: " << arrivalTime;
}

#endif // CLIENT_H_INCLUDED
