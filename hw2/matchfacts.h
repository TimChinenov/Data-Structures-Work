#include <iostream>
#include <string>
#include <vector>


#ifndef __matchfacts_h_
#define __matchfacts_h_
//this class creates a object of the match which contains a winners name, a
// losers name, and a vector of scores.
class Matchfacts {
public:
	Matchfacts(); //Default Constructor
	Matchfacts(std::string win, std::string lose, std::vector <std::string> scor); 
	//overload constructor

	std::string getwinname() const; // names
	std::string getlosename() const; //names
	std::vector <std::string> getscores() const;	

private:
	std::string winner; //winners name
	std::string loser; // losers name
	std::vector <std::string> scores; //vector of string os scores
};



#endif