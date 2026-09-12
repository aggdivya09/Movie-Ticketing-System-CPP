#include <iostream>
#include <string>
using namespace std;

class UpiPayment : public Payment {
private:
    string upiId;

public:
    UpiPayment(string id) : Payment(), upiId(id) {}

    bool pay(double amount) override {
        cout << "UPI payment of Rs." << amount
             << " successful using " << upiId << ".\n";
        return true;
    }
};

class CardPayment : public Payment {
private:
    string cardNumber;

public:
    CardPayment(string card) : Payment(), cardNumber(card) {}

    bool pay(double amount) override {
        cout << "Card payment of Rs." << amount << " successful.\n";
        return true;
    }
};

class CashPayment : public Payment {
public:
    CashPayment() : Payment() {}

    bool pay(double amount) override {
        cout << "Cash payment of Rs." << amount << " received.\n";
        return true;
    }
};
