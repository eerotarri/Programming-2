#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    cout << "Enter the encryption key: ";
    string key;
    string::size_type key_length = 0;
    cin >> key;
    key_length = key.length();

    if (key_length != 26) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
    } else {
        int check = 0;
        for (int i = 0; i < key_length; i++) {
            if ( islower(key.at(i)) == false ) {
                check += 1;
            }
        }
        if (check != 0) {
            cout << "Error! The encryption key must contain only lower case characters." << endl;
        } else {
            int space;
            int error = 0;
            for ( char l = 'a'; l < 'z'; ++l ) {
                space = key.find(l);
                if (space == string::npos) {
                    error += 1;
                }
            }
            if (error != 0) {
                cout << "Error! The encryption key must contain all alphabets a-z." << endl;
            }
        }
    }
}
