#include <string>
#include <vector>
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
    Booking(Customer* selectedCustomer,
            Show* selectedShow,
            const vector<ShowSeat*>& selectedSeats,
            Payment* selectedPayment)
        : bookingId(nextBookingId++),
          customer(selectedCustomer),
          show(selectedShow),
          showSeats(selectedSeats),
          payment(selectedPayment),
          totalAmount(0.0),
          status("PENDING") {}

    void setTotalAmount(double amount) {
        totalAmount = amount;
    }

    void confirmBooking() {
        status = "CONFIRMED";
    }

    void cancelBooking() {
        status = "CANCELLED";
        for (ShowSeat* showSeat : showSeats)
            showSeat->release();
    }

    int getBookingId() const {
        return bookingId;
    }

    double getTotalAmount() const {
        return totalAmount;
    }

    string getStatus() const {
        return status;
    }

    Customer* getCustomer() const {
        return customer;
    }

    Show* getShow() const {
        return show;
    }

    const vector<ShowSeat*>& getShowSeats() const {
        return showSeats;
    }

    Payment* getPayment() const {
        return payment;
    }

    string getBookingDetails() const;
};

int Booking::nextBookingId = 1001;
