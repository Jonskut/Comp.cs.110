#include <iostream>

using namespace std;

int main()
{
    // read input
    cout << "Enter a number: ";
    int number; cin >> number;

    // cube number
    int numberCubed = number * number * number;

    // check overflow
    if ( number == numberCubed / (number * number) ) {
        cout << "The cube of " << number << " is " << numberCubed
             << "." << endl;
    }
    else {
        cout << "Error! The cube of " << number << " is not "
             << numberCubed << "." << endl;
    }

    return 0;
}
