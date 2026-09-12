#include <iostream>
#include <string>
using namespace std;

class Movie {
private:
    int movieId;
    string title;
    string language;
    int durationMins;

public:
    Movie(int id, string t, string lang, int duration)
        : movieId(id), title(t), language(lang), durationMins(duration) {}

    string getDetails() const {
        return to_string(movieId) + ". " + title + " | " +
               language + " | " + to_string(durationMins) + " mins";
    }

    int getMovieId() const { return movieId; }
    string getTitle() const { return title; }
};
