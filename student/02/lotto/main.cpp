/*
 * Jonatan Tevaniemi 2024
 * All rights reserved
 */

#include <iostream>

using namespace std;


/*
 *  Calculate factorial
 *      Parameters:
 *          n - the input number for which to calculate the factorial.
 *      Returns:
 *      The factorial of the input number
 */
unsigned long int factorial(unsigned long int n)
{
    unsigned long int result = 1;
    for ( unsigned int i = 1; i <= n; ++i){
        result *= i;
    }
    return result;
}


/*
 * Calculate and display probability
 *      Parameters:
 *          total - total balls
 *          drawn - amount of balls drawn
 */
void calculateProbability(unsigned long int total, unsigned long int drawn)
{
    unsigned long int possibilities =
            factorial(total) / ( factorial(total-drawn) * factorial(drawn) );

    cout << "The probability of guessing all " << drawn << " balls correctly is " <<
            "1/" << possibilities << endl;

}


/*
 * Handles user input
 *     Parameters:
 *          total - total balls
 *          drawn - amount of balls drawn
 */
void handleInput(int totalBalls, int drawnBalls)

{
    // check error
    if ( totalBalls < 0 or drawnBalls < 0 ) {
        cout << "The number of balls must be a positive number." << endl;
    }
    else if ( drawnBalls > totalBalls ) {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
    }
    else {
        calculateProbability(totalBalls, drawnBalls);
    }
}


int main()
{
    // read input
    cout << "Enter the total number of lottery balls: ";
    int totalBalls; cin >> totalBalls;

    cout << "Enter the number of drawn balls: ";
    int drawnBalls; cin >> drawnBalls;

    handleInput(totalBalls, drawnBalls);

    return 0;
}
