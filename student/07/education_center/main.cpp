/* Education center
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
 *
 * */

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

const string ERROR_TEXT = "Error: the input file cannot be opened";

struct Course {
    string theme;
    string name;
    int enrollments;
};

// Implement the commands as functions
string split(string& text)
{
    string::size_type iter = text.find(";");
    string word;
    if ( iter != string::npos ) {
        word = text.substr(0, iter);
        text.erase(0, iter + 1);
    } else {
        if ( text == "full" ) {
            return "50";
        } else {
            return text;
        }
    }
    return word;
}


int main()
{
    map< string, Course > centre;

    string input;
    cout << "Input file: ";
    getline(cin, input);

    ifstream input_file(input);
    if ( !input_file ) {
        cout << ERROR_TEXT << endl;
        return EXIT_FAILURE;
    } else {
        // Read lines over input data and save to "centre"
        // in format centre.at(location).theme = theme_of_the_course
        // centre.at(location).name = name_of_the_course
        // centre.at(location).enrollments = amount_of_enrollments_in_the_course
        string line;
        Course info;
        while ( getline(input_file, line) ) {
            string location = split(line);
            string theme = split(line);
            string course_name = split(line);
            int enrollments = stoi(split(line));
            info = {theme, course_name, enrollments};

            centre.insert( {location, info} );



        }
        map< string, Course >::iterator iter;
        iter = centre.begin();
        while ( iter != centre.end() ) {
            cout << iter->first << iter->second.name << endl;
            ++iter;
        }

    }

    return 0;
}


