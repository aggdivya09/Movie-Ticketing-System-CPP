#include <string>
using namespace std;

class Seat;

class ShowSeat {
private:
    int showSeatId;
    Seat* seat;
    string status;

public:
    ShowSeat(int id, Seat* selectedSeat)
        : showSeatId(id), seat(selectedSeat), status("AVAILABLE") {}

    bool isAvailable() const {
        return status == "AVAILABLE";
    }

    void book() {
        status = "BOOKED";
    }

    void release() {
        status = "AVAILABLE";
    }

    Seat* getSeat() const {
        return seat;
    }

    string getStatus() const {
        return status;
    }
};
