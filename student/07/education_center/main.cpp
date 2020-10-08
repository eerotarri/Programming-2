/* Education center
 *
 * Desc:
 *  This program generates enrollment tracking system for education center. It
 * saves information from input file in to a data structure and iterates trough
 * it according to given commands.
 *  At start program asks user for an input file. Then user gives input
 * parameters consiting of command and possible location and/or theme
 * parameters. Program will print out wanted information.
 *  Maximum amount of enrollments for one course is 50.
 *  Commands:
 * - quit: end the program.
 * - locations: prints out all possible locations
 * - courses <location> <theme>: prints all courses currently going on in given
 *                               location and theme
 * - available: prints out all available courses, which theme they belong in
 *              and in what location they are in
 * - courses_in_theme <theme>: prints out all courses belonging to a theme
 * - favorite_theme: prints out most enrolled theme(s)
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
#include <algorithm>

using namespace std;

const string FILE_ERROR = "Error: the input file cannot be opened";
const string UNKNOWN_COMMAND = "Error: Unknown command: ";
const string PARAMETER_ERROR = "Error: error in command ";
const string UNKNOWN_LOCATION = "Error: unknown location name";
const string UNKNOWN_THEME = "Error: unknown theme";
const string EMPTY_FIELD = "Error: empty field";

struct Course {
    string theme;
    string name;
    int enrollments;
};


// Splits input from file to a word
// Takes one line from input or substring of it and returns a word or all words
// before delimiter ";".
// Pararemeters:
// - text: text to be split
// Variables:
// - iter: iterator to find the position of the first char ";"
// Return value:
// - word: first word of text
string split_to_data(string& text)
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

// Splits input string into a vector consisting of strings
// Takes string as parameter to manipulate, delimiter to determine when to
// cut the string and ingnore_empty to determine if empty string are to be
// added to the vector. They are ignored by default.
// Pararemeters:
// - s: string to be split
// - delimiter: char to cut the string with
// Variables:
// - tmp: temporary variable to hold the string or substrings in
// - new_part: variable to store the first word in
// Return value:
// - result: vector consisting of input words
vector< string > split_to_vector(const string& s,
                                 const char delimiter, bool ignore_empty=true)
{
    vector<string> result;
    string tmp = s;
    // Checks first if quotes in string need to be examined
    if ( (tmp.find("\"")!=string::npos) and (tmp.back() == '\"') ) {
        for ( int i = 0; i < 2; ++i ) {
            string new_part = tmp.substr(0, tmp.find(delimiter));
            tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
            result.push_back(new_part);
        }
        result.push_back(tmp.substr(1, tmp.size()-2));
    // If there are no quotes proceeds normally
    } else {
        while(tmp.find(delimiter) != string::npos) {
            string new_part = tmp.substr(0, tmp.find(delimiter));
            tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
            if(not (ignore_empty and new_part.empty())) {
                result.push_back(new_part);
            }
        }
        if(not (ignore_empty and tmp.empty())) {
            result.push_back(tmp);
        }
    }
    return result;
}

// Checks if the input theme exists by iterating through all courses and
// searching for user input theme
// Parameters:
// - m: data structure map for examination
// - t: user input theme
// Variables:
// - found: number of times the theme was found
// Return value:
// - true if the theme exists and false otherwise
bool search_for_theme(const map< string, vector< Course > >& m, string t)
{
    int found = 0;
    for ( map< string, vector< Course >>::const_iterator it = m.begin(); it != m.end(); ++it ) {
        for ( Course c : it->second ) {
            if (c.theme == t) {
                ++found;
            }
        }
    }
    if ( found == 0 ) {
        return true;
    } else {
        return false;
    }
}

// Prints all existing locations
// Parameters:
// - m: data structure map for examination
void print_locations(const map< string, vector< Course > >& m)
{
    for ( map< string, vector< Course >>::const_iterator it = m.begin(); it != m.end(); ++it ) {
        cout << it->first << endl;
    }
}

// Prints courses and their enrollments
// Parameters:
// - c: Course for examination
void print_courses(Course c)
{
    if ( c.enrollments == 50 ) {
        cout << c.name << " --- full" << endl;
    } else {
        cout << c.name << " --- " << c.enrollments << " enrollments" << endl;
    }

}

// Prints all available courses in format:
// "location : theme : course_name"
// Parameters:
// - m: data structure map for examination
// Variables:
// - output: vector of output lines
void print_available(const map< string, vector< Course > >& m)
{
    vector< string > output = {};
    for ( map< string, vector< Course >>::const_iterator it = m.begin(); it != m.end(); ++it ) {
        for ( Course c : it->second ) {
            if ( c.enrollments != 50 ) {
                output.push_back(it->first + " : " + c.theme + " : " + c.name);
            }
        }
    }
    sort(output.begin(), output.end());
    for ( string line : output ) {
        cout << line << endl;
    }
}

// Parameters:
// - m: data structure map for examination
// - t: user input theme
// Variables:
// - output: vector of output lines
void print_courses_in_theme(const map< string, vector< Course > >& m, string t)
{
    vector< string > output = {};
    for ( map< string, vector< Course >>::const_iterator it = m.begin(); it != m.end(); ++it ) {
        for ( Course c : it->second ) {
            if ( c.theme == t ) {
                int i = 0;
                for ( string s : output ) {
                    if ( s == c.name ) {
                        ++i;
                    }
                }
                if ( i == 0 ) {
                    output.push_back(c.name);
                }
            }
        }
    }
    sort(output.begin(), output.end());
    for ( string line : output ) {
        cout << line << endl;
    }
}

// Prints most enrolled theme.
// Works in four stages:
// - First stage is making map of values
// - Second stage is finding max value of those values
// - Third stage is making vector of the themes that have the maximum values
// - Fourth stage is printing the theme(s) and max value of total enrollments
// Parameters:
// - m: data structure map for examination
// - t: user input theme
// Variables:
// - total_enrollments: map with themes as keys and total amount of enrollments
//                      as values
void print_favorite_theme(const map< string, vector< Course > >& m)
{
    map< string, int > total_enrollments;
    for ( map< string, vector< Course >>::const_iterator it = m.begin(); it != m.end(); ++it ) {
        for ( Course c : it->second ) {
            if ( total_enrollments.find(c.theme) == total_enrollments.end() ) {
                total_enrollments.insert( {c.theme, c.enrollments} );
            } else {
                total_enrollments.at(c.theme) += c.enrollments;
            }
        }
    }
    int max_value = -1;
    for ( map< string, int >::const_iterator it = total_enrollments.begin();
          it != total_enrollments.end(); ++it ) {
        if ( max_value <= it->second ) {
            max_value = it->second;
        }
    }
    // Find which themes have the max values
    vector< string > max_theme;
    for ( map< string, int >::const_iterator it = total_enrollments.begin();
          it != total_enrollments.end(); ++it) {
        if ( it->second == max_value ) {
            max_theme.push_back(it->first);
        }
    }
    if ( max_theme.empty() ) {
        cout << "No enrollments" << endl;
    } else {
        cout << max_value << " enrollments in themes" << endl;
        for ( string theme : max_theme ) {
            cout << "--- " << theme << endl;
        }
    }
}

// Main function that starts with opening an input file and reading its content
// in to a data structure. After that function asks user for commands in a
// while loop which start to call other functions.
// Program ends with 'quit' function.
int main()
{
    map< string, vector< Course > > centre;

    string input;
    cout << "Input file: ";
    getline(cin, input);

    ifstream input_file(input);
    if ( !input_file ) {
        cout << FILE_ERROR << endl;
        return EXIT_FAILURE;
    } else {
        // Read lines over input data and save to "centre"
        // in format centre.at(location).theme = theme_of_the_course
        // centre.at(location).name = name_of_the_course
        // centre.at(location).enrollments = amount_of_enrollments_in_the_course
        string line;
        Course info;
        while ( getline(input_file, line) ) {
            if ( split_to_vector(line, ';').size() != 4 ) {
                cout << EMPTY_FIELD << endl;
                return EXIT_FAILURE;
            } else {
                string location = split_to_data(line);
                string theme = split_to_data(line);
                string course_name = split_to_data(line);
                int enrollments = stoi(split_to_data(line));
                info = {theme, course_name, enrollments};

                // Inserts the information in to the data structure
                // Creates new key if there is none for a location
                if ( centre.find(location) == centre.end() ) {
                    centre.insert( {location, {info}} );
                } else {
                    // Checks if the there are any overlapping
                    // courses and takes the last into account
                    int indicator = 0;
                    for ( Course& c : centre.at(location) ) {
                        if ( theme ==  c.theme and course_name == c.name ) {
                            c.enrollments = enrollments;
                            ++indicator;
                        }
                    }
                    if ( indicator == 0 ) {
                        centre.at(location).push_back(info);
                    }
                }
            }
        }
        input_file.close();

        // Initial user input. Takes needed commands to start to start loop
        string user_input;
        cout << "> ";
        getline(cin, user_input);
        vector< string > commands = split_to_vector(user_input, ' ');
        string command = commands.at(0);

        // Looping user interface that will loop until given gomman "quit"
        // Command "locations" prints all locations
        // "courses" prints searched courses and how many participants it has
        // "availanle" prints all courses that are not full
        // "courses_in_theme" prints all possible courses in searched theme
        // "favourite_theme" prints the theme with most participants
        while ( command != "quit" ) {
            if ( command == "locations" ) {
                print_locations(centre);
            } else if ( command == "courses" ) {
                if ( commands.size() != 3 ) {
                    cout << PARAMETER_ERROR << command << endl;
                } else {
                    // Check for unknown location
                    if ( centre.find(commands.at(1)) == centre.end() ) {
                        cout << UNKNOWN_LOCATION << endl;
                    } else if ( search_for_theme(centre, commands.at(2)) ) {
                        cout << UNKNOWN_THEME << endl;
                    } else {
                        for ( Course c : centre.at(commands.at(1)) ) {
                            if ( c.theme == commands.at(2) ) {
                                print_courses(c);
                            }
                        }
                    }
                }
            } else if ( command == "available" ) {
                print_available(centre);
            } else if ( command == "courses_in_theme" ) {
                print_courses_in_theme(centre, commands.at(1));
            } else if ( command == "favorite_theme" ) {
                print_favorite_theme(centre);
            } else {
                cout << UNKNOWN_COMMAND << command << endl;
            }
            // Get new input
            cout << "> ";
            getline(cin, user_input);
            commands = split_to_vector(user_input, ' ');
            command = commands.at(0);
        }
    }
    return 0;
}


