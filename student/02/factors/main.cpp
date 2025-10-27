#include <iostream>

using namespace std;

int main()
{
    // reads input
    int numberToCheck = 0;
    cout << "Enter a positive number: ";
    cin >> numberToCheck;

    if ( numberToCheck <= 0 ) {
        cout << "Only positive numbers accepted" << endl;
    }
    else {
        // initial "best match" is 1 * numberToCheck
        int closestFactor1 = 1;
        int closestFactor2 = numberToCheck;

        // find all the factors less than numberToCheck
        for ( int factor1 = 1; factor1 < numberToCheck; ++factor1 ) {
            if ( numberToCheck % factor1 == 0 ) {
                int factor2 = numberToCheck / factor1;


                // check if found factors are better than current
                if ( abs( factor1 - factor2 ) < abs( closestFactor1 - closestFactor2 ) ) {
                    closestFactor1 = factor1;
                    closestFactor2 = factor2;

                }
            }
        }

        cout << numberToCheck << " = " << closestFactor1 << " * " << closestFactor2 << endl;
    }

    return 0;
}
