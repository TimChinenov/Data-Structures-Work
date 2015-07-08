/*
Author: Tim Chinenov 
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
void replace(std::vector< std::vector <char> >& allchar, std::ofstream & out_str,
 char removed, char replaced)
//replace function. char removed is the character that was asked to bet removed
// and char replaced is the character the takes the placed of the previously 
//removed character.
{
	//double for loop goes through each position in the vector, removing 
	//characters that match "char removed" and replacing them with 
	//"char replaced"
	for (int j = 0; j < allchar.size(); j++)
	{
		for (int x = 0; x < allchar[j].size(); x++)
		{
			if (allchar[j][x] == removed)
				allchar[j][x] = replaced;
		}
	}
	//outputs final vector to text file line by line, character by character 
	for (int j = 0; j < allchar.size(); j++)
	{
		for (int x = 0; x < allchar[j].size(); x++)
		{
			out_str << allchar[j][x];
		}
		out_str << "\n";
	}
}

void dilation(std::vector< std::vector <char> >& allchar, std::ofstream & out_str,
 char foreground)
//dialation creates a copy of the primary vector known as notchanged.
//notchanged is used as a reference vector that never changes while the allchar
//vector changes based on the surrounding characters.
{
	//double for loop goes through each position in the vector
	std::vector< std::vector <char> > notchanged = allchar;
	for (int j = 0; j < notchanged.size(); j++)
	{
		for (int z = 0; z < notchanged[j].size(); z++)
		{
			//if a position is a foreground character then it will turn 
			//all surrounding locations in the vector into foreground 
			//characters. 
			if (notchanged[j][z] == foreground)
			{
				//the first if checks make sure that the vector is not
				//looking in a location that is out of index or does not 
				//exist
				if (j-1 >= 0)
					allchar[j-1][z] = foreground;
				if (j+1 < allchar.size())
					allchar[j+1][z] = foreground;
				if (z-1 >= 0)
					allchar[j][z-1] = foreground;
				if (z+1 < allchar[z].size())
					allchar[j][z+1] = foreground;
			}
		} 	
	}
	//outputs the final version of allchar into the text file
	for (int k = 0; k < allchar.size(); k++)
	{
		for (int a = 0; a < allchar[k].size(); a++)
		{
			out_str << allchar[k][a];
		}
		out_str << "\n";
	}
}

void erosion(std::vector< std::vector <char> >& allchar, std::ofstream & out_str,
 char foreground, char background)
//The erosion function takes in a character forground and a character background.
//Similarily to dilation(), the function creates a copy of the primary vector
//to use as a original model "notchanged"
{
	//double for loop goes through each spot in the original vector.
	std::vector< std::vector <char> > notchanged = allchar;
	for (int c = 0; c < notchanged.size(); c++)
	{
		for (int d = 0; d < notchanged[c].size(); d++)
		{
			//checks to see if current location is a foreground. If so, the function
			//begins to check surrounding positions for background characters.
			//if a surroinding character is in fact a background character then the 
			//current foreground character is removed.
			if (notchanged[c][d] == foreground)
			{ 
				//Initial if check if surrounding characters are 
				//correct vector indecies. 	
				if (c-1 >= 0)
				{
					if ((notchanged[c-1][d] == background))
						allchar[c][d] = background;
				}
				if (c+1 <notchanged.size())
				{
					if (notchanged[c+1][d] == background)
						allchar[c][d] = background;
				}
				if (d-1 >= 0)
				{
					if ((notchanged[c][d-1] == background))
						allchar[c][d] = background;
				}
				if (d +1 < notchanged[c].size())
				{
					if (notchanged[c][d+1] == background)
						allchar[c][d] = background;
				}
				//This statement turns any characters on the border of the vector 
				//into a background character regardless of it's relationship to
				//surrounding characters.
				if (c == 0 || c == notchanged.size() || d == 0 || d == notchanged.size())
				{
					allchar[c][d] == background;
				} 
			}
		}
	}
	//outputs vector to file
	for (int k = 0; k < allchar.size(); k++)
	{
		for (int p = 0; p < allchar[k].size(); p++)
		{
			out_str << allchar[k][p];
		}
		out_str << "\n";
	}
}

void floodfill( std::vector< std::vector <char> >& allchar, 
	std::ofstream & out_str, int y, int x, char rep, char cho )
//floodfill function is a recursive function which uses a single vector 
//which is passed by reference. With each call a position is sent into 
//the function as well as the character that will replaced the current 
//character. Cho never changes with each recursion
{
	//If the charachter is the same as the original chosen character
	//the function will change the current character into the replacement 
	//character and then recursively check all adjacent positions.
	if (allchar[y][x] == cho)
	{
		allchar[y][x] = rep;
		if (y + 1 < allchar.size() && allchar[y+1][x] == cho)
		{
			floodfill( allchar, out_str, y+1, x, rep, cho );
		}
		if (y - 1 > 0 && allchar[y-1][x] == cho)
		{
			floodfill(allchar, out_str, y-1, x, rep, cho );
		}
		if (x + 1 < allchar[y].size() && allchar[y][x+1] == cho)
		{
			floodfill(allchar,out_str, y, x+1, rep, cho);
		}
		if (x - 1 > 0 && allchar[y][x-1] == cho)
		{
			floodfill(allchar, out_str, y, x-1, rep, cho);
		}
	}
}
int main(int argc, char* argv[])
//Reads in stream  as a char array that can range from size of 5 to
// 7 objects
{
	std::ifstream in_str(argv[1]);
	if (!in_str.good()) 
	{
    	std::cerr << "Can't open " << argv[1] << " to read.\n";
    	return 1;
  	}
  	std::ofstream out_str(argv[2]);
  	if (!out_str.good()) {
    std::cerr << "Can't open " << argv[2] << " to write.\n";
    return 1;
  	}

	std::string line;
	std::vector < std::vector <char> > entire;
	//while loop reads in lines from the inputed text file
	//and creates a vector of characters known as "entire".
	//This will be the primary vector which will be pushed through
	//the chosen functions.
	while (in_str >> line)
	{
		std::vector <char> tempvector;
		for (int i = 0; i < line.size(); i++)
		{
				tempvector.push_back(line[i]);
		}
		entire.push_back(tempvector);
	}
	//if statements checks for key word in index 3 of char array. 
	//If a match is made, vector is sent into appropriate function.
	if (std::string(argv[3]) == std::string("replace"))
	{
		if (argc == 6)
		{
			replace(entire, out_str, argv[4][0], argv[5][0]);
		}
		else
			std::cerr <<"Too few items in inputed array, 6 required to continue\n";
			return 1;
	}
	else if (std::string(argv[3]) == std::string("dilation"))
	{
		if (argc == 5)
		{
			dilation(entire, out_str, argv[4][0]);
		}
		else
			std::cerr <<"Too few items in inputed array, 5 required to continue\n";
			return 1;
	}
	
	else if (std::string(argv[3]) == std::string("erosion"))
	{
		if (argc = 6)
		{
			erosion(entire, out_str, argv[4][0], argv[5][0]);
		}
		else
			std::cerr <<"Too few items in inputed array, 6 required to continue\n";
			return 1;
	}
	
	else if (std::string(argv[3]) == std::string("floodfill"))
	{
		if (argc = 7)
		{
			int y1 = atoi(argv[4]);
			int x1 = atoi(argv[5]);
			//sends a vector, outputfile, y, x, replace character, character
			//at the x,y position.
			floodfill(entire, out_str, y1, x1, argv[6][0], entire[y1][x1]);

		}
		else
		{
			std::cerr <<"Too few items in inputed array, 7 required to continue\n";
			return 1;
		}
		//In order to avoid the result output into the text file multiple times,
		//the for loop two output the 2D vector to the txt file is placed outside 
		//the function. 
		for (int k = 0; k < entire.size(); k++)
		{
			for (int p = 0; p < entire[k].size(); p++)
			{
				out_str << entire[k][p];
			}
			out_str << "\n";
		}
	}
	
}
