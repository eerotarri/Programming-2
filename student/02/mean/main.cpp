#include <iostream>

using namespace std;

double mean(double summa, int jakaja)
{
    double keskiarvo = summa / jakaja;
    return keskiarvo;
}

int main()
{
    int amount;
    cout << "From how many integer numbers you want to count the mean value? ";
    cin >> amount;

    int i = 1;
    double sum = 0;
    int input;
    if ( amount < 1) {
        cout << "Cannot count mean value from "
             << amount << " numbers" << endl;
    } else {
        while ( i < amount + 1 ) {
            cout << "Input " << i << ". number: ";
            cin >> input;
            sum += input;
            ++i;
        }
        double ka = mean(sum, amount);
        cout << "Mean value of the given numbers is " << ka << endl;
    }
}
