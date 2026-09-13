#include <string>
using namespace std;

class Seat {
private:
    int seatId;
    string seatNumber;
    string category;

public:
    Seat(int id, const string& number, const string& type)
        : seatId(id), seatNumber(number), category(type) {}

    bool isAvailable() const { return true; }
    void book() {}
    void release() {}

    string getSeatNumber() const { return seatNumber; }
    string getCategory() const { return category; }
};
