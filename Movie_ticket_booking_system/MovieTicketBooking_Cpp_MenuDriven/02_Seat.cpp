#include <iostream>
#include <string>
using namespace std;

class Seat {
private:
    int seatId;
    string seatNumber;
    string category;

public:
    Seat(int id, string number, string type)
        : seatId(id), seatNumber(number), category(type) {}

    bool isAvailable() const { return true; }
    bool book() { return true; }
    void release() {}

    int getSeatId() const { return seatId; }
    string getSeatNumber() const { return seatNumber; }
    string getCategory() const { return category; }
};
