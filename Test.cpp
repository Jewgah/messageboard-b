/**
 * Dynamic Message-Board Exercise - Test.cpp
 * 
 * Author: Jordan Perez
 * Course: C++ @Ariel_University
 * Year: March 2021
 */
#include "doctest.h"
#include "Board.hpp"
#include <string>
#include <array>
using namespace ariel;
using namespace std;
#include <iostream>

Board board;
    //INFORMATION : rand() range : rand() % (max_number + 1 - minimum_number) + minimum_number
    //unsigned int value = 0;
    //value = value-1;
    //cout << "value: " << value << "\n"; // prints 4294967295

TEST_CASE("Reading before Posting")
{
    CHECK(board.read(0, 0, Direction::Horizontal, 1) == string("_"));
    CHECK(board.read(0, 0, Direction::Horizontal, 2) == string("__"));
    CHECK(board.read(0, 0, Direction::Vertical, 1) == string("_"));
    CHECK(board.read(1, 5, Direction::Vertical, 2) == string("__"));
    //CHECK(board.read(rand() % (4294967295 + 1), rand() % (4294967295 + 1), Direction::Vertical, 7) == string("_______"));
    //CHECK(board.read(4294967295,4294967295, Direction::Vertical, 7) == string("_______")); // limit of unsigned int range

    unsigned int value = 0;
    value = value-1;
    CHECK(board.read(value,value, Direction::Vertical, 7) == string("_______")); // limit of unsigned int range // working with all compilers
}

TEST_CASE("Test Post, Crossing entries")

{
        unsigned int value = 0;
    value = value-1;
    CHECK_NOTHROW(board.post(0, 0, Direction::Horizontal, "Buddy"));
    CHECK_NOTHROW(board.post(0, 0, Direction::Vertical, "Buddy"));
    CHECK_NOTHROW(board.post(0, 3, Direction::Vertical, "Sacha"));
    CHECK_NOTHROW(board.post(5, 2, Direction::Horizontal, "S"));
    CHECK_NOTHROW(board.post(4, 6, Direction::Horizontal, "Francky"));
    CHECK_NOTHROW(board.post(1, 6, Direction::Vertical, "Nath"));
    CHECK_NOTHROW(board.post(2, 2, Direction::Horizontal, "Cassiopea")); // crossing everything

    //CHECK_NOTHROW(board.post(rand() % (value), rand() % (value), Direction::Horizontal, "Cassiopea")); // crossing everything

    board.show();
    
}
TEST_CASE("Test Read Vertically")
{
    CHECK(board.read(0, 0, Direction::Vertical, 3) == string("Bud"));
    CHECK(board.read(0, 0, Direction::Vertical, 4) == string("Budd"));
    CHECK(board.read(0, 0, Direction::Vertical, 5) == string("Buddy"));
    CHECK(board.read(0, 3, Direction::Vertical, 2) == string("Sa"));
    CHECK(board.read(0, 3, Direction::Vertical, 3) == string("Saa"));
    CHECK(board.read(0, 3, Direction::Vertical, 4) == string("Saah"));
    CHECK(board.read(2, 8, Direction::Vertical, 3) == string("p_a"));
    CHECK(board.read(5, 2, Direction::Vertical, 10) == string("S_________"));
}
TEST_CASE("Test Read Horizontally")
{
    CHECK(board.read(0, 0, Direction::Horizontal, 3) == string("Bud"));
    CHECK(board.read(0, 0, Direction::Horizontal, 4) == string("BudS"));
    CHECK(board.read(0, 0, Direction::Horizontal, 5) == string("BudSy"));
    CHECK(board.read(4, 6, Direction::Horizontal, 3) == string("hra"));
    CHECK(board.read(4, 6, Direction::Horizontal, 4) == string("hran"));
    CHECK(board.read(4, 5, Direction::Horizontal, 5) == string("_hran"));
}


TEST_CASE("Test Edges")
{
    CHECK(board.read(5, 8, Direction::Horizontal, 5) == string("_____"));
    CHECK(board.read(0, 6, Direction::Vertical, 10) == string("_Nith_____"));
    CHECK(board.read(0, 2, Direction::Vertical, 10) == string("d_C__S____"));
    CHECK(board.read(6, 9, Direction::Vertical, 3) == string("___"));
}

TEST_CASE("test Horizontal vs Vertical")
{
    CHECK_NOTHROW(board.post(5, 5, Direction::Horizontal, "hel"));
    CHECK(board.read(5, 5, Direction::Horizontal, 3) == "hel");
    CHECK_FALSE(board.read(5, 5, Direction::Vertical, 3) == "hel");
    CHECK_NOTHROW(board.post(5, 5, Direction::Vertical, "hel"));
    CHECK(board.read(5, 5, Direction::Vertical, 3) == "hel");
    CHECK(board.read(5, 5, Direction::Horizontal, 3) == "hel");
    CHECK_NOTHROW(board.post(3, 3, Direction::Vertical, "hi"));
    CHECK(board.read(3, 3, Direction::Vertical, 2) == "hi");
    CHECK_FALSE(board.read(3, 3, Direction::Horizontal, 2) == "hi");
}

TEST_CASE("Test Read with length==0")
{
    //0,0
    CHECK(board.read(0, 0, Direction::Horizontal, 0) == "");
    CHECK(board.read(0, 0, Direction::Vertical, 0) == "");
    //inside
    CHECK(board.read(5, 4, Direction::Horizontal, 0) == "");
    CHECK(board.read(4, 5, Direction::Vertical, 0) == "");
    //edges
    CHECK(board.read(6, 9, Direction::Horizontal, 0) == "");
    CHECK(board.read(6, 9, Direction::Vertical, 0) == "");
    //outside
    CHECK(board.read(rand() % 100, rand() % 100, Direction::Horizontal, 0) == "");
    CHECK(board.read(rand() % 100, rand() % 100, Direction::Vertical, 0) == "");
}
