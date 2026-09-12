#include <iostream>
using namespace std;

class TicketPrinter {
public:
    void printTicket(Booking* booking) {
        cout << "\n========== TICKET ==========\n";
        cout << booking->getBookingDetails() << "\n";
        cout << "============================\n";
    }
};
