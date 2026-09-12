#include <iostream>
#include <vector>
#include <string>
using namespace std;

class BookingService {
private:
    vector<Booking*> bookings;
    PriceCalculator priceCalculator;

public:
    BookingService()
        : priceCalculator(100.0, 150.0, 200.0) {}

    Booking* createBooking(
        Customer* customer,
        Show* show,
        const vector<string>& seatNumbers,
        Payment* payment
    ) {
        vector<ShowSeat*> selected;

        // First validate ALL requested seats.
        for (const string& requested : seatNumbers) {
            ShowSeat* found = nullptr;

            for (ShowSeat* ss : show->getAllShowSeats()) {
                if (ss->getSeat()->getSeatNumber() == requested &&
                    ss->isAvailable()) {
                    found = ss;
                    break;
                }
            }

            if (found == nullptr) {
                cout << "Booking rejected: seat " << requested
                     << " is unavailable or invalid.\n";
                return nullptr;
            }

            selected.push_back(found);
        }

        double amount = priceCalculator.calculatePrice(selected);

        if (payment == nullptr || !payment->pay(amount)) {
            cout << "Payment failed. Seats remain AVAILABLE.\n";
            return nullptr;
        }

        Booking* booking =
            new Booking(customer, show, selected, payment);

        booking->setTotalAmount(amount);

        for (ShowSeat* ss : selected)
            ss->book();

        bookings.push_back(booking);
        return booking;
    }

    bool cancelBooking(int bookingId) {
        for (Booking* booking : bookings) {
            if (booking->getBookingId() == bookingId &&
                booking->getStatus() == "CONFIRMED") {
                booking->cancelBooking();
                cout << "Booking cancelled successfully. "
                     << "Seats are AVAILABLE again.\n";
                return true;
            }
        }

        cout << "Booking not found or already cancelled.\n";
        return false;
    }

    void processBooking(
        Customer* customer,
        Show* show,
        const vector<string>& seatNumbers,
        Payment* payment
    ) {
        Booking* booking =
            createBooking(customer, show, seatNumbers, payment);

        if (booking == nullptr)
            return;

        booking->confirmBooking();

        TicketPrinter printer;
        printer.printTicket(booking);
    }

    vector<Booking*> getBookings() const {
        return bookings;
    }
};
