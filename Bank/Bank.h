#ifndef BANK_H_INCLUDED
#define BANK_H_INCLUDED

#include <vector>

struct Transaction
{
    int numClients;
    int inLine;
    int availableCashiers;
    int time;
    int numTransactions;
    int greatestWaitingTime;
};

/**
    \brief Function that generates a random number from startPoint, and up to max (including it).
    \param startPoint An integer from where to start the interval (including it).
    \param max An integer that holds the maximum value of the interval (including it).
    \return A random integer between [startPoint, max]
*/
int generateRandInt( int startPoint, int max)
{
    return (rand() % (max+1) + startPoint);
}

class Bank
{
public:

    Bank();
    ~Bank(){}

    /**
        \brief This method adds a client (Client object) to the waiting line (Queue<Client>).
    */
    void addClient();


    /**
        \brief Processes next transaction.
    */
    void processTransaction();

    /**
        \brief Prints current status.
    */
    void printStatus();

    /**
        \brief This method initializes the Client waiting line.
    */
    void initializeClientQueue();

    /**
        \brief Initializes the number of cashiers available.
    */
    void initializeCashiers();

    void updateCashiers();
    void updateWaitingLine();


    /**
        \brief This method prints the clients arrival time.
    */
    void printClients();
    void printTotalClients();

    /**
        \brief This method prints the cashiers available.
    */
    void printCashiers();
    void printTransaction( int minute );

private:
    Queue<Cashier*> cashiers;
    vector<Cashier*> busyCashiers;
    vector<Transaction*> transactions;

    Queue<Client*> waitingLine, totalClients;


    int currentTime, totalMins, numClients, numCashiers;
    int numTransactions, availableCashiers, lastArrivalTime, greatestWaitingTime;
};


Bank::Bank()
{
    totalMins = 420;    // a 7 hour work day
    greatestWaitingTime = numTransactions = numClients = currentTime = lastArrivalTime = 0;
    availableCashiers = numCashiers = 1;
}

void Bank::initializeCashiers()
{
    for( int i = 0 ; i < numCashiers ; ++i )
    {
        cashiers.push(new Cashier());
    }
}

void Bank::initializeClientQueue()
{

    int randMinutes, arrivalTime = 0;
    int totalMinutes = totalMins;

    while( totalMinutes > 0 )
    {
        randMinutes = generateRandInt(1,30);
        arrivalTime += randMinutes;
        totalMinutes -= randMinutes;

        if( totalMinutes <= 0 ) break;
        totalClients.push(new Client(arrivalTime));
    }
}

void Bank::updateCashiers()
{
    if(busyCashiers.empty()) return;
    for( int i = 0 ; i < busyCashiers.size() ; ++i )
    {

        busyCashiers[i]->setTimeLeft( busyCashiers[i]->getTimeLeft() - 1 );
        if(busyCashiers[i]->getTimeLeft() == 0)
        {
            cashiers.push(busyCashiers[i]);
            busyCashiers.erase( busyCashiers.begin() + i ); // erase the cashier from the vector
            ++numTransactions;
            break;  // get out of the loop
        }
    }
}

void Bank::updateWaitingLine()
{
    if( totalClients.empty() ) return;
    if( totalClients.peek()->getArrivalTime() == currentTime )
    {
        waitingLine.push(totalClients.pop());    // add another client to the waitingLine, if it's time
        cout << "updated waiting line: " << waitingLine.size() << " in waiting line with time: " << currentTime << endl;
        cout << "remaining clients in the TOTAL line: " << totalClients.size() << endl;
    }
}

void Bank::processTransaction()
{
    ++currentTime;
    cout << "The current time is: " << currentTime << endl;
    cout << "The cashiers are: " << cashiers.size() << endl;
    updateWaitingLine();
    updateCashiers();

    Transaction * newTransanction;
    newTransanction = (Transaction*) malloc(sizeof(Transaction));

    if( !cashiers.empty() && !waitingLine.empty())     // process the next client, if there are cashiers available
    {
        int randMinutes = generateRandInt(1, 30);

        Client * nextClient = waitingLine.pop();  // the client leaves the waiting line, but we store it

        cout << "INSIDE THE FUCKING IF " << nextClient->getArrivalTime() << endl;
        int tempWaitingTime = currentTime - nextClient->getArrivalTime();    // calculate client's waiting time
        if(tempWaitingTime > greatestWaitingTime ) greatestWaitingTime = tempWaitingTime;
        cout << "greatest waiting time is now: " << greatestWaitingTime << endl;


        Cashier * nextCashier = cashiers.pop();
        nextCashier->setTimeLeft(randMinutes);

        busyCashiers.push_back(nextCashier);  // transfer the next cashier to busyCashiers

        newTransanction->numClients = busyCashiers.size() + waitingLine.size();     // busyCashiers means clients, plus the ones on the waitingLine
        newTransanction->inLine = waitingLine.size();
        newTransanction->time = currentTime;
        newTransanction->availableCashiers = cashiers.size();
        newTransanction->numTransactions = numTransactions;
        newTransanction->greatestWaitingTime = greatestWaitingTime;

        transactions.push_back(newTransanction);
    }
    else    // if transaction could not be realized, print data to new Transaction.
    {
        newTransanction->numClients = busyCashiers.size() + waitingLine.size();     // busyCashiers means clients, plus the ones on the waitingLine
        newTransanction->inLine = waitingLine.size();
        newTransanction->time = currentTime;
        newTransanction->availableCashiers = cashiers.size();
        newTransanction->numTransactions = numTransactions;
        newTransanction->greatestWaitingTime = greatestWaitingTime;

        transactions.push_back(newTransanction);
    }

}

void Bank::printTransaction( int minute )
{
    int index = minute - 1;
    cout << "Current time: " << transactions[index]->time;
    cout << endl << "Number of Clients waiting: " << transactions[index]->inLine;
    cout << endl << "Available Cashiers: " << transactions[index]->availableCashiers;
    cout << endl << "Longest waiting time until now: " << transactions[index]->greatestWaitingTime;
    cout << endl << "Transactions made: " << transactions[index]->numTransactions;
}

void Bank::printTotalClients()
{
    int total = totalClients.size();
    for( int i = 0 ; i < total ; i++ )
    {
        cout << "Client arrival time: " << totalClients.pop()->getArrivalTime() << endl;
    }
}


#endif // BANK_H_INCLUDED
