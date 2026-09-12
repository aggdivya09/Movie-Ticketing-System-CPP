#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

class CinemaMenu {
private:
    int choice;
    string input;

    Cinema& cinema;
    vector<Movie*>& movies;
    vector<Show*>& shows;
    Customer& customer;
    BookingService& bookingService;

    void displayMenu() const {
        cout << "\n========== CINEMA MENU ==========\n";
        cout << "1. List Movies\n";
        cout << "2. View Shows\n";
        cout << "3. View Seats\n";
        cout << "4. Book Ticket\n";
        cout << "5. Cancel Booking\n";
        cout << "6. View My Bookings\n";
        cout << "7. Exit\n";
        cout << "=================================\n";
        cout << "Enter choice: ";
    }

    int readInt(const string& message) {
        int value;

        while (true) {
            cout << message;

            if (cin >> value)
                return value;

            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    Show* findShow(int showId) {
        for (Show* show : shows) {
            if (show->getShowId() == showId)
                return show;
        }
        return nullptr;
    }

    void listMovies() const {
        cout << "\n---------- MOVIES ----------\n";
        for (Movie* movie : movies)
            cout << movie->getDetails() << "\n";
    }

    void viewShows() const {
        cout << "\n----------- SHOWS -----------\n";
        for (Show* show : shows)
            cout << show->getShowDetails() << "\n";
    }

    void viewSeats() {
        int showId = readInt("Enter Show ID: ");
        Show* show = findShow(showId);

        if (show == nullptr) {
            cout << "Show not found.\n";
            return;
        }

        cout << "\nSeats for Show " << showId << ":\n";

        for (ShowSeat* ss : show->getAllShowSeats()) {
            cout << ss->getSeat()->getSeatNumber()
                 << " [" << ss->getSeat()->getCategory() << "] - "
                 << ss->getStatus() << "\n";
        }
    }

    void bookTicket() {
        int showId = readInt("Enter Show ID: ");
        Show* show = findShow(showId);

        if (show == nullptr) {
            cout << "Show not found.\n";
            return;
        }

        string seatNumber;
        cout << "Enter seat number: ";
        cin >> seatNumber;

        for (ShowSeat* ss : show->getAllShowSeats()) {
            if (ss->getSeat()->getSeatNumber() == seatNumber &&
                !ss->isAvailable()) {
                cout << "Seat is already BOOKED. Booking rejected.\n";
                return;
            }
        }

        int paymentChoice =
            readInt("Payment (1-UPI, 2-Card, 3-Cash): ");

        Payment* payment = nullptr;

        if (paymentChoice == 1) {
            string upiId;
            cout << "Enter UPI ID: ";
            cin >> upiId;
            payment = new UpiPayment(upiId);
        }
        else if (paymentChoice == 2) {
            string cardNumber;
            cout << "Enter card number: ";
            cin >> cardNumber;
            payment = new CardPayment(cardNumber);
        }
        else if (paymentChoice == 3) {
            payment = new CashPayment();
        }
        else {
            cout << "Invalid payment choice.\n";
            return;
        }

        vector<string> seats = {seatNumber};
        customer.bookTicket(showId, seats);
        bookingService.processBooking(
            &customer, show, seats, payment
        );

        delete payment;
    }

    void cancelBooking() {
        int bookingId = readInt("Enter Booking ID: ");
        customer.cancelBooking(bookingId);
        bookingService.cancelBooking(bookingId);
    }

    void viewBookings() const {
        cout << "\n-------- MY BOOKINGS --------\n";

        bool found = false;

        for (Booking* booking : bookingService.getBookings()) {
            if (booking->getCustomer() == &customer) {
                cout << booking->getBookingDetails() << "\n";
                found = true;
            }
        }

        if (!found)
            cout << "No bookings found.\n";
    }

public:
    CinemaMenu(
        Cinema& c,
        vector<Movie*>& movieList,
        vector<Show*>& showList,
        Customer& cust,
        BookingService& service
    )
        : choice(0), cinema(c), movies(movieList),
          shows(showList), customer(cust),
          bookingService(service) {}

    void run() {
        do {
            displayMenu();
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice.\n";
                continue;
            }

            switch (choice) {
                case 1:
                    listMovies();
                    break;

                case 2:
                    viewShows();
                    break;

                case 3:
                    viewSeats();
                    break;

                case 4:
                    bookTicket();
                    break;

                case 5:
                    cancelBooking();
                    break;

                case 6:
                    viewBookings();
                    break;

                case 7:
                    cout << "Thank you for using the Cinema Booking System.\n";
                    break;

                default:
                    cout << "Invalid choice. Please try again.\n";
            }

        } while (choice != 7);
    }
};
