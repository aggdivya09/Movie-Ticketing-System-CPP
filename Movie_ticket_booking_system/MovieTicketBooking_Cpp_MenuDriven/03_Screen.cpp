#include <iostream>
#include <vector>
using namespace std;

class Seat;

class Screen {
private:
    int screenId;
    int screenNumber;
    vector<Seat*> seats;

public:
    Screen(int id, int number) : screenId(id), screenNumber(number) {}

    void addSeat(Seat* seat) {
        seats.push_back(seat);
    }

    vector<Seat*> getSeats() const {
        return seats;
    }

    int getScreenNumber() const { return screenNumber; }
};
