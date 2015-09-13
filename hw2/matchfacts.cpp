#include "matchfacts.h"
#include <iostream>
#include <string>
#include <vector>

Matchfacts::Matchfacts(){
	winner = "";
	loser = "";
}
Matchfacts::Matchfacts(std::string win, std::string lose, std::vector <std::string> scor)
{
 	winner = win;
 	loser = lose;
 	scores = scor;
 }

std::string Matchfacts::getwinname() const{
	return winner;
}

std::string Matchfacts::getlosename() const {
	return loser;
}

std::vector <std::string> Matchfacts::getscores() const{	
	return scores;
}




