#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>
#include <iostream>
using namespace std;

class Player
{
public:
    Player(string name);
    string get_name();
    void add_points(int points);
    bool has_won();
    int get_points();


private:
    string name_;
    int points_= 0;
};

#endif // PLAYER_HH
