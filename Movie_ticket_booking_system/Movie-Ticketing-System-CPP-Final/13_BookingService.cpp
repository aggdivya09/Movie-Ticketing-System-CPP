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
        : priceCalculator(150.0, 250.0, 400.0) {}

    ~BookingService() {
        for (Booking* booking : bookings)
            delete booking;
    }

    Booking* createBooking(
        Customer* customer,
        Show* show,
        const vector<string>& seatNumbers,
        Payment* payment
    ) {
        vector<ShowSeat*> selected;

        // Validate every requested seat before making any change.
        for (const string& requested : seatNumbers) {

            ShowSeat* found = nullptr;

            for (ShowSeat* showSeat : show->getAllShowSeats()) {

                if (showSeat->getSeat()->getSeatNumber() == requested) {

                    if (!showSeat->isAvailable()) {
                        cout << "Booking rejected: seat "
                             << requested
                             << " is already BOOKED.\n";
                        return nullptr;
                    }

                    found = showSeat;
                    break;
                }
            }

            if (found == nullptr) {
                cout << "Booking rejected: seat "
                     << requested
                     << " is invalid.\n";
                return nullptr;
            }

            selected.push_back(found);
        }

        double amount =
            priceCalculator.calculatePrice(selected);

        if (payment == nullptr || !payment->pay(amount)) {
            cout << "Payment failed. Seats remain AVAILABLE.\n";
            return nullptr;
        }

        Booking* booking =
            new Booking(customer, show, selected, payment);

        booking->setTotalAmount(amount);

        for (ShowSeat* showSeat : selected)
            showSeat->book();

        return booking;
    }

    void processBooking(
        Customer* customer,
        Show* show,
        const vector<string>& seatNumbers,
        Payment* payment
    ) {
        Booking* booking =
            createBooking(customer, show, seatNumbers, payment);

        if (booking == nullptr) {
            delete payment;
            return;
        }

        booking->confirmBooking();
        bookings.push_back(booking);

        TicketPrinter printer;
        printer.printTicket(booking);
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

    const vector<Booking*>& getBookings() const {
        return bookings;
    }
};
