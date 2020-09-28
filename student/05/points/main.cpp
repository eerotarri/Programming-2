#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main()
{
    map<string, int> points;
    string file_name;
    cout << "Input file: ";
    getline(cin, file_name);

    ifstream input_file(file_name);
    if ( not input_file ) {
        cout << "Error! The file not_a_file.txt cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {
        string rivi;
        char sep = ':';

        while (getline(input_file, rivi)) {
            int index = rivi.find(sep);
            string name = rivi.substr(0, index);
            rivi.erase(0, index + 1);
            int round_points = stoi(rivi);
            auto iter = points.find(name);
            if ( iter == points.end() ) {
                points.insert( { name, round_points } );
            } else {
                points.at(name) += round_points;
            }
        }
        map<string, int>::iterator mapiter = points.begin();
        cout << "Final scores:" << endl;
        while ( mapiter != points.end() ) {
            cout << mapiter->first << ": " << mapiter->second << endl;
            ++mapiter;
        }
    }
    input_file.close();
}
