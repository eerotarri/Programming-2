#include <iostream>

using namespace std;

int main()
{
    int amount;
    cout << "How many numbers would you like to have? ";
    cin >> amount;

    int i = 1;

    while ( i < amount + 1 ) {
        if ( i % 3 == 0 && i % 7 == 0) {
            cout << "zip boing" << endl;
        } else if ( i % 7 == 0 ) {
            cout << "boing" << endl;
        } else if ( i % 3 == 0 ) {
            cout << "zip" << endl;
        } else {
            cout << i << endl;
        }
        ++i;
    }
}
