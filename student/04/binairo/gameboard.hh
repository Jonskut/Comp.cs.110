/*
 * Header for gameboard class
 * The gameboard class handles the board's contents and printing it.
 *
 * Written by
 * Name: Jonatan Tevaniemi
 * Student number: 150176680
 * Username: cnjote
 * E-Mail: jonatan.tevaniemi@tuni.fi
 */

#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <vector>
#include <string>
#include <random>

// Type of the elements in the gameboard
enum Element_type {ZERO, ONE, EMPTY};

// Constants for the size of the gameboard
const int NUMBER_OF_SYMBOLS = 3;
const int SIZE = 2 * NUMBER_OF_SYMBOLS;

// Constant for the upper bound of probability distribution
// Zeros and ones have the same probability, say x, and the estimated
// probability of empties is 6x, whereupon their sum is 8x, and thus,
// the interval must have eight points, as [0..7]
const int DISTR_UPPER_BOUND = 7;

// Width of the left-most column, needed in printing the gameboard
const unsigned int LEFT_COLUMN_WIDTH = 5;


class GameBoard
{
public:
    // Constructor
    // Initializes board to be 6x6 size and EMPTY on all squares
    GameBoard();

    // Generates random board
    // Input: unsigned int, seed
    void generate_random_board(unsigned int seed);

    // Check if position is empty
    // Return: true if position is empty
    bool is_empty(int x, int y);

    // Check if too many of same type in a row or col
    // Return: true if too many in a row or col
    bool is_too_many() const;

    // Check if too many of same type consecutively
    // Return: true if too consecutive numbers
    bool is_too_many_consecutive() const;

    // Prints the gameboard
    void print() const;

    // Sets element type in number board
    // This is used for initial board setting
    // as well as when player inputs a new number
    void set_type(int row, int col, char input);

    // Checks if the game is over
    // Return: bool, true if game is over
    bool is_game_over() const;

    // Check for bad seed
    // Return: bool, true if seed is bad
    bool is_bad_seed(unsigned int& seed) const;


private:
    // Prints a line with the given length and the given character
    void print_line(unsigned int length, char fill_character) const;

    // Seed values, from [1..50], producing non-solvable gameboard
    const std::vector<unsigned int> BAD_SEEDS = { 2, 8, 12, 13, 16, 20, 21, 23,
                                                  26, 29, 31, 32, 34, 41, 42,
                                                  43, 44, 46 };

    // Actual board where the game state is stored
    std::vector< std::vector<Element_type> > number_board_;
};

#endif // GAMEBOARD_HH
