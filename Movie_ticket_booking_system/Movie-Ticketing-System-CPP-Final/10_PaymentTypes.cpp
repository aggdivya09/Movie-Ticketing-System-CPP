#include <string>
using namespace std;

class UpiPayment : public Payment {
private:
    string upiId;

public:
    UpiPayment(const string& id)
        : upiId(id) {}

    bool pay(double paymentAmount) override {
        amount = paymentAmount;
        return true;
    }
};

class CardPayment : public Payment {
private:
    string cardNumber;

public:
    CardPayment(const string& number)
        : cardNumber(number) {}

    bool pay(double paymentAmount) override {
        amount = paymentAmount;
        return true;
    }
};

class CashPayment : public Payment {
public:
    bool pay(double paymentAmount) override {
        amount = paymentAmount;
        return true;
    }
};
