#include "matchfacts.h"
#include "player.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <iomanip>

// Parses a string that represents a set (i.e., "6-3") by breaking the
// string into two substrings and converting those strings to
// integers, which are returned via call-by-reference parameters
void parse_set(std::string &set, int &games_won, int &games_lost) {
  int i = set.find('-');
  games_won = atoi(set.substr(0,i).c_str());
  games_lost = atoi(set.substr(i+1,set.size()-i-1).c_str());
}
// print_match sends the results to the file
void print_match( std::vector <Player> &players, std::ofstream &out_str ){
  int maxlength = 0;
  std::sort (players.begin(), players.end(), is_better_player_match);
  out_str << "MATCH STATISTICS\n";
  //For loop to find out the required white space between the player and score
  for (int i = 0; i < players.size(); i++){
    if (players[i].get_name().size() > maxlength)
      {maxlength = players[i].get_name().size();} 
  }
// title
  out_str << "Player" << std::setw(maxlength-1) << "W" << std::setw(5) 
  << "L" << std::setw(14) << "percentage\n";
//for loop goes through each player object outputting the required stats
  for (int i = 0; i < players.size(); i++){
    out_str << players[i].get_name(); 
    out_str << std::setw(maxlength - players[i].get_name().size()+ 5);
    out_str << players[i].get_match_wins() << std::setw(5);
    out_str << players[i].get_match_losses(); 
    out_str << std::setw(13) << std::fixed << std::setprecision(3);
    out_str << players[i].average_match_wins() << "\n"; 
  }
  out_str << "\n";
}
// print_games sends the results of the stat games to the output file  
void print_games( std::vector <Player> &players, std::ofstream &out_str){
  int maxlength = 0;
  //sorts array by best average
  std::sort (players.begin(), players.end(), is_better_player_game);
  out_str << "GAME STATISTICS\n";
  //for loop finds maxlength for white space between player and winner
  for (int i = 0; i < players.size(); i++){
    if (players[i].get_name().size() > maxlength)
      {maxlength = players[i].get_name().size();}
  }
  out_str << "Player" << std::setw(maxlength-1) << "W" << std::setw(5) 
  << "L" << std::setw(14) << "percentage\n";
  // for loop prints out players name, wins, losses, and percentage
  for (int i = 0; i < players.size(); i++){
    out_str << players[i].get_name() << 
    std::setw(maxlength - players[i].get_name().size()+ 5) << 
    players[i].get_game_wins() << std::setw(5) << players[i].get_game_losses() 
    << std::setw(13) << std::fixed << std::setprecision(3) <<
     players[i].average_games_wins() << "\n"; 
  }
}
//PART THREE: print_required outputs the players name, the most amount of points,
// and the least amount of points needed to win.
void print_required(std::vector <Player> &players, std::ofstream &out_str)
{
  out_str << "\n";
  int maxlength = 0;
  //sorts player objects by the highest average required to win.
  std::sort (players.begin(), players.end(), is_better_least);
  out_str << "NUMBER OF POINTS TO WIN STATISTICS\n";
// finds maxlength for white space between player name and winner.
  for (int i = 0; i < players.size(); i++){;
    if (players[i].get_name().size() > maxlength)
      {maxlength = players[i].get_name().size();}
  }
  out_str << "Player" << std::setw(maxlength-1) << "Most" << std::setw(6) 
  << "Least" << std::setw(13) << "Average\n";

  //for loop which outputs the players name, the most amount of points,
  //and the least amount of points needed to win.
  for (int i = 0; i < players.size(); i++)
  {
    players[i].sortvec();
    out_str << players[i].get_name();
    out_str << std::setw(maxlength - players[i].get_name().size()+ 5); 
    out_str << players[i].getlargest() << std::setw(5);
    out_str << players[i].getsmallest() << std::setw(13); 
    out_str << std::fixed << std::setprecision(3);
    out_str << players[i].getaverage_req() << "\n";
   }
}
//Player_create function creats the player objects vector from the 
//vector of match objects
void player_create(std::vector <Matchfacts> &matches, 
  std::vector <Player> &players, int &games_won, int &games_lost)
{
  //##########################################Winners
  bool found = false;
 //this for loop goes through the match vector and assigns the winners
  //name to tempname
  for (int j = 0; j < matches.size(); j++)
  {
    found = false;
    std::string tempname = matches[j].getwinname();
    //the following for loop checks whether tempname already exists within the
    //player object vector. If it does...
    for (int k = 0; k < players.size() && !found; k++){
      if (players[k].get_name() == tempname){
        std::vector <std::string> scorevec = matches[j].getscores();
        //the function increases the players wins by one...
        players[k].incrementw();
        int winscore = 0; // int to find total set points per match
        for (int t = 0; t < scorevec.size(); t++)
        {
          parse_set(scorevec[t],games_won,games_lost);
          //increases there wins and losses by the respected wins and losses
          //parsed by parse_set...
          players[k].increase_wins(games_won);
          players[k].increase_loss(games_lost);
          winscore += games_won;
        }
        //and adds the score to the players required_to_win vector
        players[k].pushbackvec(winscore);
        found = true;
      }
    }
    //if the player is not found in the player object vector then
    //the function goes to this if statement.
    if (!found){
      std::vector <std::string> scorevec = matches[j].getscores();
      // a temporary player is created...
      Player tempobject(tempname);
      //the players wins is increased by one
      tempobject.incrementw();
      int winscore = 0;
      for (int t = 0; t < scorevec.size(); t++)
      {
        parse_set(scorevec[t],games_won,games_lost);
        tempobject.increase_wins(games_won);
        tempobject.increase_loss(games_lost);
        winscore += games_won;
      }
      //the ned player object is pushed back into the player object vector
      tempobject.pushbackvec(winscore);
      players.push_back(tempobject);
    }
  }
  //########################################LOSERS
  //this for loop is similar to the winners for loop, but many of the statements
  //are flipped. This for loop also doesn't check for least amount of points
  //to win and most amount of points as the players in this for loop did not win.
  found = false;
  //creates a temp name from the losers name in the match object
  for (int j = 0; j < matches.size(); j++)
  {
    found = false;
    std::string tempname = matches[j].getlosename();

    for (int k = 0; k < players.size() && !found; k++){
      //if the player is found in the vector...
      if (players[k].get_name() == tempname){
        std::vector <std::string> scorevec = matches[j].getscores();
        //their losses are incremented by one
        players[k].incrementl();
        
        for (int t = 0; t < scorevec.size(); t++)
        {
          //increase wins by the lost variable and increase losses by the win 
          //variable.
          parse_set(scorevec[t],games_won,games_lost);
          players[k].increase_wins(games_lost);
          players[k].increase_loss(games_won);
        } 
        found = true;
      }
    }
    //if name is not found in vector...
    if (!found){
      std::vector <std::string> scorevec = matches[j].getscores();
      //create temp object
      Player tempobject(tempname);
      //increase LOSSES by one
      tempobject.incrementl();
      for (int t = 0; t < scorevec.size(); t++)
      {
        parse_set(scorevec[t],games_won,games_lost);
        tempobject.increase_wins(games_lost);
        tempobject.increase_loss(games_won);
      }
      players.push_back(tempobject);
    }
  }
}
//////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{

  int games_won = 0; ///parsing variables
  int games_lost = 0; // parsing variables
	std::ifstream in_str(argv[1]);
	if (!in_str.good()) // checks if input stream is good
	{
    	std::cerr << "Can't open " << argv[1] << " to read.\n";
    	return 1;
  	}

  std::ofstream out_str(argv[2]); //checks if output stream is good
  if (!out_str.good()) {
    std::cerr << "Can't open " << argv[2] << " to write.\n";
    return 1;
  	}

    std::string line;
    std::vector <Player> player_objects;
    std::vector <Matchfacts> match_objects; //vector of match objects.
    bool alpha = true;
    std::vector <std::string> tempvec; // temporary vector to hold names and scores
    std::vector <std::string> setscores; // temporary vector to hold scores

    //This while loop takes in the text document string by string
    //checking whether it is a name or a number. If there is a transition
    //point from name to number the loop will create a match object and place it
    //into a vector.
    while (in_str >> line) //parses text file
    {
      // checks to make sure the the transition point from number
      //to letter has been made
      if (alpha == false && (!std::isdigit(line[0]))) 
      {
        //takes tempvec and creates a match object
        match_objects.push_back(Matchfacts(tempvec[0] + " " + tempvec[1], 
          tempvec[2] + " " + tempvec[3], setscores));
        alpha = true;
        setscores.clear();
        tempvec.clear();
      }
      //if the character is a digit we added it to the setscores vector
      if (std::isdigit(line[0]))
      {
        setscores.push_back(line); 
        alpha = false;
      }
      //this checks if the string is a letter and if so we simply put it 
      //into the vector.
      else if (line.size() > 2)
      {
        tempvec.push_back(line);
      }
    }//end of while loop
    //adds last object incase the text ends without switiching to new name
    match_objects.push_back(Matchfacts(tempvec[0] + " " + tempvec[1], 
      tempvec[2] + " " + tempvec[3], setscores));
    
    //function calls
    player_create(match_objects,player_objects, games_won, games_lost);
    print_match(player_objects, out_str);
    print_games(player_objects, out_str);
    print_required(player_objects, out_str);
}
    