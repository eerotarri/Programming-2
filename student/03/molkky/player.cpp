#include "player.hh"

Player::Player(string name):
    name_(name)
{
}

string Player::get_name()
{
    return name_;
}

void Player::add_points(int points)
{
    points_ += points;
    if ( points_ > 50 ) {
        points_ = 25;
        cout << name_ << " gets penalty points!" << endl;
    }
}

bool Player::has_won()
{
    if ( points_ == 50 ) {
        return true;
    } else {
        return false;
    }
}

int Player::get_points()
{
    return points_;
}
