#include <string>
#include <vector>
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
    Show(int id, const string& time, Movie* selectedMovie, Screen* selectedScreen)
        : showId(id), startTime(time), movie(selectedMovie), screen(selectedScreen) {}

    void addShowSeat(ShowSeat* showSeat) {
        showSeats.push_back(showSeat);
    }

    string getShowDetails() const;

    vector<ShowSeat*> getAvailableSeats() const;

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
