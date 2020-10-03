#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
    cout << "Input file: ";
    string file_name;
    getline(cin, file_name);
    map<string, vector<int>> words;

    ifstream input_file(file_name);
    if ( input_file ) {
        string line;
        int row = 1;
        while ( getline(input_file, line) ) {
            // save words in line to a vector
            vector<string> words_in_a_line = {};
            string separator = " ";
            while ( line != "" ) {
                size_t index = line.find(separator);
                if ( index != string::npos ) {
                    words_in_a_line.insert(words_in_a_line.end(), line.substr(0, index));
                    line.erase(0, index + 1);
                } else {
                    words_in_a_line.insert(words_in_a_line.end(), line);
                    line.erase(0, line.length());
                }
            }
            // Iterate trough words in a line

            for ( string word : words_in_a_line ) {
                if ( words.find(word) == words.end() ) {
                    words.insert( {word, {1, row}} );
                } else {
                    words.at(word).at(0) += 1;
                    words.at(word).insert(words.at(word).end(), row);
                }
            }
            ++row;
        }
        for ( auto avain : words ) {
            string line;
            for ( size_t i = 1; i < avain.second.size(); ++i ) {
                if ( line != "" ) {
                    line += ", ";
                }
                line += to_string(avain.second.at(i));
            }



            cout << avain.first << " " << avain.second.at(0) << ": " << line << endl;
        }

    } else {
        cout << "Error! The file " << file_name << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
}
