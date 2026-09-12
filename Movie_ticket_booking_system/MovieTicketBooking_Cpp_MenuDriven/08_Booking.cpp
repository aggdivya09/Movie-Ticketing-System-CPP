#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Customer;
class Show;
class ShowSeat;
class Payment;

class Booking {
private:
    int bookingId;
    Customer* customer;
    Show* show;
    vector<ShowSeat*> showSeats;
    Payment* payment;
    double totalAmount;
    string status;

    static int nextBookingId;

public:
    Booking(Customer* c, Show* s, const vector<ShowSeat*>& seats, Payment* p)
        : bookingId(++nextBookingId), customer(c), show(s),
          showSeats(seats), payment(p), totalAmount(0.0),
          status("PENDING") {}

    void setTotalAmount(double amount) {
        this->totalAmount = amount;
    }

    void confirmBooking() {
        status = "CONFIRMED";
    }

    void cancelBooking() {
        status = "CANCELLED";
        for (ShowSeat* ss : showSeats)
            ss->release();
    }

    int getBookingId() const { return bookingId; }
    double getTotalAmount() const { return totalAmount; }
    string getStatus() const { return status; }
    Customer* getCustomer() const { return customer; }

    string getBookingDetails() const {
        return "Booking ID: " + to_string(bookingId) +
               " | Amount: Rs." + to_string(totalAmount) +
               " | Status: " + status;
    }
};

int Booking::nextBookingId = 1000;
