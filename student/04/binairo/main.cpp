/* Binairo
 *
 * Description:
 *   This program implements the Binairo game. The game features a 6x6 board,
 * where each square is either empty, zero, or one. The objective is to fill
 * the empty squares according to the following rules:
 * - Each row and column can have at most three instances of the same number.
 * - Each row and column can have at most
 * two consecutive instances of the same number.
 *   Initially, the user is asked whether to fill the game grid with randomly
 * generated symbols or with the user's choice of 36 symbols.
 * In the first option,
 * the user is prompted for the seed of the random number generator.
 * In the second option, the user is asked to input 36 symbols,
 * which are then validated for correctness.
 *   In each round, the user is prompted for the
 *   coordinates of the symbol to be added,
 * as well as the symbol itself (three symbols in total).
 * The game ends in victory
 * if the game grid is filled according to the aforementioned rules.
 * The program
 * prevents additions that violate the specified rules,
 * but it is possible to reach
 * a situation where no further additions are possible.
 *   The program validates the input provided by the user.
 * The symbol to be added must be either zero or one.
 *  The coordinates must be within the game grid, and the
 * indicated square must be empty.
 *
 * Written by
 * Name: Jonatan Tevaniemi
 * Student number: 150176680
 * Username: cnjote
 * E-Mail: jonatan.tevaniemi@tuni.fi
 *
 * Notes about the program and its implementation:
 *
 * */

#include "gameboard.hh"
#include <iostream>

using namespace std;

// Output messages
const string QUIT = "Quitting ...";
const string OUT_OF_BOARD = "Out of board";
const string INVALID_INPUT = "Invalid input";
const string CANT_ADD = "Can't add";
const string WIN = "You won!";
const string BAD_SEED = "Bad seed";
const string WRONG_SIZE = "Wrong size of input";
const string WRONG_CHARACTER = "Wrong character";


// Converts the given numeric string to the corresponding integer
// (by calling stoi) and returns the integer.
// If the given string is not numeric, returns zero.
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

// Removes empty characters (such as ' ' etc.) from the given string.
// Returns true if the given string has exactly one non-empty character,
// which is either '0' or '1', otherwise returns false.
bool find_fill_symbol(string& str)
{
    string fill_str = "";
    for(unsigned int i = 0; i < str.size(); ++i)
    {
        if(not isspace(str.at(i)))
        {
            fill_str += str.at(i);
        }
    }
    str = fill_str;
    return (fill_str.size() == 1 and
           (fill_str.at(0) == '0' or fill_str.at(0) == '1'));
}

// Enables the user to play the game, i.e. by repeatedly asking an element
// to be added and its position, until the game is over.
void play_game(GameBoard& board)
{
    board.print();
    while(not board.is_game_over())
    {
        string x_str = "";
        string y_str = "";
        string rest_input = "";
        cout << "Enter two coordinates and a fill symbol, or q to quit: ";

        // Reading x coordinate as a string and checking if it was quit command
        cin >> x_str;
        if(x_str.at(0) == 'q' or x_str.at(0) == 'Q')
        {
            cout << QUIT << endl;
            return;
        }

        // Reading y coordinate
        cin >> y_str;

        // Changing coordinates from string to int and checking if they are
        // inside the board
        unsigned int x = stoi_with_check(x_str);
        unsigned int y = stoi_with_check(y_str);
        if(not (1 <= x and x <= SIZE and 1 <= y and y <= SIZE))
        {
            cout << OUT_OF_BOARD << endl;
            getline(cin, rest_input);
            continue;
        }

        // Reading the rest of the input line including fill symbol and
        // checking if the rest input consists exactly of one '0' or '1'
        getline(cin, rest_input);
        if(not find_fill_symbol(rest_input))
        {
            cout << INVALID_INPUT << endl;
            continue;
        }

        // At this point, we know that the input is valid, but we don't know
        // if it is possible to add the given symbol on the given position
        // TODO: Add such check
        if (board.is_empty(y-1, x-1))
        {
            board.set_type(y-1, x-1, rest_input[0]);

            if (board.is_too_many())
            {
                cout << CANT_ADD << endl;
                board.set_type(y-1, x-1, ' ');
            }
            else if (board.is_too_many_consecutive())
            {
                cout << CANT_ADD << endl;
                board.set_type(y-1, x-1, ' ');
            }
            else
            {
                // If the given symbol was possible to add,
                // print the changed gameboard
                board.print();
            }
        }
        else
        {
            cout << CANT_ADD << endl;
        }

    }
    // If the game ends up to a totally filled gameboard, the player won
    cout << WIN << endl;
}

// Checks for wrong character in initial board input
bool is_wrong_character(string input)
{
    for(size_t i = 1; i < size(input) - 1; ++i)
    {
        if(input[i] != ' ' and input[i] != '0' and input[i] != '1')
        {
            return true;
        }
    }
    return false;
}

// Gives the user a possibility to select a filling way.
// Returns true if filling succeeded, otherwise returns false.
bool select_start(GameBoard& board)
{
    string choice = "";
    cout << "Select start (R for random, I for input): ";
    getline(cin, choice);
    if(choice != "R" and choice != "r" and choice != "I" and choice != "i")
    {
        return false;
    }
    else if(choice == "R" or choice == "r")
    {
        string seed_string = "";
        cout << "Enter a seed value: ";
        getline(cin, seed_string);

        // check if user seed is bad
        unsigned int seed_int = stoi_with_check(seed_string);
        if(board.is_bad_seed(seed_int))
        {
            cout << BAD_SEED << endl;
            return false;
        }
        else
        {
            board.generate_random_board(seed_int);
        }
        return true;

        // TODO: Fill gameboard and return if it succeeded or not
    }
    else // if(choice == "I" or choice == "i")
    {
        string input = "";
        cout << "Input: ";
        getline(cin, input);

        // Check that the input is correct
        if(input.size() != 38)
        {
            cout << WRONG_SIZE << endl;
            return false;
        }
        else if(is_wrong_character(input))
        {
            cout << WRONG_CHARACTER << endl;
            return false;
        }
        // Fill game board
        else
        {
            for(size_t i = 1; i < size(input) - 1; ++i)
            {
                int x = (i - 1) / SIZE;
                int y = (i - 1) % SIZE;
                board.set_type(x, y, input[i]);
            }
        }
        return true;

    }
}

// Short and simple main function.
int main()
{
    GameBoard board;
    while(not select_start(board));
    play_game(board);
    return 0;
}
