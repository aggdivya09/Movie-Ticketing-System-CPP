#include <iostream>
using namespace std;

class Payment {
protected:
    double amount;

public:
    Payment(double a = 0.0) : amount(a) {}

    virtual bool pay(double amount) = 0;

    virtual ~Payment() = default;
};
