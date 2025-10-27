#ifndef PLAYER_HH
#define PLAYER_HH
#include <iostream>

using namespace std;

class Player
{
public:
    // constructor
    Player(const string& name);

    // methods
    string get_name();
    int get_points();
    bool has_won();
    void add_points(int pts);

private:
    // attributes
    string name_;
    int points_;
    bool has_won_;

};

#endif // PLAYER_HH
