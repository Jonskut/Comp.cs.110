#include "array_operations.hh"
#include<iostream>

int greatest_v1(int *itemptr, int size)
{
    int greatest = *itemptr;
    for (int i = 0; i < size; ++i)
    {
        if (*(itemptr + i) > greatest)
        {
            greatest = *(itemptr+i);
        }
    }
    return greatest;
}

int greatest_v2(int *itemptr, int *endptr)
{
    int greatest = *itemptr;
    while (itemptr < endptr)
    {
        if(*itemptr > greatest)
        {
            greatest = *itemptr;
        }
        ++itemptr;
    }
    return greatest;
}

void copy(int *itemptr, int *endptr, int *targetptr)
{
    while (itemptr < endptr)
    {
        *targetptr = *itemptr;
        ++targetptr;
        ++itemptr;
    }
}

void reverse(int *leftptr, int *rightptr)
{
    --rightptr;
    while (leftptr < rightptr)
    {
        int temp = *leftptr;
        *leftptr = *rightptr;
        *rightptr = temp;

        ++leftptr;
        --rightptr;
    }
}
