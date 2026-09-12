#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Customer {
private:
    int customerId;
    string name;
    string phone;

public:
    Customer(int id, string n, string p)
        : customerId(id), name(n), phone(p) {}

    void bookTicket(int showId, const vector<string>& seats) {
        cout << "\nBooking request for Show " << showId << ": ";
        for (const string& seat : seats)
            cout << seat << " ";
        cout << "\n";
    }

    void cancelBooking(int bookingId) {
        cout << "\nCancellation request for Booking "
             << bookingId << ".\n";
    }

    int getCustomerId() const { return customerId; }
    string getName() const { return name; }
};
