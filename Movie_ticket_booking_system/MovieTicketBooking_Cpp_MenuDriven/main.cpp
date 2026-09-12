#include "01_Movie.cpp"
#include "02_Seat.cpp"
#include "06_ShowSeat.cpp"
#include "03_Screen.cpp"
#include "04_Cinema.cpp"
#include "05_Show.cpp"
#include "07_Customer.cpp"
#include "09_Payment.cpp"
#include "10_PaymentTypes.cpp"
#include "11_PriceCalculator.cpp"
#include "08_Booking.cpp"
#include "12_TicketPrinter.cpp"
#include "13_BookingService.cpp"
#include "14_CinemaMenu.cpp"

#include <iostream>
#include <vector>
using namespace std;

int main() {

    // Cinema and Screen demonstrate composition.
    Cinema cinema(1, "City Cinema");

    Screen* screen1 = new Screen(1, 1);
    cinema.addScreen(screen1);

    // Physical seats belong to the Screen.
    Seat* a1 = new Seat(1, "A1", "SILVER");
    Seat* a2 = new Seat(2, "A2", "GOLD");
    Seat* a3 = new Seat(3, "A3", "PLATINUM");
    Seat* a4 = new Seat(4, "A4", "SILVER");

    screen1->addSeat(a1);
    screen1->addSeat(a2);
    screen1->addSeat(a3);
    screen1->addSeat(a4);

    // Movies
    Movie* movie1 = new Movie(1, "Spider-Man", "English", 170);
    Movie* movie2 = new Movie(2, "Avengers", "English", 148);
    Movie* movie3 = new Movie(3, "Hanuman Ansh", "Hindi", 161);
    Movie* movie4 = new Movie(4, "Hai Jawani Toh Ishq Hona Hai", "Hindi", 169);

    vector<Movie*> movies = {
        movie1, movie2, movie3, movie4
    };

    // Shows
    Show* show1 = new Show(1, "18:00", movie1, screen1);
    Show* show2 = new Show(2, "21:00", movie2, screen1);
    Show* show3 = new Show(3, "15:00", movie3, screen1);
    Show* show4 = new Show(4, "21:30", movie4, screen1);

    // Show 1 seats
    show1->addShowSeat(new ShowSeat(1, a1));
    show1->addShowSeat(new ShowSeat(2, a2));
    show1->addShowSeat(new ShowSeat(3, a3));
    show1->addShowSeat(new ShowSeat(4, a4));

    // Show 2 seats
    show2->addShowSeat(new ShowSeat(5, a1));
    show2->addShowSeat(new ShowSeat(6, a2));
    show2->addShowSeat(new ShowSeat(7, a3));
    show2->addShowSeat(new ShowSeat(8, a4));

    // Show 3 seats
    show3->addShowSeat(new ShowSeat(9, a1));
    show3->addShowSeat(new ShowSeat(10, a2));
    show3->addShowSeat(new ShowSeat(11, a3));
    show3->addShowSeat(new ShowSeat(12, a4));

    // Show 4 seats
    show4->addShowSeat(new ShowSeat(13, a1));
    show4->addShowSeat(new ShowSeat(14, a2));
    show4->addShowSeat(new ShowSeat(15, a3));
    show4->addShowSeat(new ShowSeat(16, a4));

    // All four shows
    vector<Show*> shows = {
        show1, show2, show3, show4
    };

    Customer customer(1, "Customer", "9999999999");

    BookingService bookingService;

    // Menu-driven application
    CinemaMenu menu(
        cinema,
        movies,
        shows,
        customer,
        bookingService
    );

    menu.run();

    // Clean-up ShowSeats
    for (ShowSeat* ss : show1->getAllShowSeats())
        delete ss;

    for (ShowSeat* ss : show2->getAllShowSeats())
        delete ss;

    for (ShowSeat* ss : show3->getAllShowSeats())
        delete ss;

    for (ShowSeat* ss : show4->getAllShowSeats())
        delete ss;

    // Clean-up Shows
    delete show1;
    delete show2;
    delete show3;
    delete show4;

    // Clean-up Movies
    delete movie1;
    delete movie2;
    delete movie3;
    delete movie4;

    // Clean-up Seats
    delete a1;
    delete a2;
    delete a3;
    delete a4;

    delete screen1;

    return 0;
}