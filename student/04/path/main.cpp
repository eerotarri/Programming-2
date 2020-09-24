/* Path
 *
 * Desc:
 *  This program generates a Path puzzle. The board is ROWS x COLUMNS (5x4),
 * and every round the player chooses a source point and a target point
 * (totally four numbers), making the given button to be moved to the target
 * position (if possible). The game checks if the user-given move can be made.
 *  At start all green buttons are on the top row, and all red buttons are on
 * the bottom row. Game will end when all green buttons have been moved to the
 * bottom row, and all red buttons to the top row. It is not allowed to move a
 * button over another button.
 *  When printing the game board, green button is represented by 'G', red
 * button by 'R', empty hole by 'o', and unused position by empty space.
 *
 * Program author
 * Name: Eero Tarri
 * Student number: 283568
 * UserID: tarri
 * E-Mail: eero.tarri@tuni.fi
 * Feedback language (fi/en): fi
 *
 * Notes about the program and it's implementation:
 *
 * */

#include <iostream>
#include <vector>

using namespace std;

enum Slot_type {RED, GREEN, EMPTY, UNUSED};
const unsigned int ROWS = 5;
const unsigned int COLUMS = 4;

const string INPUT_TEXT = "Enter start point (x, y) and destination point (x, y), or q to quit: ";
const string INVALID_POINT = "Invalid start/destination point.";
const string CANNOT_MOVE = "There is no path between start point and destination point.";
const string GAME_OVER = "Game over. Congratulations!";
const string MOVES_MADE = " move(s) made.";

// Prints the grid
void print(const vector< vector< Slot_type >>& g)
{
    cout << "===============" << endl;
    cout << "|   | 1 2 3 4 |" << endl;
    cout << "---------------" << endl;
    for(unsigned int i = 0; i < ROWS; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < COLUMS; ++j)
        {
            switch(g.at(i).at(j))
            {
            case GREEN: cout << "G "; break;
            case RED: cout << "R "; break;
            case EMPTY: cout << "o "; break;
            case UNUSED: cout << "  "; break;
            }
        }
        cout << "|" << endl;
    }
    cout << "===============" << endl;
}


// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns 0.
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}


// Turns the numbers in input into a vector
// by searching the first separator (" ").
// and saving everything before it to a vector.
// Returns the vector containing the input values as strings.
vector< string > split(string text)
{
    vector<string> separated_line = { };
    string::size_type i = 0;

    while ( text != "" ) {
        i = text.find(" ");
        if ( i != 0 ) {
            separated_line.push_back(text.substr(0, i));
            text.erase(0, i);
        } else if ( i == string::npos ) {
            separated_line.push_back(text.substr(0, text.length()));
        }
        text.erase(0, 1);
    }
    return separated_line;
}


// Takes the user input as parameter.
// Turns the user input into a vector or integer values.
// Returns the vector of input values.
vector< int > get_input(string line)
{
    vector< string > separated = split(line);
    vector< int > values;

    for ( unsigned int i = 0; i < separated.size(); ++i ) {
        values.push_back(stoi_with_check(separated.at(i)));
    }
    return values;
}


int main()
{
    vector< vector< Slot_type > > playground = {
        {GREEN, GREEN, GREEN, GREEN},
        {UNUSED, EMPTY, UNUSED, UNUSED},
        {UNUSED, EMPTY, EMPTY, UNUSED},
        {UNUSED, EMPTY, UNUSED, UNUSED},
        {RED, RED, RED, RED}
    };
    print(playground);

    vector< int > values;

    while ( true ) {
        string line;
        cout << INPUT_TEXT;
        getline(cin, line);

        values = get_input(line);

        // Breaks the while loop if the input is "q".
        if ( line == "q" ) {
            break;
        }

        // Checks that the values are in range.
        if ( values.at(0) <= 0 or values.at(0) > 4 or
             values.at(1) <= 0 or values.at(1) > 5 or
             values.at(2) <= 0 or values.at(2) > 4 or
             values.at(3) <= 0 or values.at(3) > 5 ) {
            cout << INVALID_POINT << endl;
            continue;
        }

        // Checks if the given points are valid.
        if ( playground.at(values.at(1) - 1).at(values.at(0) - 1) != GREEN and
             playground.at(values.at(1) - 1).at(values.at(0) - 1) != RED ) {
            cout << INVALID_POINT << endl;
            continue;
        } else if ( playground.at(values.at(3) - 1).at(values.at(2) - 1) != EMPTY ) {
            cout << INVALID_POINT << endl;
            continue;
        }
    }
    return 0;
}
