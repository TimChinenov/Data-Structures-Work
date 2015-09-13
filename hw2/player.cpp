#include "player.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

Player::Player(){
	name = "";
	//default constructor
	match_wins = 0;
	match_losses= 0;

	game_wins = 0;
	game_losses = 0;
}

Player::Player(std::string players_name){
	//overload constructor
	match_wins = 0;
	match_losses= 0;

	game_wins = 0;
	game_losses = 0;

	name = players_name;

	required_to_win.push_back(0);
	required_to_win.push_back(0);
	
}

int Player::get_match_wins() const{
	return match_wins;
}

int Player::get_match_losses() const{
	return match_losses;
}

int Player::get_game_wins() const{
	return game_wins;
}

int Player::get_game_losses() const{
	return game_losses;
}

void Player::incrementw(){
	match_wins++;
}

void Player::incrementl(){
	match_losses++;
}

void Player::increase_wins(int number){
	game_wins += number;
}

void Player::increase_loss(int number){
	game_losses += number;
}
//takes sum of match wins and losses and divides match wins by the sum
//*1.0 turns it into a float
float Player::average_match_wins() const{
	return (match_wins*1.0)/(match_wins + match_losses);
}
//takes sum of game wins and losses and divides game wins by the sum
float Player::average_games_wins()const{
	return (game_wins*1.0)/(game_wins + game_losses)*1.0;
}

std::string Player::get_name() const{
	return name;
}
void Player::pushbackvec(int n) {
	required_to_win.push_back(n);
}

void Player::sortvec(){
	std::sort(required_to_win.begin(), required_to_win.end());
}
int Player::getlargest() const{
	//returns last position of required_to_win
	return required_to_win[required_to_win.size()-1];
}
int Player::getsmallest() const{
	//if object never won return zero
	//else object returns 3 index or position
	//[2]
	if (required_to_win.size() < 3)
	{
		return required_to_win[0];
	}
	else
		return required_to_win[2];
}
float Player::getaverage_req() const{
	//total adds up all values in for loop and then
	//returns the total by the size of the vector
	int total = 0;
	for (int i = 0; i < required_to_win.size(); i++)
	{
		total += required_to_win[i];
	}
	return (total*1.0)/required_to_win.size();
}

bool is_better_player_match(const Player& p1, const Player& p2){
	//checks if average of 1 is greater than 2
	if (p1.average_match_wins() > p2.average_match_wins()){
		return true;
	}
	//if they are the same the creates substring of the last names... 
	else if (p1.average_match_wins() == p2.average_match_wins()){
		int i = p1.get_name().find(' ');
		int j = p2.get_name().find(' ');
		std::string lastp1 = p1.get_name().substr(i,p1.get_name().size()-i-1);
		std::string lastp2 = p2.get_name().substr(j,p2.get_name().size()-j-1);
		//returns true if one last name is greater than the other
		if (lastp1 < lastp2){
			return true;
		}
		//if the last names are the same create substrings of the first names
		//and compare them.
		else if (lastp1 == lastp2){
			std::string firstp1 = p1.get_name().substr(0, i);
			std::string firstp2 = p2.get_name().substr(0, j);
			if (firstp1 < firstp2){
				return true;
			}
			else
				return false;
		}
	}
	return false;
}
//this function is the same as the previous function but compares
//average games win instead of average match wins
bool is_better_player_game(const Player& p1, const Player& p2){
	if (p1.average_games_wins() > p2.average_games_wins()){
		return true;
	}
	else if (p1.average_games_wins() == p2.average_games_wins()){
		int i = p1.get_name().find(' ');
		int j = p2.get_name().find(' ');
		std::string lastp1 = p1.get_name().substr(i,p1.get_name().size()-i-1);
		std::string lastp2 = p2.get_name().substr(j,p2.get_name().size()-j-1);
		if (lastp1 < lastp2){
			return true;
		}
		else if (lastp1 == lastp2){
			std::string firstp1 = p1.get_name().substr(0, i);
			std::string firstp2 = p2.get_name().substr(0, j);
			if (firstp1 < firstp2){
				return true;
			}
			else
				return false;
		}
	}
	return false;
}
// same as first compare sort changing function, except compares
//compares getaverage_req initially.
bool is_better_least(const Player& p1, const Player& p2){

	if (p1.getaverage_req() > p2.getaverage_req()){
		return true;
	}
	else if (p1.getaverage_req() == p2.getaverage_req()){
		int i = p1.get_name().find(' ');
		int j = p2.get_name().find(' ');
		std::string lastp1 = p1.get_name().substr(i,p1.get_name().size()-i-1);
		std::string lastp2 = p2.get_name().substr(j,p2.get_name().size()-j-1);
		if (lastp1 < lastp2){
			return true;
		}
		else if (lastp1 == lastp2){
			std::string firstp1 = p1.get_name().substr(0, i);
			std::string firstp2 = p2.get_name().substr(0, j);
			if (firstp1 < firstp2){
				return true;
			}
			else
				return false;
		}
	}
	return false;
}

