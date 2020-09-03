#include <iostream>

using namespace std;

int cube(int num)
{
    int ans = num * num * num;
    return ans;
}

int main()
{
    int number;
    cout << "Enter a number: ";
    cin >> number;

    // cout << number << endl;
    int cubed = cube(number);
    // cout << cubed << endl;
    if ( ( ( cubed / number ) / number ) == number ) {
        cout << "The cube of "
             << number << " is "
             << cubed << endl;
    } else {
        cout << "Error! The cube of "
             << number << " is not "
             << cubed << "." << endl;
    }
}
