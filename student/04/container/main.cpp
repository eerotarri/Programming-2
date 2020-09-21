#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);
    }
}

bool same_values(const std::vector< int >& ints)
{
    int index = 0;
    for ( int vektorin_alkio : ints) {
        if ( vektorin_alkio != ints.at(0)){
            index += 1;
        }
    }
    if ( index == 0 ) {
        return true;
    } else {
        return false;
    }
}

bool is_ordered_non_strict_ascending(const std::vector< int >& ints)
{
    int index = 1;
    int counter = 0;
    size_t runningNumber = 0;
    size_t intendedSize = ints.size();
    for ( int vektorin_alkio : ints ) {
        if ( runningNumber < intendedSize - 1) {
            if ( vektorin_alkio > ints.at(index)) {
                counter += 1;
            }
        }
        index += 1;
        runningNumber += 1;
    }
    if ( counter == 0 ) {
        return true;
    } else {
        return false;
    }
}

bool is_arithmetic_series(const std::vector< int >& ints)
{
    int arit = ints.at(1) - ints.at(0);
    int index = 1;
    int counter = 0;
    size_t runningNumber = 0;
    size_t intendedSize = ints.size();
    for ( int vektorin_alkio : ints ) {
        if ( runningNumber < intendedSize - 1 ) {
            if ( ints.at(index) - vektorin_alkio != arit ) {
                counter += 1;
            }
        }
        runningNumber += 1;
        index += 1;
    }
    if ( counter == 0 ) {
        return true;
    } else {
        return false;
    }
}

bool is_geometric_series(const std::vector< int >& ints)
{
    for ( int vektorin_alkio : ints ) {
        if ( vektorin_alkio == 0 )
            return false;
    }
    double geom = ints.at(1) / ints.at(0);
    int index = 1;
    int counter = 0;
    size_t runningNumber = 0;
    size_t intendedSize = ints.size();
    for ( int vektorin_alkio : ints ) {
        if ( runningNumber < intendedSize - 1 ) {
            if ( ints.at(index) / vektorin_alkio != geom ) {
                counter += 1;
            }
        }
        runningNumber += 1;
        index += 1;
    }
    if ( counter == 0 ) {
        return true;
    } else {
        return false;
    }
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
