#include <iostream>
using namespace std;

class Booking;

class TicketPrinter {
public:
    void printTicket(Booking* booking) const {
        cout << "\n========== TICKET ==========\n";
        cout << booking->getBookingDetails() << "\n";
        cout << "============================\n";
    }
};
