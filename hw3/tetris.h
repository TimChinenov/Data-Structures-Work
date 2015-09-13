#include <iostream>
#include <string>
#include <new>
#include <cassert>
#include <cstdlib>

#ifndef _tetris_h_
#define _tetris_h_
class Tetris 
{
	public:
	Tetris(); // default constructor
	Tetris(int w); //overload constructor
	int get_width() const; // returns the width Tetris
	void add_piece(char letter, int degree, int pos); //adds a piece to board
	int get_max_height() const; //return greatest int in height array
	
	int get_min_height() const;

	int count_squares() const; //returns total squares on the board
	void print() const;
	void destroy();
	int remove_full_rows();
	void remove_empty_columns();
	void add_left_column();
	void add_right_column();
	void remove_left_column();
	void remove_right_column();
	char* empty_array(int size);

	private:
	int width; // single assigned int 
	// an array that holds that tallest point on the board in each column
	int* heights;
	//creates 2D pointer array called Data 
	char** data;
};
#endif