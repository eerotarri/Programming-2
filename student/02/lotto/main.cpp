#include <iostream>

using namespace std;

int main()
{
    unsigned long int total_balls;
    cout << "Enter the total number of lottery balls: ";
    cin >> total_balls;

    unsigned long int drawn_balls;
    cout << "Enter the number of drawn balls: ";
    cin >> drawn_balls;

    cout << total_balls << " " << drawn_balls << endl;
}
