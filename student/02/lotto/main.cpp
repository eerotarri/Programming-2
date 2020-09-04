#include <iostream>

using namespace std;

int main()
{
    long int total_balls;
    cout << "Enter the total number of lottery balls: ";
    cin >> total_balls;

    long int drawn_balls;
    cout << "Enter the number of drawn balls: ";
    cin >> drawn_balls;

    if ( ( total_balls <= 0 ) || ( drawn_balls <= 0 ) ) {
        cout << "The number of balls must be a positive number" << endl;
    } else {
        // cout << total_balls << " " << drawn_balls << endl;
    }
}
