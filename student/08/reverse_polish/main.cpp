#include <iostream>
#include <ctype.h>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

int main()
{
    string notation;
    cout << "Input an expression in reverse Polish notation (end with #):" << endl
         << "EXPR> ";
    getline(cin, notation);

    int i = 0;
    int digits = 0;
    int operators = 0;
    for ( auto it = notation.begin(); *it != '#'; ++it ) {
        if ( *it != ' ' ) {
            if ( isdigit(*it) ) {
                ++digits;
            } else {
                ++operators;
            }
            ++i;
        }
    }
    char array[i];
    i = 0;
    for ( auto it = notation.begin(); *it != '#'; ++it ) {
        if ( *it != ' ' ) {
            *(array + i) = *it;
            ++i;
        }
    }

    if ( !isdigit(*notation.begin()) ) {
        cout << "Error: Expression must start with a number" << endl;
        return EXIT_FAILURE;
    } else if ( digits - operators < 1 ) {
        cout << "Error: Too few opernds" << endl;
        return EXIT_FAILURE;
    } else if ( digits - operators > 1 ) {
        cout << "Error: Too few operators" << endl;
        return EXIT_FAILURE;
    } else {
        vector< int > operands = {};
        for ( char* position = array; position < array + i; position++) {
            if ( isdigit(*position) ) {
                operands.push_back(*position - '0');
            } else if ( *position == '+' ) {
                int sum = *(operands.end()-2) + *(operands.end()-1);
                operands.pop_back();
                operands.pop_back();
                operands.push_back(sum);
            } else if ( *position == '-' ) {
                int sub = *(operands.end()-2) - *(operands.end()-1);
                operands.pop_back();
                operands.pop_back();
                operands.push_back(sub);
            } else if ( *position == '*' ) {
                int multi = (*(operands.end()-2)) * (*(operands.end()-1));
                operands.pop_back();
                operands.pop_back();
                operands.push_back(multi);
            } else if ( *position == '/' ) {
                if ( *(operands.end()-1) == 0 ) {
                    cout << "Error: Division by zero" << endl;
                    return EXIT_FAILURE;
                } else {
                    int div = (*(operands.end()-2)) / (*(operands.end()-1));
                    operands.pop_back();
                    operands.pop_back();
                    operands.push_back(div);
                }
            } else {
                cout << "Error: Unknown character" << endl;
                return EXIT_FAILURE;
            }
//            for ( auto kakka : operands ) {
//                cout << kakka << " ";
//            }
//            cout << endl;
        }

        cout << "Correct: " << operands.at(0) << " is the result" << endl;
    }

//    for ( char* position = array; position < array + i; position++) {
//        cout << *position << endl;
//    }


}
