#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string encryption(string k, string t)
{
    string alphabet = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < t.length(); i++) {
        t.at(i) = k.at( alphabet.find( t.at( i ) ) );
    }
    return t;
}

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
        for (unsigned long int i = 0; i < key_length; i++) {
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
            } else {
                cout << "Enter the text to be encrypted: ";
                string text;
                string::size_type text_length = 0;
                cin >> text;
                text_length = text.length();

                int text_error = 0;
                for (unsigned long int j = 0; j < text_length; j++) {
                    if ( islower(text.at(j)) == false ) {
                        text_error += 1;
                    }
                }
                if (text_error != 0) {
                    cout << "Error! The encryption key must contain only lower case characters." << endl;
                } else {
                    cout << "Encrypted text: " << encryption(key, text) << endl;
                }
            }
        }
    }
}
