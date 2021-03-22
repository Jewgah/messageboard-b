/**
 * Dynamic Message-Board Exercise - Board.cpp
 * 
 * Author: Jordan Perez
 * Course: C++ @Ariel_University
 * Year: March 2021
 */

#include "Board.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

namespace ariel
{
/************************************************ BOARD CONSTRUCTOR *************************************************************/
    Board::Board()
    {
        _rows = 0;
        _cols = 0;
        _board.push_back({'_'}); //we are pushing back a new vector containing the char '_'
       }

/*********************************************** ROWS RESIZER METHOD *************************************************************/
    void Board::resize_rows(unsigned int missing_length){

        // raise board's heigth by missing_length to adapt it
        for (int i = 0; i < missing_length; i++){
            _board.push_back(vector<char>(_board.at(0).size(), '_')); //pushes back a new vector  of size _board.at(0).size() containing only '_'
        }
        _rows = _board.size() - 1; //update _rows to new value

    }

/********************************************* COLUMNS RESIZER METHOD* ***********************************************************/
    void Board::resize_cols(unsigned int missing_length, unsigned int size){

        for (unsigned int i = 0; i < size; i++){
            for (int j = 0; j < missing_length; j++){
                _board.at(i).push_back('_'); // raise board's height by missing_length to adapt it
                }
            }
            _cols = _board.at(0).size() - 1; //update _cols to new value
        
    }

/***************************************************** POST METHOD ****************************************************************/
    void Board::post(unsigned int row, unsigned int column, Direction direction, string message)
    {
        if (message.length() == 0){
            return;
        }

        /******************** Firstly: Resize board if too small *********************/
        if (direction == Direction::Vertical)
        {
            //Resize board's heigth if too small
            if (row + message.length() > _rows)
            {
                resize_rows(row + message.length() - _rows - 1);
            }

            //Resize board's width if too small
            if (column > _cols)
            {
                resize_cols(column- _cols,_rows);
            }
        }
        else // if Direction::Horizontal
        {
            //Resize board's height if too small
            if (row > _rows)
            {
                resize_rows(row-_rows);
            }

            //Resize board's width if too small
            if (column + message.length() > _cols)
            {
                resize_cols(column+message.length()-_cols-1,_board.size()); // board_size == _rows+1
            }
        }
        
    /************************** Secondly: Post message *****************************/
    if (direction == Direction::Vertical){
        for (unsigned int i = 0; i < message.length(); i++){
            _board.at(row + i).at(column) = message.at(i); //writes vertically
        }
    }
    else{ // if Direction::Horizontal
        for (unsigned int i = 0; i < message.length(); i++){
            _board.at(row).at(column + i) = message.at(i); // writes horizontally
        }
    }
}
    
/*************************************************** READ METHOD ************************************************************/
    string Board::read(unsigned int row, unsigned int column, Direction direction, unsigned int length)
    {
        if (length == 0)
        {
            return "";
        }


        // If we start reading outside of the board
        if ((row > _rows && direction == Direction::Vertical) || (column > _cols && direction == Direction::Horizontal))
        {
            string empty_mess;
            for (int i = 0; i < length; i++)
            {
                empty_mess += "_"; //fill string with input length of '_'
            }
            return empty_mess;
        }

        unsigned int missing_length = 0;

        //if the message is read vertically but it gets out of board at the bottom
        if (direction == Direction::Vertical && row + length > _rows)
        {
            missing_length = row + length - _rows - 1;
        }
        //else if the message is read horizontally but it gets out of board at the right
        else if (direction == Direction::Horizontal && column + length > _cols)
        {
            missing_length = column + length - _cols - 1;
        }

        /********** Reads the message ***********/
        string mess;

        if (direction == Direction::Horizontal){
            for (unsigned int i = 0; i < length-missing_length; i++){
                mess += _board.at(row).at(column + i); //reads horizontally
            }
        }

        else{ //if direction == Direction::Vertical
            for (unsigned int i = 0; i < length-missing_length; i++){
                mess += _board.at(row + i).at(column); // reads vertically
            }
        }
    
        //Filling message with all the '_' missing
        for (int i = 0; i < missing_length; i++)
        {
            mess += "_";
        }

        return mess;
    }

/*************************************************** SHOW METHOD ************************************************************/
    void Board::show(){

        /******** prints all board *********/
        // for (unsigned long i = 0; i < _board.size(); i++){
        //     cout << i << ":\t";
        //     for (unsigned long j = 0; j < _board.at(i).size(); j++){
        //         cout << _board.at(i).at(j);
        //     }
        //     cout << endl;
        // }

        /******* prints "reasonably" *******/
        unsigned long min_row = _rows;
        unsigned long min_col = _cols;

        //get the smallest not empty row
        bool breaking_double_loop = true;
        for(unsigned long i = 0; i < _board.size() && breaking_double_loop; i++){
            for (unsigned long j = 0; j < _board.at(i).size() && breaking_double_loop; j++){
                if(_board.at(i).at(j) != '_'){
                    min_row=i;
                    breaking_double_loop = false; //break; only breaks one loop apparently
                }
            }
        }

        //get the smallest not empty column
        for(unsigned long i = 0; i < _board.size(); i++){
            for (unsigned long j = 0; j < _board.at(i).size(); j++){
                if(_board.at(i).at(j) != '_'){
                    if(j<min_col){
                        min_col=j;
                    }
                }
            }
        }

        //cout << "min_row= " << min_row << " & min_col= " << min_col << endl;

        //"Reasonable show" printing only from min_row and min_col
        for (unsigned long i = min_row; i < _board.size(); i++){
            cout << i << ":\t";
            for (unsigned long j = min_col; j < _board.at(i).size(); j++)
            {
                cout << _board.at(i).at(j);
            }
            cout << endl;
        }
    }
}