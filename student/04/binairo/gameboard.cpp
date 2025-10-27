/*
 * Gameboard class, contains all methods and private functions for
 * implementing the board and printing it to the terminal.
 * Check header file for function commments
 *
 * Written by
 * Name: Jonatan Tevaniemi
 * Student number: 150176680
 * Username: cnjote
 * E-Mail: jonatan.tevaniemi@tuni.fi
 */

#include "gameboard.hh"
#include <iostream>
#include <random>

GameBoard::GameBoard():
    number_board_(6, std::vector<Element_type>(6, EMPTY))
{

}

void GameBoard::generate_random_board(unsigned int seed)
{
    // Settings for random number generation
    std::default_random_engine gen(seed);
    std::uniform_int_distribution<int> distr(0, DISTR_UPPER_BOUND);

    // Make string from random numbers
    std::string random_string = "";
    int random_number;
    for (int i = 0; i < 36; ++i)
    {
        random_number = distr(gen);

        if (random_number >= 2)
        {
            random_string += ' ';
        }
        else
        {
            random_string += std::to_string(random_number);
        }
    }

    // Fill game board
    for (size_t i = 0; i < size(random_string); ++i)
    {
        int x = i / SIZE;
        int y = i % SIZE;
        set_type(x, y, random_string[i]);
    }


}

bool GameBoard::is_empty(int x, int y)
{
    if (number_board_[x][y] == EMPTY)
    {
        return true;
    }
    return false;
}

bool GameBoard::is_too_many() const
{
    // Check rows
    for (unsigned int x = 0; x < SIZE; ++x)
    {
        int zeros = 0;
        int ones = 0;

        for (unsigned int y = 0; y < SIZE; ++y)
        {
            if (number_board_[x][y] == ZERO)
            {
                ++zeros;
            }
            else if (number_board_[x][y] == ONE)
            {
                ++ones;
            }
        }
        if (zeros > 3 or ones > 3)
        {
            return true;
        }
    }
    // Check cols
    for (unsigned int y = 0; y < SIZE; ++y)
    {
        int zeros = 0;
        int ones = 0;

        for (unsigned int x = 0; x < SIZE; ++x)
        {
            if (number_board_[x][y] == ZERO)
            {
                ++zeros;
            }
            else if (number_board_[x][y] == ONE)
            {
                ++ones;
            }
        }
        if (zeros > 3 or ones > 3)
        {
            return true;
        }
    }
    return false;
}

bool GameBoard::is_too_many_consecutive() const
{
    {
        // Check rows
        for (unsigned int x = 0; x < SIZE; ++x)
        {
            int zeros = 0;
            int ones = 0;

            for (unsigned int y = 0; y < SIZE; ++y)
            {
                if (number_board_[x][y] == ZERO)
                {
                    ++zeros;
                    ones = 0;
                }
                else if (number_board_[x][y] == ONE)
                {
                    ++ones;
                    zeros = 0;
                }
                else // There is an empty space -> not consecutive
                {
                    zeros = 0;
                    ones = 0;
                }

                if (zeros > 2 or ones > 2)
                {
                    return true;
                }
            }
        }
        // Check cols
        for (unsigned int y = 0; y < SIZE; ++y)
        {
            int zeros = 0;
            int ones = 0;

            for (unsigned int x = 0; x < SIZE; ++x)
            {
                if (number_board_[x][y] == ZERO)
                {
                    ++zeros;
                    ones = 0;
                }
                else if (number_board_[x][y] == ONE)
                {
                    ++ones;
                    zeros = 0;
                }
                else // There is an empty space -> not consecutive
                {
                    zeros = 0;
                    ones = 0;
                }

                if (zeros > 2 or ones > 2)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void GameBoard::print() const
{
    // Printing upper border
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');

    // Printing title row
    std::cout << "|   | ";
    for (unsigned int i = 0; i < SIZE; ++i)
    {
        std::cout << i + 1 << " ";
    }
    std::cout << "|" << std::endl;

    // Printing line after the title row
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '-');

    // Printing the actual content of the gameboard
    for (unsigned int i = 0; i < SIZE; ++i)
    {
        std::cout << "| " << i + 1 << " | ";
        for (unsigned int j = 0; j < SIZE; ++j)
        {
            if (number_board_[i][j] == EMPTY)
            {
                std::cout << "  ";
            }

            else
            {
                std::cout << number_board_[i][j] << " ";
            }

        }
        std::cout << "|" << std::endl;
    }

    // Printing lower border
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');
}

void GameBoard::set_type(int x, int y, char input)
{
    if (input == ' ')
    {
        number_board_[x][y] = EMPTY;
    }
    else if (input == '0')
    {
        number_board_[x][y] = ZERO;
    }
    else if (input == '1')
    {
        number_board_[x][y] = ONE;
    }
}

bool GameBoard::is_game_over() const
{
    for (unsigned int y = 0; y < SIZE; ++y)
    {
        for (unsigned int x = 0; x < SIZE; ++x)
        {
            if (number_board_[x][y] == EMPTY)
            {
                return false;
            }
        }
    }
    return true;
}

bool GameBoard::is_bad_seed(unsigned int& seed_to_check) const
{
    for (auto seed : BAD_SEEDS)
    {
        if (seed_to_check == seed)
        {
            return true;
        }
    }
    return false;
}

void GameBoard::print_line(unsigned int length, char fill_character) const
{
    for (unsigned int i = 0; i < length; ++i)
    {
        std::cout << fill_character;
    }
    std::cout << std::endl;
}
