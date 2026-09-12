#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Movie;
class Screen;
class ShowSeat;

class Show {
private:
    int showId;
    string startTime;
    Movie* movie;
    Screen* screen;
    vector<ShowSeat*> showSeats;

public:
    Show(int id, string time, Movie* m, Screen* s)
        : showId(id), startTime(time), movie(m), screen(s) {}

    void addShowSeat(ShowSeat* showSeat) {
        showSeats.push_back(showSeat);
    }

    string getShowDetails() const;

    vector<ShowSeat*> getAvailableSeats() const {
        vector<ShowSeat*> available;
        for (ShowSeat* ss : showSeats) {
            if (ss->isAvailable())
                available.push_back(ss);
        }
        return available;
    }

    vector<ShowSeat*> getAllShowSeats() const {
        return showSeats;
    }

    int getShowId() const { return showId; }
    string getStartTime() const { return startTime; }
    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
};

string Show::getShowDetails() const {
    return "Show ID: " + to_string(showId) +
           " | Time: " + startTime +
           " | Movie: " + movie->getTitle() +
           " | Screen: " + to_string(screen->getScreenNumber());
}
