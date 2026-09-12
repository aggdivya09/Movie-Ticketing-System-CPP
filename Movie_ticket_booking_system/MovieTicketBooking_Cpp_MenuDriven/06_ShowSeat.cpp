#include <iostream>
#include <string>
using namespace std;

class Seat;

class ShowSeat {
private:
    int showSeatId;
    Seat* seat;
    string status;

public:
    ShowSeat(int id, Seat* s)
        : showSeatId(id), seat(s), status("AVAILABLE") {}

    bool isAvailable() const {
        return status == "AVAILABLE";
    }

    bool book() {
        if (!isAvailable()) return false;
        status = "BOOKED";
        return true;
    }

    void release() {
        status = "AVAILABLE";
    }

    int getShowSeatId() const { return showSeatId; }
    Seat* getSeat() const { return seat; }
    string getStatus() const { return status; }
};
