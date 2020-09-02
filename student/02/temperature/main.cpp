#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";
    double temperature;
    cin >> temperature;

    double celsius = (temperature - 32) / 1.8;
    double fahrenheit = temperature * 1.8 + 32;

    cout << temperature << " degrees Celsius is " << fahrenheit << " degrees Fahrenheit" << endl;
    cout << temperature << " degrees Fahrenheit is " << celsius << " degrees Celsius" << endl;

    return 0;
}
