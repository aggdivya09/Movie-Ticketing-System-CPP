#include <iostream>
#include <vector>
#include <string>
using namespace std;

class PriceCalculator {
private:
    double silverPrice;
    double goldPrice;
    double platinumPrice;

public:
    PriceCalculator(double silver, double gold, double platinum)
        : silverPrice(silver), goldPrice(gold), platinumPrice(platinum) {}

    double calculatePrice(const vector<ShowSeat*>& seats) const {
        double total = 0.0;

        for (ShowSeat* ss : seats) {
            string category = ss->getSeat()->getCategory();

            if (category == "SILVER")
                total += silverPrice;
            else if (category == "GOLD")
                total += goldPrice;
            else if (category == "PLATINUM")
                total += platinumPrice;
        }

        return total;
    }

    // Compile-time polymorphism: overloaded method.
    double calculatePrice(int numberOfSeats, double pricePerSeat) const {
        return numberOfSeats * pricePerSeat;
    }
};
