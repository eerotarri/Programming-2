#include <iostream>

using namespace std;

int main()
{
    int amount;
    cout << "How many numbers would you like to have? ";
    cin >> amount;

    int i = 1;

    while ( i < amount + 1 )
    {
        cout << i << endl;
        ++i;
    }
}
