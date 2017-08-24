#include"stdafx.h"
#include"game_board.h"
#include"utility.h"
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include"Game.h"
#include"NineAlmondGame.h"

using namespace std;

//constructor of the class of game
NineAlmondGame::NineAlmondGame()  {
	game_name = "NineAlmonds";
	brown_almond.color = black;
	brown_almond.name = "brown_almond";
	brown_almond.rule = "A";
	empty.color = none;
	empty.name = "";
	empty.rule = " ";
	ostringstream file_name;
	file_name << this->game_name << ".txt";
	cout << file_name.str() << endl;
	ifstream read_file(file_name.str());
	string first_line = " ";
	if (read_file.is_open()) {
		getline(read_file, first_line);// in case
	}
	width = 5;
	height = 5;
	int size = width*height;
	for (int i = 0; i < size; ++i) {
		game_board.push_back(empty);
	}
	if (first_line == game_name) {
		read_game_board(read_file, width, height);
		for(game_piece & i:game_board){
			string temp_line;
			string color;
			getline(read_file, temp_line);
			istringstream  temp(temp_line);
			if (temp >> color >> i.name >> i.rule) {
				i.color = label_to_enum(color);
			}
		}
	}
	else {
		for (unsigned int i = 0; i < width; ++i) {
			for (unsigned int j = 0; j < height; ++j) {
				if ((i == 0) || (j == 0) || (i == width - 1) || (j == height - 1)) {
					//do nothing
				}
				else {
					game_board[i + j*width] = brown_almond;
				}
			}
		}
	}
}
bool NineAlmondGame::done() {
	int central_width = width / 2;//use integral division
	int central_height = height / 2;
	int pos = central_height*width + central_width;
	//1st condition:central game piece
	if (game_board[pos] == empty) {
		return false;
	}
	//2nd condition:lower half of board is empty
	for (int i = 0; i < pos; ++i) {
		if (game_board[i] == brown_almond) {
			return false;
		}
	}
	int end = width*height;
	//3nd condition:lupper half of board is empty
	for (int i = pos + 1; i < end; ++i) {
		if (game_board[i] == brown_almond) {
			return false;
		}
	}
	return true;
}
bool NineAlmondGame::stalemate() {
	if (done()) {
		return false;
	}
	int size = width*height;
	int dist = 2;
	//to go over all the positions on a board to find possible valid moves.
	for (int i = 0; i < size; ++i) {
		if (is_vaild(i, i + dist*width)) {
			return false;
		}
		else if (is_vaild(i, i - dist*width)) {
			return false;
		}
		else if (is_vaild(i, i + dist)) {
			return false;
		}
		else if (is_vaild(i, i - dist)) {
			return false;
		}
		else if (is_vaild(i, i + dist*width + dist)) {
			return false;
		}
		else if (is_vaild(i, i + dist*width - dist)) {
			return false;
		}
		else if (is_vaild(i, i - dist*width + dist)) {
			return false;
		}
		else if (is_vaild(i, i - dist*width - dist)) {
			return false;
		}
	}
	return true;
}

int NineAlmondGame::prompt(unsigned int & first, unsigned int & second) {
	int i = no_valid_input;
	//to make sure this while loop will be excuted at least once
	while (i == no_valid_input) {
		string input;
		cin >> input;
		if (input == "quit") {
			return user_request_quit;
		}
		else {
			//In this case, the find function in std library returns a string indicating no such string was found.
			if (input.find(",") == string::npos) {
				cout << "please type in a right cordinate or type quit" << endl;
				continue;
			}
			else {
				input.replace(input.find(","), 1, " ");
			}
			istringstream numbers(input);
			if ((numbers >> first) && (numbers >> second)) {
				if ((first < width) && (second < height)) {
					++i;
				}
				else {
					cout << "please type in a right cordinate or type quit" << endl;
				}
			}
			else {
				continue;
			}
		}
	}
	return success;
}
int NineAlmondGame::turn() {
	ostringstream move; //to record each move
	unsigned int s_width;
	unsigned int s_height;
	int i = no_valid_input;
	while (i == no_valid_input) {
		cout << "Please enter a beginning cordinate or enter quit" << endl;
		if (prompt(s_width, s_height) == user_request_quit) {
			return user_request_quit;
		}
		move << s_width << ", " << s_height;
		//use auxiliary function to make next move
		i = turn_next(s_width, s_height, move);
		if (i == user_request_quit) {
			return user_request_quit;
		}
		if (i == no_valid_input) {
			//delete moves
			move.str("");
			move.clear();
		}
	}
	string condition = "y";
	// to make sure this loop will be excuted once
	while (condition == "y") {
		//print out the board
		cout << *this << endl << endl;
		cout << move.str() << endl;
		if (done()) {
			return success;
		}
		if (stalemate()) {
			return no_valid_move;
		}
		cout << "Continue this turn(YyNn) ?" << endl;
		cin >> condition;
		to_lower_case(condition);
		while ((condition != "n") && (condition != "y")) {
			cout << "try to type in y or n, y to continue, n to quit" << endl;
			cin >> condition;
		}
		if (condition == "n") {
			cout << "next turn starts" << endl;
			return success;
		}
		if (turn_next(s_width, s_height, move) == user_request_quit) {
			//in this case, at least one valid move has been made.
			cout << "next turn starts" << endl;
			return success;
		}
	}
	return success;
}

//to determine whether one move is valid or not
bool NineAlmondGame::is_vaild(unsigned int s_pos, unsigned int e_pos) {
	if ((s_pos >= width*height) || (e_pos >= width*height)) {
		return false;
	}
	int difference = s_pos - e_pos;
	bool indicator;
	int dist = 2;
	//1st condition:the starting piece and ending piece are one piece away
	if ((difference == dist*width) || (difference == dist*(0 - width)) ||
		(difference == dist) || (difference == -dist) ||
		(difference == dist*(width + 1)) || (difference == dist*(width - 1)) ||
		(difference == dist*(0 - width + 1)) || (difference == dist*(0 - width - 1))) {
		indicator = true;
	}
	else {
		return false;
	}
	int central_pos = (s_pos + e_pos) / 2;
	//2nd condition: those places are placed right game piece
	if ((game_board[s_pos] == brown_almond) && (game_board[e_pos] == empty) &&
		(game_board[central_pos] == brown_almond)) {
		indicator = true;
	}
	else {
		indicator = false;
	}
	return indicator;
}
//handles the second part of a move given a start game piece
int NineAlmondGame::turn_next(unsigned int& s_width, unsigned int& s_height, ostringstream & move) {
	cout << "Please enter a ending cordinate or enter quit" << endl;
	unsigned int e_width;
	unsigned int e_height;
	if (prompt(e_width, e_height) == user_request_quit) {
		return user_request_quit;
	}
	int s_pos = s_width + s_height*width;
	int e_pos = e_width + e_height*width;
	if (is_vaild(s_pos, e_pos)) {
		//update the gameboard
		game_board[s_pos] = empty;
		game_board[e_pos] = brown_almond;
		game_board[(s_pos + e_pos) / 2] = empty;
		//update move 
		move << " to " << e_width << ", " << e_height;
		//update start point
		s_width = e_width;
		s_height = e_height;
		return success;
	}
	else {
		cout << "The move take in is not valid!" << endl;
		return no_valid_input;
	}
}


void NineAlmondGame::print() {

	cout << *this << endl;

}


ostream &operator << (ostream & out, const NineAlmondGame & game) {
	//use an overload of print function written in lab1
	print_game_board(out, game.game_board, game.width, game.height);
	return out;
}