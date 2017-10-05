#ifndef CASHIER_H_INCLUDED
#define CASHIER_H_INCLUDED

#include <string>
#include <ctime>
#include <cstdlib>

class Cashier
{
public:
    Cashier();
    Cashier(int);
    Cashier(std::string, int);
    ~Cashier();

    std::string getName(){ return name; }
    int getAvgProcessTime(){ return avgProcessTime; }
    int getTimeLeft(){ return timeLeft; }
    void setTimeLeft(int newVal){ timeLeft = newVal; }

private:

    std::string name;
    int avgProcessTime;     // this will be generated as a random value in the constructor
    int timeLeft;
};

Cashier::Cashier()
{
    name = "";
    avgProcessTime = 0;
    timeLeft = 0;
}

Cashier::Cashier(int _avgProcessTime)
{
    name = "";
    avgProcessTime = _avgProcessTime;
}

Cashier::Cashier(std::string _name, int _avgProcessTime)
{
    name = _name;
    avgProcessTime = _avgProcessTime;
}

Cashier::~Cashier()
{
    name = "";
    avgProcessTime = 0;
}


#endif // CASHIER_H_INCLUDED
