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


    if ( input_file ) {
        ofstream output_file(output);
        string line;
        int index = 1;
        while ( getline(input_file, line) ) {
            output_file << index << " " << line << endl;
            ++index;
        }
        output_file.close();
    } else {
        cout << "Error! The file " << input << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    input_file.close();
    return 0;
}
