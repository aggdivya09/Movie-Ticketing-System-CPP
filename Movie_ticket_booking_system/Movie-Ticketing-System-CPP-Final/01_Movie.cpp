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

    int getMovieId() const { return movieId; }
    string getTitle() const { return title; }
};
