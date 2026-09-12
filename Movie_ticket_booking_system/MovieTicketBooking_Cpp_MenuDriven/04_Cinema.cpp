#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Screen;

class Cinema {
private:
    int cinemaId;
    string name;
    vector<Screen*> screens;

public:
    Cinema(int id, string n) : cinemaId(id), name(n) {}

    void addScreen(Screen* screen) {
        screens.push_back(screen);
    }

    vector<Screen*> getScreens() const {
        return screens;
    }

    string getName() const { return name; }
};
