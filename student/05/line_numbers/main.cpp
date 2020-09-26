#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    cout << "Input file: ";
    string input;
    cin >> input;

    ifstream input_file(input);

    cout << "Output file: ";
    string output;
    cin >> output;

    ofstream output_file(output);

    if ( input_file ) {
        string line;
        int index = 1;
        while ( getline(input_file, line) ) {
            output_file << index << " " << line << endl;
            ++index;
        }
    } else {
        cout << "Error! The file " << input << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    input_file.close();
    output_file.close();
    return 0;
}
