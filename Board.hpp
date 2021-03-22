/**
 * Dynamic Message-Board Exercise - Board.hpp
 * 
 * Author: Jordan Perez
 * Course: C++ @Ariel_University
 * Year: March 2021
 */

#include <string>
#include <vector>
#include "Direction.hpp"


namespace ariel
{
    class Board
    {
        std::vector<std::vector<char>> _board;
        uint _rows;
        uint _cols;

    public:
        Board();
        void post(unsigned int row, unsigned int column, Direction direction, std::string message);
        std::string read(unsigned int row, unsigned int column, Direction direction, unsigned int length);
        void show();
        void resize_rows(unsigned int missing_length);
        void resize_cols(unsigned int missing_length, unsigned int size);
    };
}