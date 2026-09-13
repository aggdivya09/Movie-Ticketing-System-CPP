#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Movie {
private:
    int movieId;
    string title;
    string language;
    int durationMins;

public:
    Movie(int id, const string& movieTitle, const string& movieLanguage, int duration)
        : movieId(id), title(movieTitle), language(movieLanguage), durationMins(duration) {}

    string getDetails() const {
        return to_string(movieId) + ". " + title + " | " + language +
               " | " + to_string(durationMins) + " mins";
    }

    string getTitle() const { return title; }
};

class Seat {
private:
    int seatId;
    string seatNumber;
    string category;

public:
    Seat(int id, const string& number, const string& type)
        : seatId(id), seatNumber(number), category(type) {}

    string getSeatNumber() const { return seatNumber; }
    string getCategory() const { return category; }
};

class ShowSeat {
private:
    int showSeatId;
    Seat* seat;
    string status;

public:
    ShowSeat(int id, Seat* selectedSeat)
        : showSeatId(id), seat(selectedSeat), status("AVAILABLE") {}

    bool isAvailable() const {
        return status == "AVAILABLE";
    }

    void book() {
        status = "BOOKED";
    }

    void release() {
        status = "AVAILABLE";
    }

    Seat* getSeat() const { return seat; }
    string getStatus() const { return status; }
};

class Screen {
private:
    int screenId;
    int screenNumber;
    vector<Seat*> seats;

public:
    Screen(int id, int number)
        : screenId(id), screenNumber(number) {}

    void addSeat(Seat* seat) {
        seats.push_back(seat);
    }

    int getScreenNumber() const {
        return screenNumber;
    }
};

class Cinema {
private:
    int cinemaId;
    string name;
    vector<Screen*> screens;

public:
    Cinema(int id, const string& cinemaName)
        : cinemaId(id), name(cinemaName) {}

    void addScreen(Screen* screen) {
        screens.push_back(screen);
    }
};

class Show {
private:
    int showId;
    string startTime;
    Movie* movie;
    Screen* screen;
    vector<ShowSeat*> showSeats;

public:
    Show(int id, const string& time, Movie* selectedMovie, Screen* selectedScreen)
        : showId(id), startTime(time),
          movie(selectedMovie), screen(selectedScreen) {}

    void addShowSeat(ShowSeat* showSeat) {
        showSeats.push_back(showSeat);
    }

    string getShowDetails() const {
        return "Show ID: " + to_string(showId) +
               " | Time: " + startTime +
               " | Movie: " + movie->getTitle() +
               " | Screen: " + to_string(screen->getScreenNumber());
    }

    const vector<ShowSeat*>& getAllShowSeats() const {
        return showSeats;
    }

    int getShowId() const {
        return showId;
    }

    Movie* getMovie() const {
        return movie;
    }

    Screen* getScreen() const {
        return screen;
    }
};

class Customer {
private:
    int customerId;
    string name;
    string phone;

public:
    Customer(int id, const string& customerName, const string& customerPhone)
        : customerId(id), name(customerName), phone(customerPhone) {}

    string getName() const {
        return name;
    }
};

class Payment {
protected:
    double amount;

public:
    Payment() : amount(0.0) {}
    virtual ~Payment() = default;

    virtual bool pay(double paymentAmount) = 0;
};

class UpiPayment : public Payment {
private:
    string upiId;

public:
    UpiPayment(const string& id)
        : upiId(id) {}

    bool pay(double paymentAmount) override {
        amount = paymentAmount;
        return true;
    }
};

class CardPayment : public Payment {
private:
    string cardNumber;

public:
    CardPayment(const string& number)
        : cardNumber(number) {}

    bool pay(double paymentAmount) override {
        amount = paymentAmount;
        return true;
    }
};

class CashPayment : public Payment {
public:
    bool pay(double paymentAmount) override {
        amount = paymentAmount;
        return true;
    }
};

class PriceCalculator {
private:
    double silverPrice;
    double goldPrice;
    double platinumPrice;

public:
    PriceCalculator(double silver, double gold, double platinum)
        : silverPrice(silver),
          goldPrice(gold),
          platinumPrice(platinum) {}

    double calculatePrice(
        const vector<ShowSeat*>& seats) const {

        double total = 0.0;

        for (ShowSeat* showSeat : seats) {

            string category =
                showSeat->getSeat()->getCategory();

            if (category == "SILVER")
                total += silverPrice;

            else if (category == "GOLD")
                total += goldPrice;

            else if (category == "PLATINUM")
                total += platinumPrice;
        }

        return total;
    }

    double calculatePrice(
        int quantity,
        double pricePerSeat) const {

        return quantity * pricePerSeat;
    }
};

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
    Booking(
        Customer* selectedCustomer,
        Show* selectedShow,
        const vector<ShowSeat*>& selectedSeats,
        Payment* selectedPayment
    )
        : bookingId(nextBookingId++),
          customer(selectedCustomer),
          show(selectedShow),
          showSeats(selectedSeats),
          payment(selectedPayment),
          totalAmount(0.0),
          status("PENDING") {}

    void setTotalAmount(double amountValue) {
        totalAmount = amountValue;
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

    string getStatus() const {
        return status;
    }

    Customer* getCustomer() const {
        return customer;
    }

    string getBookingDetails() const {

        string result =
            "Booking ID: " + to_string(bookingId) +
            " | Movie: " + show->getMovie()->getTitle() +
            " | Screen: " +
            to_string(show->getScreen()->getScreenNumber()) +
            " | Time: ";

        result += "See show listing";
        result += " | Seats: ";

        for (size_t i = 0; i < showSeats.size(); ++i) {

            result +=
                showSeats[i]->getSeat()->getSeatNumber();

            if (i + 1 < showSeats.size())
                result += ", ";
        }

        result +=
            " | Amount: Rs. " +
            to_string(static_cast<int>(totalAmount));

        result +=
            " | Status: " + status;

        return result;
    }
};

int Booking::nextBookingId = 1001;

class TicketPrinter {
public:
    void printTicket(Booking* booking) const {

        cout << "\n========== TICKET ==========\n";
        cout << booking->getBookingDetails() << "\n";
        cout << "============================\n";
    }
};

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

    void processBooking(
        Customer* customer,
        Show* show,
        const vector<string>& seatNumbers,
        Payment* payment
    ) {

        vector<ShowSeat*> selected;

        for (const string& requested : seatNumbers) {

            ShowSeat* found = nullptr;

            for (ShowSeat* showSeat :
                 show->getAllShowSeats()) {

                if (showSeat->getSeat()->getSeatNumber()
                    == requested) {

                    if (!showSeat->isAvailable()) {

                        cout << "Booking rejected: seat "
                             << requested
                             << " is already BOOKED.\n";

                        delete payment;
                        return;
                    }

                    found = showSeat;
                    break;
                }
            }

            if (found == nullptr) {

                cout << "Booking rejected: seat "
                     << requested
                     << " is invalid.\n";

                delete payment;
                return;
            }

            selected.push_back(found);
        }

        double amount =
            priceCalculator.calculatePrice(selected);

        if (payment == nullptr ||
            !payment->pay(amount)) {

            cout << "Payment failed. "
                 << "Seats remain AVAILABLE.\n";

            delete payment;
            return;
        }

        Booking* booking =
            new Booking(
                customer,
                show,
                selected,
                payment
            );

        booking->setTotalAmount(amount);

        for (ShowSeat* showSeat : selected)
            showSeat->book();

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
    }

    int readInt(const string& message) {

        int value;

        while (true) {

            cout << message;

            if (cin >> value)
                return value;

            cout << "Invalid input. "
                 << "Please enter a number.\n";

            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    Show* findShow(int showId) {

        for (Show* show : shows) {

            if (show->getShowId() == showId)
                return show;
        }

        return nullptr;
    }

    string normalizeSeatNumber(
        const string& seatNumber) const {

        if (seatNumber.size() == 1 &&
            seatNumber[0] >= '1' &&
            seatNumber[0] <= '4') {

            return "A" + seatNumber;
        }

        return seatNumber;
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

        int showId =
            readInt("Enter Show ID: ");

        Show* show =
            findShow(showId);

        if (show == nullptr) {

            cout << "Show not found.\n";
            return;
        }

        cout << "\nSeats for Show "
             << showId << ":\n";

        for (ShowSeat* showSeat :
             show->getAllShowSeats()) {

            cout << showSeat->getSeat()->getSeatNumber()
                 << " [" << showSeat->getSeat()->getCategory()
                 << "] - "
                 << showSeat->getStatus() << "\n";
        }
    }

    void bookTicket() {

        int showId =
            readInt("Enter Show ID: ");

        Show* show =
            findShow(showId);

        if (show == nullptr) {

            cout << "Show not found.\n";
            return;
        }

        cout << "Enter seat number "
             << "(1-4 or A1-A4): ";

        cin >> input;

        string seatNumber =
            normalizeSeatNumber(input);

        bool seatFound = false;

        for (ShowSeat* showSeat :
             show->getAllShowSeats()) {

            if (showSeat->getSeat()->getSeatNumber()
                == seatNumber) {

                seatFound = true;

                if (!showSeat->isAvailable()) {

                    cout << "Seat is already BOOKED. "
                         << "Booking rejected.\n";

                    return;
                }

                break;
            }
        }

        if (!seatFound) {

            cout << "Invalid seat number. "
                 << "Booking rejected.\n";

            return;
        }

        int paymentChoice =
            readInt(
                "Payment (1-UPI, 2-Card, 3-Cash): "
            );

        Payment* payment = nullptr;

        if (paymentChoice == 1) {

            string upiId;

            cout << "Enter UPI ID: ";
            cin >> upiId;

            payment =
                new UpiPayment(upiId);
        }

        else if (paymentChoice == 2) {

            string cardNumber;

            cout << "Enter card number: ";
            cin >> cardNumber;

            payment =
                new CardPayment(cardNumber);
        }

        else if (paymentChoice == 3) {

            payment =
                new CashPayment();
        }

        else {

            cout << "Invalid payment choice. "
                 << "Booking rejected.\n";

            return;
        }

        vector<string> seats =
            {seatNumber};

        bookingService.processBooking(
            &customer,
            show,
            seats,
            payment
        );
    }

    void cancelBooking() {

        int bookingId =
            readInt("Enter Booking ID: ");

        bookingService.cancelBooking(
            bookingId
        );
    }

    void viewBookings() const {

        cout << "\n-------- MY BOOKINGS --------\n";

        bool found = false;

        for (Booking* booking :
             bookingService.getBookings()) {

            if (booking->getCustomer()
                == &customer) {

                cout << booking->getBookingDetails()
                     << "\n";

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
        : choice(0),
          cinema(c),
          movies(movieList),
          shows(showList),
          customer(cust),
          bookingService(service) {}

    void run() {

        do {

            displayMenu();

            choice =
                readInt("Enter choice: ");

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
                    cout
                        << "Thank you for using the "
                        << "Cinema Booking System.\n";
                    break;

                default:
                    cout
                        << "Invalid choice. "
                        << "Please try again.\n";
            }

        } while (choice != 7);
    }
};

int main() {

    Cinema cinema(
        1,
        "City Cinema"
    );

    Screen* screen1 =
        new Screen(1, 1);

    cinema.addScreen(screen1);

    Seat* a1 =
        new Seat(1, "A1", "SILVER");

    Seat* a2 =
        new Seat(2, "A2", "GOLD");

    Seat* a3 =
        new Seat(3, "A3", "PLATINUM");

    Seat* a4 =
        new Seat(4, "A4", "SILVER");

    screen1->addSeat(a1);
    screen1->addSeat(a2);
    screen1->addSeat(a3);
    screen1->addSeat(a4);

    Movie* movie1 =
        new Movie(
            1,
            "Spider-Man",
            "English",
            170
        );

    Movie* movie2 =
        new Movie(
            2,
            "Avengers",
            "English",
            148
        );

    Movie* movie3 =
        new Movie(
            3,
            "Hanuman Ansh",
            "Hindi",
            161
        );

    Movie* movie4 =
        new Movie(
            4,
            "Hai Jawani Toh Ishq Hona Hai",
            "Hindi",
            169
        );

    vector<Movie*> movies =
        {
            movie1,
            movie2,
            movie3,
            movie4
        };

    Show* show1 =
        new Show(
            1,
            "18:00",
            movie1,
            screen1
        );

    Show* show2 =
        new Show(
            2,
            "21:00",
            movie2,
            screen1
        );

    Show* show3 =
        new Show(
            3,
            "15:00",
            movie3,
            screen1
        );

    Show* show4 =
        new Show(
            4,
            "21:30",
            movie4,
            screen1
        );

    show1->addShowSeat(
        new ShowSeat(1, a1)
    );

    show1->addShowSeat(
        new ShowSeat(2, a2)
    );

    show1->addShowSeat(
        new ShowSeat(3, a3)
    );

    show1->addShowSeat(
        new ShowSeat(4, a4)
    );

    show2->addShowSeat(
        new ShowSeat(5, a1)
    );

    show2->addShowSeat(
        new ShowSeat(6, a2)
    );

    show2->addShowSeat(
        new ShowSeat(7, a3)
    );

    show2->addShowSeat(
        new ShowSeat(8, a4)
    );

    show3->addShowSeat(
        new ShowSeat(9, a1)
    );

    show3->addShowSeat(
        new ShowSeat(10, a2)
    );

    show3->addShowSeat(
        new ShowSeat(11, a3)
    );

    show3->addShowSeat(
        new ShowSeat(12, a4)
    );

    show4->addShowSeat(
        new ShowSeat(13, a1)
    );

    show4->addShowSeat(
        new ShowSeat(14, a2)
    );

    show4->addShowSeat(
        new ShowSeat(15, a3)
    );

    show4->addShowSeat(
        new ShowSeat(16, a4)
    );

    vector<Show*> shows =
        {
            show1,
            show2,
            show3,
            show4
        };

    Customer customer(
        1,
        "Customer",
        "9999999999"
    );

    BookingService bookingService;

    CinemaMenu menu(
        cinema,
        movies,
        shows,
        customer,
        bookingService
    );

    menu.run();

    for (ShowSeat* seat :
         show1->getAllShowSeats())
        delete seat;

    for (ShowSeat* seat :
         show2->getAllShowSeats())
        delete seat;

    for (ShowSeat* seat :
         show3->getAllShowSeats())
        delete seat;

    for (ShowSeat* seat :
         show4->getAllShowSeats())
        delete seat;

    delete show1;
    delete show2;
    delete show3;
    delete show4;

    delete movie1;
    delete movie2;
    delete movie3;
    delete movie4;

    delete a1;
    delete a2;
    delete a3;
    delete a4;

    delete screen1;

    return 0;
}
