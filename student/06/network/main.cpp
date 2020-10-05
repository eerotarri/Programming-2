#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

const string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


vector<string> split(const string& s, const char delimiter, bool ignore_empty = false){
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }

    return result;
}

void print(string name, const map< string, vector< string > >& container, int round=0)
{
    string dots = "";
    for ( int i = 0; i < round; ++i ) {
        dots += "..";
    }
    cout << dots << name << endl;
    if ( container.find(name) == container.end() ) {
        return;
    } else {
        vector< string > recruits = container.at(name);
        for ( string n : recruits ) {
            print(n, container, round+1);
        }
    }
}

int count( string name, const map< string, vector< string > >& container )
{
    if ( container.find(name) == container.end() ) {
        return 0;
    } else {
        int sum = 0;
        for ( auto n : container.at(name) ) {
            sum += count(n, container);
        }
        return container.at(name).size() + sum;

    }
}

int depth(string name, const map< string, vector< string > >& container)
{
    vector< int > numbers;
    if ( container.find(name) == container.end() ) {
        return 1;
    } else {
        for ( string n : container.at(name) ) {
            numbers.push_back(depth(n, container));
        }
        int max = 0;
        for ( int i : numbers ) {
            if ( i > max) {
                max = i;
            }
        }
        return max + 1;
    }
}

int main()
{
    // map that has person that recruitted as a key and recruits as values in a vector
    map< string, vector< string > > network;


    while(true){
        string line;
        cout << "> ";
        getline(cin, line);
        vector<string> parts = split(line, ' ', true);

        string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                cout << "Erroneous parameters!" << endl << HELP_TEXT;
                continue;
            }
            string id1 = parts.at(1);
            string id2 = parts.at(2);

            if ( network.find(id1) == network.end() ) {
                // Create new recruitter
                network.insert( {id1, {id2}} );
            } else {
                // Add recruits to an existing recruitter
                network.at(id1).push_back(id2);
            }


        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                cout << "Erroneous parameters!" << endl << HELP_TEXT;
                continue;
            }
            string id = parts.at(1);

            print(id, network);

        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                cout << "Erroneous parameters!" << endl << HELP_TEXT;
                continue;
            }
            string id = parts.at(1);

            cout << count(id, network) << endl;

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                cout << "Erroneous parameters!" << endl << HELP_TEXT;
                continue;
            }
            string id = parts.at(1);

            cout << depth(id, network) << endl;

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            cout << "Erroneous command!" << endl << HELP_TEXT;
        }
    }
}
