#include <iostream>
#include <string>
#include <new>
#include "tetris.h"

Tetris::Tetris(){
//default constructor
  width = 6; // set width to 6
  heights = new int [width];
  for (int i = 0; i< width; i++) // asighns values to height
  {
  	heights[i] = 0; 
  }
  data = new char *[width];
}
Tetris::Tetris(int w){
  width = w; // width is w
  heights = new int [width]; // heights is the size of width
  for (int i = 0; i< width; i++)// heights is all 0
  {
  	heights[i] = 0; 
  }
  data = new char *[width]; // point data to char array size of width
}
int Tetris::get_width() const{
	return width; // returns width
}
void Tetris::remove_empty_columns(){
	// this function checks if an array has only blank spaces and then
	//deletes it.
	bool empty = false;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < heights[i]; j++)
		{
			if ((data[i][j] != ' '))
			{// loops through program checking for spaces
				empty = false;
				break;
			}
			else 
			{
				empty = true;
			}
		}
		
		if (empty)
		{// deletes data slot that is found with all blank spaces
			if (heights[i] != 0)
				{delete [] data[i];}
			heights[i] = 0;
		}
	}
}
int Tetris::remove_full_rows(){
	int lowest = get_min_height();
	bool full = false;
	int points = 0;
	if (lowest == 0)
		return points;
	//boolean check that goes through each slow
	// and checks if each slot is full
	for (int i = (lowest - 1); i >= 0; i = i -1)
	{
		full = false;
		for (int j = 0; j < width; j++)
		{//if slots are 0 height or no spaces are found 
			//proceeds to next loop
			if (heights[j] == 0)
			{
				full = false;
				break;
			}
			if (data[j][i] == ' ')
			{
				full = false;
				break;
			}
			else 
			{
				full = true;
			}
		}
		
		if (full == true)
		{//copys old data to new array while skipping line 
			//that is the same as i
			
			points++;
			for (int k = 0; k < width; k++)
			{
				char *temparray;
				if (heights[k] -1 < 0)
					continue;
				if (heights[k] -1 != 0)
					temparray = new char[(heights[k] - 1)];
				int count = 0;
				for (int l = 0; l < heights[k]; l++ )
				{

					if (l == i)
					{	//skipps line when i = l and does not copy that line t
						//to the new array
						continue;
					}

					temparray[count] = data[k][l];
					count++;
				}
				//deletes old data slots to avoid memory leaks
				if (heights[k] != 0)
					delete [] data[k];
				data[k] = temparray;
				heights[k]--;
				remove_empty_columns();

			}
			full = false;
		}
				
	}
	return points;
}
int Tetris::get_max_height() const {
	//this function finds the max hight in data arrays
	int highest = 0;
	const int *i;
	for (i = heights; i < heights + width; i++)
	{// loops through the array if the size of height is greater than 
		//highest then, replaces the current height with highest.
		if (*i > highest)
			highest = *i;
	}
	return highest;
}
int Tetris::get_min_height() const{
	//finds the highest minimum height. this line is 
	//the line all the lines have in common.
	int lowest = heights[0];
	const int *i;
	for (i = heights; i < heights + width; i++)
	{// this line is the top most full row.
		if (*i < lowest)
			lowest = *i;
	}
	return lowest;
}
int Tetris::count_squares() const{
	// goes line by line adding every char that is not a space
	// to a total
	int total = 0;
	for (int i = 0; i < width; i++)
	{
		if (heights[i] != 0)
		{
			for (int j = 0; j < heights[i]; j++)
			{
				if (data[i][j] != ' ' )
					total++;
				//adds 1 to total
			}
		}
	}
	return total;
}

void Tetris::destroy(){
	for (int row = 0; row < width; row++)
	{//goes line by line destroys each arrray in
		//the forst data pointer 
		if (heights[row] > 0)
			delete [] data[row];
	}
	//deletes data  and deletes height
	delete [] data;
	delete [] heights;
}

void Tetris::add_left_column(){
	// increases width by one
	width++;
	char** tempdata = new char *[width];
	int *tempheights = new int [width];
	int count = 1;
	//copys line by line to a new array and adds an extra space in the 
	//begining of data. This can later be filled in with an array
	for (int i = 0; i < width -1; i++)
	{	
		tempheights[count] = heights[i];
		if (tempheights[count] != 0)
			tempdata[count] = data[i];
		count++;
	}// delete hights and data afterwards
	tempheights[0] = 0;
	delete [] heights;
	delete[] data;
	heights = tempheights;
	data = tempdata;
}

void Tetris::add_right_column(){
	// does that samething as add_left_column except adds extra array
	//space to the end of data* instead of the begining. 
	width++;
	char** tempdata = new char *[width];
	int *tempheights = new int [width];
	for (int i = 0; i < width -1; i++)
	{
		tempheights[i] = heights[i];
		if (tempheights[i] != 0)
			tempdata[i] = data[i];
	}
	//delete heights and data afterwards to avoid memory leaks that 
	//are definetly not here.
	tempheights[width - 1] = 0;
	delete [] heights;
	delete[] data;
	heights = tempheights;
	data = tempdata;
}

void Tetris::remove_left_column(){
	// removes left column by copying line by line into new array while 
	//avoiding the left most row aka the first more row.
	width--;
	char** tempdata = new char *[width];
	int *tempheights = new int [width];
	int count = 0;
	for (int i = 1; i < width + 1; i++)
	{
		tempheights[count] = heights[i];
		if (tempheights[count] != 0)
			tempdata[count] = data[i];
		count++;
	}
	// removes all heights and data.
	delete [] heights;
	delete [] data;
	heights = tempheights;
	data = tempdata;
}
void Tetris::remove_right_column(){
	//removes the right column by decreasing width and copying all the
	// lines of data intp a temp data. does not copy the final though.
	//this is the right most line.
	width--;
	char** tempdata = new char *[width];
	int *tempheights = new int [width];
	for (int i = 0; i < width; i++)
	{
		tempheights[i] = heights[i];
		if (tempheights[i] != 0)
			tempdata[i] = data[i];
	}
	delete [] data;
	delete [] heights;
	heights = tempheights;
	data = tempdata;
}
char* Tetris::empty_array( int size ){
	char *temparray =  new char [size];
		//fills all positions in the array with spaces
		for (int k = 0; k < size; k++)
		{
			temparray[k] = ' ';
		}
	return temparray;
}

void Tetris::add_piece(char letter, int degree, int pos){
	///begins the long process of adding new pieces 
	// this entire function is a huge if statement that checks which
	// what the letter is, what is it's degree and orientation
	//and places the letter in the appropriate slots. A lot of the letters
	//after T stop being commented as the code repeats a lot.
	////////////////////////////////////////////////////////////////////
	if (letter == 'O')
	{
		if (heights[pos] == 0 && heights[pos+1] == 0)
		{	
			for (int i = pos; i < (pos+2); i++)
			{
				char *temparray = new char[2];
				temparray[0] = 'O';
				temparray[1] = 'O';
				data[i] = temparray;
				heights[i] = 2;
			}
		} 
		else  
		{
			int largest_height = 0; //holds greatest height int
			//for loop finds greatest height in range of position
			for (int i = pos; i <= pos+1; i++)
			{
				if (heights[i] > largest_height)
					largest_height = heights[i];
			}
		//for loop makes copy of the current array. Then an array of size
		//largest height + 2 is made. The current copy array reads in each
		//index into the new array and then adds 'O' in the last two positions 
			for (int i = pos; i <= pos+1; i++)
			{
				char *temparray =  new char [largest_height+2];
				//fills all positions in the array with spaces
				for (int k = 0; k < largest_height+2; k++)
				{
					temparray[k] = ' ';
				}
				for(int j = 0; j < heights[i]; j++)
				{
					temparray[j] = data[i][j];
				}
				//adds two o's to the top of the new line
				temparray[largest_height] = 'O';
				temparray[largest_height+1] = 'O';
				
				//redundant engineering. Avoids memory leeks.
				if (heights[i] != 0) 
					delete [] data[i];

				data[i] = temparray;
				heights[i] = largest_height+2;
			}
		} 

	}
	//places I shape into array
	/////////////////////////////////////////////////////////////////
	else if (letter == 'I')
	{
		//seperates possibilities by angles
		if (degree == 0 || degree == 180)
		{
			///assumes the current array is empty
			if (heights[pos] == 0)
			{
				
				char *temparray = new char[4];
				for (int k = 0; k < 4; k++)
				{
					temparray[k] = 'I';
				}
				data[pos] = temparray;
				heights[pos] = 4;	
			}
			///assuming the array is not empty
			else
			{
				int largest_height = 0; //holds greatest height int
			//for loop finds greatest height in range of position
				for (int i = pos; i <= pos+1; i++)
				{
					if (heights[i] > largest_height)
						largest_height = heights[i];
				}
		//for loop makes copy of the current array. Then an array of size
		//largest height + 4 is made. The current copy array reads in each
		//index into the new array and then adds 'O' in the last two positions 
				char *temparray =  new char [largest_height+4];
				//fills all positions in the array with spaces
				for (int k = 0; k < largest_height+4; k++)
				{
					temparray[k] = ' ';
				}
				for(int j = 0; j < heights[pos]; j++)
				{
					temparray[j] = data[pos][j];
			    }
				for (int t = largest_height; t < largest_height + 4; t++)
				{
					temparray[t] = 'I';
				}
				delete [] data[pos];
				data[pos] = temparray;
				heights[pos] = largest_height+4;
			}
		}
		else if (degree == 90 || degree == 270) 
		{ // if The asked for orientation is either 90 or 270
			// I will print out in a straight pattern
			if (heights[pos] == 0 && heights[pos + 1] == 0 
				&& heights[pos + 2] == 0 && heights[pos + 3] == 0)
			{
				for (int i = pos; i < pos+4; i++)
				{// this for loop adds one I on top of the current
					//array until 4 I's have been stacked.
					char *temparray = new char[1];
					temparray[0] = 'I'; 
					data[i] = temparray;
					heights[i]++;
				}
			}
			else
			{
				int largest_height = 0; //holds greatest height int
			//for loop finds greatest height in range of position
				for (int i = pos; i <= pos+3; i++)
				{
					if (heights[i] > largest_height)
						largest_height = heights[i];
				}
				for (int i = pos; i <= pos+3; i++)
				{
					char *temparray =  new char [largest_height+1];
					//fills all positions in the array with spaces
					for (int k = 0; k < largest_height+1; k++)
					{
						temparray[k] = ' ';
					}

					for(int j = 0; j < heights[i]; j++)
					{
						temparray[j] = data[i][j];
					}
					temparray[largest_height] = 'I';
	
					if (heights[i] != 0)
						delete [] data[i];
					data[i] = temparray;
					heights[i] = largest_height+1;
				}
			}

		}
	}
	////////////////////////////////////////////////////////////////////////
	else if (letter == 'T')
	{
		//for degree 0
		if (degree == 0)
		{
			//checks if all three adjacent positions are empty
			if (heights[pos] == 0 && heights[pos+1] == 0 && heights[pos+2] == 0)
			{
				//first line of T
				char *temparray = new char [2];
				temparray[0] = ' ';
				temparray[1] = 'T';
				data[pos] = temparray;
				heights[pos] = 2;
				//second line of T
				temparray = new char [2];
				temparray[0] = 'T';
				temparray[1] = 'T';
				data[pos+1] = temparray;
				heights[pos+1] = 2;
				//Third line of T
				temparray = new char [2];
				temparray[0] = ' ';
				temparray[1] = 'T';
				data[pos+2] = temparray;
				heights[pos+2] = 2;
			}
			//if the three adjacent positions are not empty
			else
			{
				int largest_height = 0; //holds greatest height int
			//for loop finds greatest height in range of position
				for (int i = pos; i <= pos+2; i++)
				{
					if (heights[i] > largest_height)
						largest_height = heights[i];
				}
				//create empty array full of spaces
				char *temparray =  empty_array(largest_height + 2);
				for(int j = 0; j < heights[pos]; j++)
					{
						temparray[j] = data[pos][j];
						//points the old data line to the new templine
					}
					//adds these two parts on top of the line to add new shape
					temparray[largest_height] = ' '; 
					temparray[largest_height + 1] = 'T';
					if (heights[pos] != 0)
						delete [] data[pos];
					data[pos] = temparray;
					heights[pos] = largest_height + 2;
					
				temparray =  empty_array(largest_height + 2);
				for(int j = 0; j < heights[pos+1]; j++)
					{
						temparray[j] = data[pos+1][j];
					}
					temparray[largest_height] = 'T'; 
					temparray[largest_height + 1] = 'T';
					if (heights[pos + 1] != 0)
						delete [] data[pos + 1];
					data[pos+1] = temparray;
					heights[pos+1] = largest_height + 2;

				temparray =  empty_array(largest_height + 2);	
				for(int j = 0; j < heights[pos+2]; j++)
					{
						temparray[j] = data[pos+2][j];
					}
					temparray[largest_height] = ' '; 
					temparray[largest_height + 1] = 'T';
					if (heights[pos+2] != 0)
						delete [] data[pos+2];
					data[pos+2] = temparray;
					heights[pos+2] = largest_height + 2;
					
			}
		}
		else if (degree == 90)
		{
			//checks if all three adjacent positions are empty
			if (heights[pos] == 0 && heights[pos+1] == 0)
			{
				//first line of T
				char *temparray = new char [3];
				temparray[0] = 'T';
				temparray[1] = 'T';
				temparray[2] = 'T';
				data[pos] = temparray;
				heights[pos] = 3;
				//second line of T
				temparray = new char [2];
				temparray[0] = ' ';
				temparray[1] = 'T';
				data[pos+1] = temparray;
				heights[pos+1] = 2;
			}
			//if the three adjacent positions are not empty
			else
			{
				int largest_height = 0; //holds greatest height int
			//for loop finds greatest height in range of position
				for (int i = pos; i <= pos+1; i++)
				{
					if (heights[i] > largest_height)
						largest_height = heights[i];
				}
				///adds TTT
				char *temparray =  empty_array(largest_height + 3);
				for(int j = 0; j < heights[pos]; j++)
					{
						temparray[j] = data[pos][j];
					}
					temparray[largest_height] = 'T'; 
					temparray[largest_height + 1] = 'T';
					temparray[largest_height + 2] = 'T';
					if (heights[pos] != 0)
						delete [] data[pos];
					data[pos] = temparray;
					heights[pos] = largest_height + 3;
				// adds '  T' to array	
				temparray =  empty_array(largest_height + 2);
				for(int j = 0; j < heights[pos+1]; j++)
					{
						temparray[j] = data[pos+1][j];
					}
					temparray[largest_height] = ' '; 
					temparray[largest_height + 1] = 'T';
					if (heights[pos + 1] != 0)
						delete [] data[pos + 1];
					data[pos+1] = temparray;
					heights[pos+1] = largest_height + 2;
			}
		}
		else if (degree == 180)
		{
			//checks if all three adjacent positions are empty
			if (heights[pos] == 0 && heights[pos+1] == 0 && heights[pos+2] == 0)
			{
				//first line of T
				char *temparray = new char [1];
				temparray[0] = 'T';
				data[pos] = temparray;
				heights[pos] = 1;
				//second line of T
				temparray = new char [2];
				temparray[0] = 'T';
				temparray[1] = 'T';
				data[pos+1] = temparray;
				heights[pos+1] = 2;
				//Third line of T
				temparray = new char [1];
				temparray[0] = 'T';
				data[pos+2] = temparray;
				heights[pos+2] = 1;
			}
			//if the three adjacent positions are not empty
			else
			{
				int largest_height = 0; //holds greatest height int
			//for loop finds greatest height in range of position
				for (int i = pos; i <= pos+2; i++)
				{
					if (heights[i] > largest_height)
						largest_height = heights[i];
				}
				//create empty array full of spaces
				char *temparray =  empty_array(largest_height + 1);
				for(int j = 0; j < heights[pos]; j++)
					{
						temparray[j] = data[pos][j];
					}
					temparray[largest_height] = 'T'; 
					if (heights[pos] != 0)
						delete [] data[pos];
					data[pos] = temparray;
					heights[pos] = largest_height + 1;
					
				temparray =  empty_array(largest_height + 2);
				for(int j = 0; j < heights[pos+1]; j++)
					{
						temparray[j] = data[pos+1][j];
					}
					temparray[largest_height] = 'T'; 
					temparray[largest_height + 1] = 'T';
					if (heights[pos + 1] != 0)
						delete [] data[pos + 1];
					data[pos+1] = temparray;
					heights[pos+1] = largest_height + 2;

				temparray =  empty_array(largest_height + 1);
				for(int j = 0; j < heights[pos+2]; j++)
					{
						temparray[j] = data[pos+2][j];
					}
					temparray[largest_height] = 'T'; 
					if (heights[pos+2] != 0)
						delete [] data[pos+2];
					data[pos+2] = temparray;
					heights[pos+2] = largest_height + 1;
					
			}
		}
		else if (degree == 270)
		{
			//checks if all three adjacent positions are empty
			if (heights[pos] == 0 && heights[pos+1] == 0)
			{
				//first line of T
				char *temparray = new char [2];
				temparray[0] = ' ';
				temparray[1] = 'T';
				data[pos] = temparray;
				heights[pos] = 2;
				//second line of T
				temparray = new char [3];
				temparray[0] = 'T';
				temparray[1] = 'T';
				temparray[2] = 'T';
				data[pos+1] = temparray;
				heights[pos+1] = 3;
			}
			//if the three adjacent positions are not empty
			else
			{
				int largest_height = 0; //holds greatest height int
			//for loop finds greatest height in range of position
				for (int i = pos; i <= pos+1; i++)
				{
					if (heights[i] > largest_height)
						largest_height = heights[i];
				}
				///adds TTT
				char *temparray =  empty_array(largest_height + 2);
				for(int j = 0; j < heights[pos]; j++)
					{
						temparray[j] = data[pos][j];
					}
					temparray[largest_height] = ' '; 
					temparray[largest_height + 1] = 'T';
					if (heights[pos] != 0)
						delete [] data[pos];
					data[pos] = temparray;
					heights[pos] = largest_height + 2;
				// adds '  T' to array	
				temparray =  empty_array(largest_height + 3);
				for(int j = 0; j < heights[pos+1]; j++)
					{
						temparray[j] = data[pos+1][j];
					}
					temparray[largest_height] = 'T'; 
					temparray[largest_height + 1] = 'T';
					temparray[largest_height + 2] = 'T';
					if (heights[pos + 1] != 0)
						delete [] data[pos + 1];
					data[pos+1] = temparray;
					heights[pos+1] = largest_height + 3;
			}
	 	}
	} 
	//////////////////////////////////////////////////////////////////////////
	else if (letter == 'J')
	{
		if (degree == 0) //if 0 degree spin
		{
			if (heights[pos] == 0, heights[pos+1] == 0)
			{
				//second line of J
				char *temparray = new char [3];
				temparray[0] = 'J';
				temparray[1] = 'J';
				temparray[2] = 'J';
				data[pos+1] = temparray;
				heights[pos+1] = 3;
				//first line of J
				temparray = new char [1];
				temparray[0] = 'J';
				data[pos] = temparray;
				heights[pos] = 1;
			}
			///IF FIELD IS NOT EMPTY
			else
			{
				int largest_height = 0; //holds greatest height int
			//for loop finds greatest height in range of position
				for (int i = pos; i <= pos+1; i++)
				{
					if (heights[i] > largest_height)
						largest_height = heights[i];
				}
				char *temparray =  empty_array(largest_height + 3);
				for(int j = 0; j < heights[pos]; j++)
					{
						temparray[j] = data[pos][j];
					}
				temparray[largest_height] = 'J'; 
				temparray[largest_height + 1] = 'J';
				temparray[largest_height + 2] = 'J';
				if (heights[pos] != 0)
						delete [] data[pos];
				data[pos] = temparray;
				heights[pos] = largest_height + 3;

				temparray =  empty_array(largest_height + 1);
				for(int j = 0; j < heights[pos+1]; j++)
					{
						temparray[j] = data[pos+1][j];
					}	
				temparray[largest_height] = 'J';
				if (heights[pos+1] != 0)
						delete [] data[pos + 1];
				data[pos+1] = temparray;
				heights[pos+1] = largest_height + 1;
			}
		}
		else if (degree == 90) // if 90 degree spin
		{
			if (heights[pos] == 0 && heights[pos+1] == 0 && heights[pos+2] == 0)
			{
				char *temparray = new char [2];
				temparray[0] = 'J';
				temparray[1] = 'J';
				data[pos+2] = temparray;
				heights[pos+2] = 2;
				//makes the last two J
				for (int i = pos; i <= pos+1; i++)
				{
					char *temparray = new char [1];
					temparray[0] = 'J';
					data[i] = temparray;
					heights[i] = 1;
				}
			}
			else//IF NOT EMPTY FOR 90 DEG J
			{
				int largest_height = 0; //holds greatest height int
			//for loop finds greatest height in range of position
				for (int i = pos; i <= pos+2; i++)
				{
					if (heights[i] > largest_height)
						largest_height = heights[i];
				}
				char *temparray =  empty_array(largest_height + 2);
				for(int j = 0; j < heights[pos+2]; j++)
					{
						temparray[j] = data[pos+2][j];
					}
				temparray[largest_height] = 'J';
				temparray[largest_height +1] = 'J';
				if (heights[pos] != 0)
						delete [] data[pos+2];
				data[pos+2] = temparray;
				heights[pos+2] = largest_height + 2;

				for( int k = 0; k <= 1; k++)
				{
					char *temparray =  empty_array(largest_height + 2);
					for(int j = 0; j < heights[pos + k]; j++)
						{
							temparray[j] = data[pos + k][j];
						}
				temparray[largest_height] = ' ';
				temparray[largest_height +1 ] = 'J';
				if (heights[pos + k] != 0)
						delete [] data[pos + k];
				data[pos + k] = temparray;
				heights[pos + k] = largest_height + 2;
				}

			}
		}
		else if (degree == 180) // if 180 degree spin
		{
			if (heights[pos] == 0, heights[pos+1] == 0)
			{
				//first line of J
				char *temparray = new char [3];
				temparray[0] = 'J';
				temparray[1] = 'J';
				temparray[2] = 'J';
				data[pos] = temparray;
				heights[pos] = 3;
				//second line of J
				temparray = new char [3];
				temparray[0] = 'J';
				temparray[1] = ' ';
				temparray[2] = ' ';
				data[pos+1] = temparray;
				heights[pos+1] = 3;
			}
			else//IF NOT EMPTY FOR J 180
			{
				int largest_height = 0; //holds greatest height int
			//for loop finds greatest height in range of position
				for (int i = pos; i <= pos+1; i++)
				{
					if (heights[i] > largest_height)
						largest_height = heights[i];
				}
				char *temparray =  empty_array(largest_height + 3);
				for(int j = 0; j < heights[pos]; j++)
					{
						temparray[j] = data[pos][j];
					}
				temparray[largest_height] = 'J'; 
				temparray[largest_height + 1] = 'J';
				temparray[largest_height + 2] = 'J';
				if (heights[pos] != 0)
						delete [] data[pos];
				data[pos] = temparray;
				heights[pos] = largest_height + 3;

				temparray =  empty_array(largest_height + 3);
				for(int j = 0; j < heights[pos+1]; j++)
					{
						temparray[j] = data[pos+1][j];
					}	
				temparray[largest_height] = ' ';
				temparray[largest_height + 1] = ' ';
				temparray[largest_height + 2] = 'J';
				if (heights[pos+1] != 0)
						delete [] data[pos + 1];
				data[pos+1] = temparray;
				heights[pos+1] = largest_height + 1;
			}
		}
		else if (degree == 270) //if 170 degree spin
		{
			if (heights[pos] == 0 && heights[pos+1] == 0 && heights[pos+2] == 0)
			{
				char *temparray = new char [2];
				temparray[0] = 'J';
				temparray[1] = 'J';
				data[pos +2] = temparray;
				heights[pos +2] = 2;
				//makes the last two J
				for (int i = pos; i <= pos+1; i++)
				{
					char *temparray = new char [2];
					temparray[0] = ' ';
					temparray[2] = 'J';
					data[i] = temparray;
					heights[i] = 1;
				}
			}
			else //IF J IS 270 DEG AND BOARD EMPTY
			{
				int largest_height = 0; //holds greatest height int
			//for loop finds greatest height in range of position
				for (int i = pos; i <= pos+2; i++)
				{
					if (heights[i] > largest_height)
						largest_height = heights[i];
				}
				char *temparray =  empty_array(largest_height + 2);
				for(int j = 0; j < heights[pos+2]; j++)
					{
						temparray[j] = data[pos+2][j];
					}
				temparray[largest_height] = 'J';
				temparray[largest_height +1] = 'J';
				if (heights[pos] != 0)
						delete [] data[pos];
				data[pos] = temparray;
				heights[pos] = largest_height + 2;

				for( int k = 0; k <= 1; k++)
				{
					char *temparray =  empty_array(largest_height + 1);
					for(int j = 0; j < heights[pos + k]; j++)
						{
							temparray[j] = data[pos + k][j];
						}
				temparray[largest_height] = 'J';
				if (heights[pos + k] != 0)
						delete [] data[pos + k];
				data[pos + k] = temparray;
				//increase height
				heights[pos + k] = largest_height + 1;
				}
			}
		}
	}
	///////////////////////////////////////////////////////////////////////////
	else if (letter == 'L')
	{
		if (degree == 0)
		{
			if (heights[pos] == 0, heights[pos+1] == 0)
			{
				//second line of L
				char *temparray = new char [3];
				temparray[0] = 'L';
				temparray[1] = 'L';
				temparray[2] = 'L';
				data[pos] = temparray;
				heights[pos] = 3;
				//first line of L
				temparray = new char [1];
				temparray[0] = 'L';
				data[pos+1] = temparray;
				heights[pos+1] = 1;
			}
			else
			{
				int largest_height = 0; //holds greatest height int
			//for loop finds greatest height in range of position
				for (int i = pos; i <= pos+1; i++)
				{
					if (heights[i] > largest_height)
						largest_height = heights[i];
				}

				char *temparray =  empty_array(largest_height + 3);
				for(int j = 0; j < heights[pos]; j++)
					{
						temparray[j] = data[pos][j];
					}
				temparray[largest_height] = 'L'; 
				temparray[largest_height + 1] = 'L';
				temparray[largest_height + 2] = 'L';
				if (heights[pos] != 0)
						delete [] data[pos];
				data[pos] = temparray;
				heights[pos] = largest_height + 3;

				temparray =  empty_array(largest_height + 1);
				for(int j = 0; j < heights[pos + 1]; j++)
					{
						temparray[j] = data[pos+1][j];
					}	
				temparray[largest_height] = 'L';
				if (heights[pos+1] != 0)
						delete [] data[pos +1];
				data[pos +1] = temparray;
				heights[pos+1] = largest_height + 1;
			}
		}
		else if (degree == 90)
		{
			if (heights[pos] == 0 && heights[pos+1] == 0 && heights[pos+2] == 0)
			{
				char *temparray = new char [2];
				temparray[0] = 'L';
				temparray[1] = 'L';
				data[pos+2] = temparray;
				heights[pos+2] = 2;
				//makes the first two 'L'
				for (int i = pos; i <= pos+1; i++)
				{
					char *temparray = new char [1];
					temparray[0] = 'L';
					data[i] = temparray;
					heights[i] = 1;
				}
			}
			else //L 90 DEG AND BOARD IS NOT EMPTY
			{
				int largest_height = 0; //holds greatest height int
			//for loop finds greatest height in range of position
				for (int i = pos; i <= pos+2; i++)
				{
					if (heights[i] > largest_height)
						largest_height = heights[i];
				}

				char *temparray =  empty_array(largest_height + 2);
				for(int j = 0; j < heights[pos+2]; j++)
					{
						temparray[j] = data[pos+2][j];
					}
				temparray[largest_height] = 'L';
				temparray[largest_height +1] = 'L';
				if (heights[pos+2] != 0)
						delete [] data[pos+2];
				data[pos+2] = temparray;
				heights[pos+2] = largest_height + 2;

				for( int k = 0; k <= 1; k++)
				{
					char *temparray =  empty_array(largest_height + 1);
					for(int j = 0; j < heights[pos + k]; j++)
						{
							temparray[j] = data[pos + k][j];
						}
				temparray[largest_height] = 'L';
				if (heights[pos + k] != 0)
						delete [] data[pos + k];
				data[pos + k] = temparray;
				heights[pos + k] = largest_height + 1;
				}
			}
		}
		else if (degree == 180)
		{
			if (heights[pos] == 0, heights[pos+1] == 0)
			{
				//second line of L
				char *temparray = new char [3];
				temparray[0] = 'L';
				temparray[1] = 'L';
				temparray[2] = 'L';
				data[pos+1] = temparray;
				heights[pos+1] = 3;
				//first line of L
				temparray = new char [3];
				temparray[0] = ' ';
				temparray[1] = ' ';
				temparray[2] = 'L';
				data[pos] = temparray;
				heights[pos] = 1;
			}
			else// L board is not empty and 180 deg
			{
				int largest_height = 0; //holds greatest height int
			//for loop finds greatest height in range of position
				for (int i = pos; i <= pos+1; i++)
				{
					if (heights[i] > largest_height)
						largest_height = heights[i];
				}

				char *temparray =  empty_array(largest_height + 3);
				for(int j = 0; j < heights[pos+1]; j++)
					{
						temparray[j] = data[pos+1][j];
					}
				temparray[largest_height] = 'L'; 
				temparray[largest_height + 1] = 'L';
				temparray[largest_height + 2] = 'L';
				if (heights[pos +1] != 0)
						delete [] data[pos +1];
				data[pos +1] = temparray;
				heights[pos+1] = largest_height + 3;

				temparray =  empty_array(largest_height + 3);
				for(int j = 0; j < heights[pos]; j++)
					{
						temparray[j] = data[pos][j];
					}	
				temparray[largest_height] = ' ';
				temparray[largest_height+1] = ' ';
				temparray[largest_height+2] = 'L';
				if (heights[pos] != 0)
						delete [] data[pos];
				data[pos] = temparray;
				heights[pos] = largest_height + 3;
			}
		}
		else if (degree == 270)
		{
			if (heights[pos] == 0 && heights[pos+1] == 0 && heights[pos+2] == 0)
			{
				char *temparray = new char [2];
				temparray[0] = 'L';
				temparray[1] = 'L';
				data[pos] = temparray;
				heights[pos] = 2;
				//makes the last two L's
				for (int i = pos+1; i <= pos+2; i++)
				{
					char *temparray = new char [2];
					temparray[0] = ' ';
					temparray[2] = 'L';
					data[i] = temparray;
					heights[i] = 1;
				}
			}
			else//270 DEG BOARD IS NOT EMPTY L
			{
				int largest_height = 0; //holds greatest height int
			//for loop finds greatest height in range of position
				for (int i = pos; i <= pos+2; i++)
				{
					if (heights[i] > largest_height)
						largest_height = heights[i];
				}

				char *temparray =  empty_array(largest_height + 2);
				for(int j = 0; j < heights[pos]; j++)
					{
						temparray[j] = data[pos][j];
					}
				temparray[largest_height] = 'L';
				temparray[largest_height +1] = 'L';
				if (heights[pos] != 0)
						delete [] data[pos];
				data[pos] = temparray;
				heights[pos] = largest_height + 2;

				for( int k = 1; k <= 2; k++)
				{
					char *temparray =  empty_array(largest_height + 1);
					for(int j = 0; j < heights[pos + k]; j++)
						{
							temparray[j] = data[pos + k][j];
						}
				temparray[largest_height] = 'L';
				if (heights[pos + k] != 0)
						delete [] data[pos + k];
				data[pos + k] = temparray;
				heights[pos + k] = largest_height + 1;
				}
			}
		}
	}
	///////////////////////////////////////////////////////////////////////////
	else if (letter == 'Z')
	{
		if (degree == 0 || degree == 180 )
		{
			if (heights[pos] == 0 && heights[pos+1] == 0 && heights[pos+2] == 0)
			{
				//first part of z
				char *temparray = new char [2];
				temparray[0] == ' ';
				temparray[1] == 'Z';
				data[pos] = temparray;
				heights[pos] = 2;
				//second part of ZZ
				temparray = new char [2];
				temparray[0] == 'Z';
				temparray[1] == 'Z';
				data[pos+1] = temparray;
				heights[pos+1] = 2;
				//Third part of Z
				temparray = new char [1];
				temparray[0] = 'Z';
				data[pos+2] = temparray;
				heights[pos+2] = 1;
			}
			else //z is 0 or 180 degrees and board is not empty
			{
				int largest_height = 0; //holds greatest height int
			//for loop finds greatest height in range of position
				for (int i = pos; i <= pos+2; i++)
				{
					if (heights[i] > largest_height)
						largest_height = heights[i];
				}

				char *temparray =  empty_array(largest_height + 2);
				for(int j = 0; j < heights[pos]; j++)
					{
						temparray[j] = data[pos][j];
					}
				temparray[largest_height] = ' ';
				temparray[largest_height +1] = 'Z';
				if (heights[pos] != 0)
						delete [] data[pos];
				data[pos] = temparray;
				heights[pos] = largest_height + 2;

				temparray = empty_array(largest_height + 2);
				for(int j = 0; j < heights[pos+1]; j++)
					{
						temparray[j] = data[pos+1][j];
					}
				temparray[largest_height] = 'Z';
				temparray[largest_height +1] = 'Z';
				if (heights[pos+1] != 0)
						delete [] data[pos+1];
				data[pos+1] = temparray;
				heights[pos+1] = largest_height + 2;

				temparray = empty_array(largest_height + 1);
				for(int j = 0; j < heights[pos+2]; j++)
					{
						temparray[j] = data[pos+2][j];
					}
				temparray[largest_height] = 'Z';
				if (heights[pos+2] != 0)
						delete [] data[pos+2];
				data[pos+2] = temparray;
				heights[pos+2] = largest_height + 1;
			}

		}
		else if (degree == 90 || degree == 270)
		{
			if (heights[pos] =+ 0 && heights[pos+1] == 0)
			{
			//first part of ZZ
			char *temparray = new char [2];
			temparray[0] = 'Z';
			temparray[1] = 'Z';
			data[pos] = temparray;
			heights[pos] = 2;
			//second prat of ' ZZ'
			temparray = new char [3];
			temparray[0] = ' ';
			temparray[1] = 'Z';
			temparray[2] = 'Z';
			data[pos+1] = temparray;
			heights[pos+1] = 3;
			}
			else // Z 90 270 if board is not empty 
			{
				int largest_height = 0; //holds greatest height int
			//for loop finds greatest height in range of position
				for (int i = pos; i <= pos+1; i++)
				{
					if (heights[i] > largest_height)
						largest_height = heights[i];
				}

				char *temparray =  empty_array(largest_height + 2);
				for(int j = 0; j < heights[pos]; j++)
					{
						temparray[j] = data[pos][j];
					}
				temparray[largest_height] = 'Z';
				temparray[largest_height +1] = 'Z';
				if (heights[pos] != 0)
						delete [] data[pos];
				data[pos] = temparray;
				heights[pos] = largest_height + 2;

				temparray = empty_array(largest_height + 3);
				for(int j = 0; j < heights[pos+1]; j++)
					{
						temparray[j] = data[pos+1][j];
					}
				temparray[largest_height] = ' ';
				temparray[largest_height+1] = 'Z';
				temparray[largest_height+2] = 'Z';
				if (heights[pos+1] != 0)
						delete [] data[pos+1];
				data[pos+1] = temparray;
				heights[pos+1] = largest_height + 3;
			}
		}
	}
	///////////////////////////////////////////////////////////////////////////
	else if (letter == 'S')
	{
		if (degree == 0 || degree == 180)
		{
			if (heights[pos] == 0 && heights[pos+1] == 0 && heights[pos+2] == 0)
			{
				//first part of z
				char *temparray = new char [1];
				temparray[0] == 'S';
				data[pos] = temparray;
				heights[pos] = 1;
				//second part of ZZ
				temparray = new char [2];
				temparray[0] == 'S';
				temparray[1] == 'S';
				data[pos+1] = temparray;
				heights[pos+1] = 2;
				//Third part of Z
				temparray = new char [2];
				temparray[0] = ' ';
				temparray[1] = 'S';
				data[pos+2] = temparray;
				heights[pos+2] = 2;
			}
			else //z is 0 or 180 degrees and board is not empty
			{
				int largest_height = 0; //holds greatest height int
			//for loop finds greatest height in range of position
				for (int i = pos; i <= pos+2; i++)
				{
					if (heights[i] > largest_height)
						largest_height = heights[i];
				}
				char *temparray =  empty_array(largest_height + 1);
				for(int j = 0; j < heights[pos]; j++)
					{
						temparray[j] = data[pos][j];
					}
				temparray[largest_height] = 'S';
				if (heights[pos] != 0)
						delete [] data[pos];
				data[pos] = temparray;
				heights[pos] = largest_height + 1;

				temparray = empty_array(largest_height + 2);
				for(int j = 0; j < heights[pos+1]; j++)
					{
						temparray[j] = data[pos+1][j];
					}
				temparray[largest_height] = 'S';
				temparray[largest_height +1] = 'S';
				if (heights[pos+1] != 0)
						delete [] data[pos+1];
				data[pos+1] = temparray;
				heights[pos+1] = largest_height + 2;

				temparray = empty_array(largest_height + 2);
				for(int j = 0; j < heights[pos+2]; j++)
					{
						temparray[j] = data[pos+2][j];
					}
				temparray[largest_height] = ' ';
				temparray[largest_height +1 ] = 'Z';
				if (heights[pos+2] != 0)
						delete [] data[pos+2];
				data[pos+2] = temparray;
				heights[pos+2] = largest_height + 2;
			}
		}
		else if (degree == 90 || degree == 270)
		{
			if (heights[pos] =+ 0 && heights[pos+1] == 0)
			{
			//second part of ZZ
			char *temparray = new char [2];
			temparray[0] = 'S';
			temparray[1] = 'S';
			data[pos+1] = temparray;
			heights[pos+1] = 2;
			//first prat of ' ZZ'
			temparray = new char [3];
			temparray[0] = ' ';
			temparray[1] = 'S';
			temparray[2] = 'S';
			data[pos] = temparray;
			heights[pos] = 3;
			}
			else // Z 90 270 if board is not empty for S
			{
				int largest_height = 0; //holds greatest height int
			//for loop finds greatest height in range of position
				for (int i = pos; i <= pos+1; i++)
				{
					if (heights[i] > largest_height)
						largest_height = heights[i];
				}

				char *temparray =  empty_array(largest_height + 2);
				for(int j = 0; j < heights[pos+1]; j++)
					{
						temparray[j] = data[pos+1][j];
					}
				temparray[largest_height] = 'S';
				temparray[largest_height +1] = 'S';
				if (heights[pos] != 0)
						delete [] data[pos+1];
				data[pos+1] = temparray;
				heights[pos+1] = largest_height + 2;

				temparray = empty_array(largest_height + 3);
				for(int j = 0; j < heights[pos]; j++)
					{
						temparray[j] = data[pos][j];
					}
				temparray[largest_height] = ' ';
				temparray[largest_height+1] = 'S';
				temparray[largest_height+2] = 'S';
				if (heights[pos+1] != 0)
						delete [] data[pos];
				data[pos] = temparray;
				heights[pos] = largest_height + 3;
			}
		}
	}
	///////////////////////////////////////////////////////////////////////////
	else
		std::cout<< "ERROR\n";
}
