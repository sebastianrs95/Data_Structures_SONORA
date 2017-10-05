#include <iostream>
#include "Client.h"
#include "Cashier.h"
#include "Queue.h"
#include "Stack.h"
#include "Bank.h"
#include <ctime>
#include <cstdlib>


/**
    \brief Function that generates a random number from startPoint, and up to max (including it).
    \param max An integer that holds the maximum value of the interval (including it).
    \param startPoint An integer from where to start the interval (including it).
    \return A random integer between [startPoint, max]
*/
int generateRandInt( int max, int startPoint );

using namespace std;

int main()
{
/*
    Queue<Cashier*> cashierQueue;
    Queue<Client*> clientQueue;

    srand(time(0));
    int totalMins = 420;
    int randMinutes, currentTime = 0;

    while( totalMins > 0 )
    {
        randMinutes = generateRandInt(30,1);
        currentTime += randMinutes;
        totalMins -= randMinutes;

        if( totalMins <= 0 ) break;

        clientQueue.push(new Client(currentTime));
        clientQueue.pop()->printData();
        cout << endl;
    }
*/


    srand(time(0));
    Bank bank;
    bank.initializeClientQueue();
    bank.initializeCashiers();
    //bank.printTotalClients();

    for( int i = 0 ; i < 420 ; ++i )
    {
        bank.processTransaction();
    }

    cout << endl << endl;
    for( int i = 400 ; i <= 420 ; ++i )
    {
        bank.printTransaction(i);
        cout << endl << endl;
    }


    return 0;
}


