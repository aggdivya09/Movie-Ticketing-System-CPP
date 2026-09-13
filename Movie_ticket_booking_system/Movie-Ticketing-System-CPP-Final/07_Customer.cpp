#include <string>
#include <vector>
using namespace std;

class Customer {
private:
    int customerId;
    string name;
    string phone;

public:
    Customer(int id, const string& customerName, const string& customerPhone)
        : customerId(id), name(customerName), phone(customerPhone) {}

    void bookTicket(int showId, const vector<string>& seats) {
        // BookingService performs the actual booking.
    }

    void cancelBooking(int bookingId) {
        // BookingService performs the actual cancellation.
    }

    int getCustomerId() const { return customerId; }
    string getName() const { return name; }
    string getPhone() const { return phone; }
};
