#include <iostream>
#include <string>
#include <vector>


std::vector< std::string > split(std::string text, char sep, bool no_empty=false)
{
    std::vector<std::string> separated_line = { };
    std::string::size_type i = 0;
    if ( no_empty == true ) {
        while ( text != "" ) {
            i = text.find(sep);
            if ( i != 0 ) {
                separated_line.push_back(text.substr(0, i));
                text.erase(0, i);
            } else if ( i == std::string::npos ) {
                separated_line.push_back(text.substr(0, text.length()));
            }
            text.erase(0, 1);
        }
    } else {
        while ( text != "" ) {
            i = text.find(sep);
            if ( i != 0 ) {
                separated_line.push_back(text.substr(0, i));
                text.erase(0, i);
            } else if ( i == 0 ) {
                separated_line.push_back("");
                if ( text.length() == 1 ) {
                    separated_line.push_back("");
                }
            } else if ( i == std::string::npos ) {
                separated_line.push_back(text.substr(0, text.length()));
            }
            text.erase(0, 1);
        }
    }
    return separated_line;
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
