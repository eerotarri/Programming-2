#include "array_operations.hh"
#include <algorithm>
#include <iostream>

using namespace std;

int greatest_v1(int* itemptr, int size)
{
        int* max = max_element(itemptr, itemptr + size);
        return *max;
}

int greatest_v2(int* itemptr, int* endptr)
{
        int* max = max_element(itemptr, endptr);
        return *max;
}

void copy(int* itemptr, int* endptr, int* targetptr)
{
    int index = 0;
    for ( int* position = itemptr; position < endptr; ++position ) {
        *(targetptr + index) = *position;
        ++index;
    }
}

void reverse(int* leftptr, int* rightptr)
{
    while (leftptr < rightptr)
        {
            int temp = *leftptr;
            *leftptr = *rightptr;
            *rightptr = temp;
            ++leftptr;
            --rightptr;
        }
}
