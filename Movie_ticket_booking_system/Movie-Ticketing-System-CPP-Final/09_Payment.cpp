class Payment {
protected:
    double amount;

public:
    Payment() : amount(0.0) {}
    virtual ~Payment() = default;

    virtual bool pay(double paymentAmount) = 0;
};
