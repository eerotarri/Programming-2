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


vector< string > split_to_vector(const string& s, const char delimiter, bool ignore_empty=true)
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
        for ( auto alkio : result ) {
            cout << alkio << endl;
        }
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


void print_locations(const map< string, vector< Course > >& m)
{
    for ( map< string, vector< Course >>::const_iterator it = m.begin(); it != m.end(); ++it ) {
        cout << it->first << endl;
    }
}

void print_courses(Course c)
{
    if ( c.enrollments == 50 ) {
        cout << c.name << " --- full" << endl;
    } else {
        cout << c.name << " --- " << c.enrollments << " enrollments" << endl;
    }

}

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


