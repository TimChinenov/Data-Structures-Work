#include <iostream>
#include <string>
#include <vector>
//this class will hold a player object that contains 
//a name a number of match_wins, a number of match losses
//, a number of game losses, a number of game wins, and 
//a vector the shows the total points accumulated per match.
#ifndef __player_h_
#define __player_h_

class Player {
public:
	Player();
	Player(std::string players_name);

	std::string get_name() const;

	int get_match_wins() const; //returns match_wins
	int get_match_losses()const; //returns match_losses

	int get_game_wins() const; //returns game_wins
	int get_game_losses() const; //return game_losses

	void incrementw(); //increases match_wins by one
	void incrementl(); // increases match_losses by one

	void increase_wins(int number); //increase games_wins by number
	void increase_loss(int number);	//increase games_loss by number

	float average_match_wins()const; //returns the average of matches
	float average_games_wins()const; //returns the average of games

	void pushbackvec(int n); // pushes back a number to required_to_win
	void sortvec(); //sorts required_to_win
	int getlargest() const; //gets greates value in vector
	int getsmallest() const; //gets smallest value in vector
	float getaverage_req() const; //gets average of vector

private:
	std::string name;

	int match_wins;
	int match_losses;

	int game_wins;
	int game_losses;

	std::vector <int> required_to_win;
	// extra part
	

};
//changes the sort comp for sorting matches
bool is_better_player_match(const Player& p1, const Player& p2);
//changes the sort comp for sorting games
bool is_better_player_game(const Player& p1, const Player& p2);
//changes the sort comp for least and most wins 
bool is_better_least(const Player& p1, const Player& p2);
#endif