#include <string>
#include <vector>
using namespace std;

class Screen;

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

    const vector<Screen*>& getScreens() const {
        return screens;
    }

    string getName() const {
        return name;
    }
};
