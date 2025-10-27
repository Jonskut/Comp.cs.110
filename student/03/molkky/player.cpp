#include "player.hh"
#include <iostream>

using namespace std;

Player::Player(const string& name):
    name_(name)
{
    points_ = 0;
}

string Player::get_name()
{
    return name_;
}

int Player::get_points()
{
    return points_;
}

bool Player::has_won()
{
    return points_ == 50;
}

void Player::add_points(int pts)
{
    if ( (points_ + pts) < 50 )
    {
        points_ += pts;
    }
    else if ( points_ + pts == 50 && pts >= 0 )
    {
        points_ += pts;
    }
    else
    {
        points_ = 25;
        cout << get_name() << " gets penalty points!" << endl;

    }

}
