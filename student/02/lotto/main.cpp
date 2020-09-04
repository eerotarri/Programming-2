#include <iostream>

using namespace std;

unsigned long int factorial(long int num)
{
    unsigned long int sum = 1;
    long int i;
    for ( i = 1; i <= num; ++i ) {
        sum = sum * i;
    }
    return sum;
}

unsigned long int probability(long int total, long int drawn)
{
    unsigned long int osoittaja = factorial(total);
    unsigned long int nimittaja = factorial(total - drawn) * factorial(drawn);

    unsigned long int prob = osoittaja / nimittaja;

    return prob;
}

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
    } else if (drawn_balls > total_balls) {
        cout << "The maximum number of drawn balls "
                "is the total amount of balls" << endl;
    } else {
        unsigned long int prob = probability(total_balls, drawn_balls);

        cout << "The probability of guessing all "
             << drawn_balls << " correctly is 1/" << prob
             << endl;
    }
}
