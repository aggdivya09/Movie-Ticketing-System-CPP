#include <string>
#include <vector>
using namespace std;

class ShowSeat;

class PriceCalculator {
private:
    double silverPrice;
    double goldPrice;
    double platinumPrice;

public:
    PriceCalculator(double silver, double gold, double platinum)
        : silverPrice(silver),
          goldPrice(gold),
          platinumPrice(platinum) {}

    double calculatePrice(const vector<ShowSeat*>& seats) const;

    double calculatePrice(int quantity, double pricePerSeat) const {
        return quantity * pricePerSeat;
    }
};
