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
// and .push_back() everything before it to a vector.
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
vector< unsigned int > get_input(string line)
{
    vector< string > separated = split(line);
    vector< unsigned int > values;

    for ( unsigned int i = 0; i < separated.size(); ++i ) {
        values.push_back(stoi_with_check(separated.at(i)));
    }
    return values;
}


// Checks if the path is clear.
// Returns true if path is clear and false if not.
// Will check in three parts:
// - First if the path is clear to the second column.
// - Second if the path is clear to the correct row.
// - Third if the path is clear to the correct column.
bool is_clear_path(vector<vector<Slot_type>>& board, const vector< unsigned int >& input)
{
    int distance_from_y_axis = 2 - input.at(0);
    bool path_to_second;
    // Checks path on the initial axis.
    // path_to_second will be true if path is clear to the second column.
    if ( distance_from_y_axis == 0 ) {
        // you are already on the y-axis
        path_to_second = true;
    } else if ( ( distance_from_y_axis == 1 ) or
                ( distance_from_y_axis == -1 ) ) {
        // you are right next to the y-axis
        if ( board.at(input.at(1) - 1).at(1) == EMPTY ) {
            path_to_second = true;
        } else {
            path_to_second = false;
        }
    } else {
        // you are on either places of the 4th column
        if ( input.at(1) == input.at(3) and
             input.at(2) == 3 ) {
            // Special case when there is no need to go to the 2nd column at all.
            if ( board.at(input.at(1) - 1).at(2) == EMPTY ) {
                return true;
            } else {
                return false;
            }
        } else {
            if  (( board.at(input.at(1) - 1).at(1) == EMPTY ) and
                 ( board.at(input.at(1) - 1).at(2) == EMPTY )) {
                 path_to_second = true;
            } else {
                 path_to_second = false;
            }
        }
    }

    bool path_to_row;
    if ( input.at(1) == input.at(3) ) {
        // No need to move vertically
        path_to_row = true;
    } else if ( input.at(1) < input.at(3) ) {
        // Go down. Iterates trough the spaces and
        // returns false if at any point the path is blocked.
        for ( unsigned int i = input.at(1); i <= input.at(3) - 1; ++i ) {
            if ( board.at(i).at(1) != EMPTY ) {
                return false;
            } else {
                path_to_row = true;
            }
        }
    } else {
        // Go up. Iterates trough the spaces and returns
        // false if at any point the path is blocked.
        if ( input.at(1) - input.at(3) == 1 ) {
            path_to_row = true;
        } else {
            for ( unsigned int i = input.at(1) - 2; i >= input.at(3); --i ) {
                if ( board.at(i).at(1) != EMPTY ) {
                    return false;
                } else {
                    path_to_row = true;
                }
            }
        }
    }

    bool path_to_column;
    if ( input.at(2) == 2 ) {
        // No need to move horizontally
        path_to_column = true;
    } else if ( input.at(2) < 2 ) {
        // Move left
        for ( int i = 0; i >= 0; --i ) {
            if ( board.at(input.at(3) - 1).at(i) != EMPTY) {
                return false;
            } else {
                path_to_column = true;
            }
        }
    } else {
        // Move right
        for ( unsigned int i = 2; i <= input.at(2) - 1; ++i ) {
            if ( board.at(input.at(3) - 1).at(i) != EMPTY) {
                return false;
            } else {
                path_to_column = true;
            }
        }
    }


    if ( path_to_second and path_to_row and path_to_column ) {
        return true;
    } else {
        return false;
    }
}


// After given valid input, moves the pieces to assigned location on board.
// Checks the path before moving.
// Will print out error and end function if the path is not clear.
void move(vector<vector<Slot_type>>& board, const vector< unsigned int >& input)
{
    Slot_type color = board.at(input.at(1) - 1).at(input.at(0) - 1);
    board.at(input.at(1) - 1).at(input.at(0) - 1) = EMPTY;
    board.at(input.at(3) - 1).at(input.at(2) - 1) = color;
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

    vector< vector< Slot_type > > finished = {
        {RED, RED, RED, RED},
        {UNUSED, EMPTY, UNUSED, UNUSED},
        {UNUSED, EMPTY, EMPTY, UNUSED},
        {UNUSED, EMPTY, UNUSED, UNUSED},
        {GREEN, GREEN, GREEN, GREEN}
    };

    print(playground);

    vector< unsigned int > values;
    unsigned int moves = 0;

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
        if ( values.at(0) <= 0 or values.at(0) > COLUMS or
             values.at(1) <= 0 or values.at(1) > ROWS or
             values.at(2) <= 0 or values.at(2) > COLUMS or
             values.at(3) <= 0 or values.at(3) > ROWS ) {
            cout << INVALID_POINT << endl;
            continue;
        }

        // Checks if the given points are valid.
        // -1 in if statements because the values are the board values
        // and must be turned to indexes.
        if ( playground.at(values.at(1) - 1).at(values.at(0) - 1) != GREEN and
             playground.at(values.at(1) - 1).at(values.at(0) - 1) != RED ) {
            cout << INVALID_POINT << endl;
            continue;
        } else if ( playground.at(values.at(3) - 1).at(values.at(2) - 1) != EMPTY ) {
            cout << INVALID_POINT << endl;
            continue;
        } else {
            // Checks if there is a path from start to end.
            if ( not is_clear_path(playground, values) ) {
                cout << CANNOT_MOVE << endl;
                continue;
            } else {
                move(playground, values);
                moves += 1;
            }
        }
        print(playground);
        if ( playground == finished ) {
            cout << GAME_OVER << endl;
            break;
        }
    }
    cout << moves << MOVES_MADE << endl;
    return 0;
}
