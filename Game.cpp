#include"stdafx.h"
#include "utility.h"
#include <iostream>
#include <sstream>
#include <vector>
#include "game_piece.h"
#include <fstream>
#include"Game.h"
#include"game_board.h"
#include"NineAlmondGame.h"
#include"Magic_square.h"
#include"ReversiGame.h"
#include<memory>

using namespace std;
Game::Game() {};
Game::Game(int rows, int cols) : width(rows), height(cols), max_string_length(1) {};
void Game::operate(int argc, char* argv[]) {
	if (smart_pointer != nullptr) {
		throw game_already_exist;
	}
	string input_game_name = "";
	if (argc == no_input_game_name) //there is no input file name
	{
		cout << "No file name provided!" << '\n' << endl;
		usage_message(argv[prog_name_pos]);
		throw no_valid_input;
	}
	else {
		input_game_name = argv[game_name_pos];
	}
	to_lower_case(input_game_name);
	if (input_game_name == "ninealmonds") {
		if (argc == expected_command_line_size) {
			smart_pointer = make_shared<NineAlmondGame>();
		}
		else {
			usage_message(argv[prog_name_pos]);
			throw no_valid_input;
		}
	}
	else if (input_game_name == "magicsquare") {
		if (argc == expected_command_line_size) {
			smart_pointer = make_shared<MagicSquare>();
		}
		else if (argc == expected_command_line_size + 1) {
			istringstream in(argv[game_name_pos + 1]);
			int dim;
			if (in >> dim) {
				smart_pointer.reset(new MagicSquare(dim));
			}
			else {
				throw not_a_number;
			}
		}
		else if (argc == expected_command_line_size + 2) {
			istringstream in_dim(argv[game_name_pos + 1]);
			istringstream in_start(argv[game_name_pos + 2]);
			int dim;
			int start;
			if ((in_dim >> dim) && (in_start >> start)) {
				smart_pointer.reset(new MagicSquare(dim, start));
			}
			else {
				throw not_a_number;
			}
		}
	}
	else if (input_game_name == "reversi") {
		if (argc == expected_command_line_size+2) {
			string a = argv[game_name_pos + 1];
			string b = argv[game_name_pos + 2];
			smart_pointer.reset(new ReversiGame(a, b));
		}
		else {
			usage_message(argv[prog_name_pos]);
			throw no_valid_input;
		}
	}
	else {
		cout << "game not found!" << endl;
		usage_message(argv[game_name_pos]);
		throw file_get_failure;
	}
};
int Game::play() {
	print();
	int i = 0;
	while (true) {
		if (turn() == user_request_quit) {
			instance()->save_or_not(this->game_name);
			cout << "There are " << i << " turns played" << endl;
			cout << "user quit the game" << endl;
			return user_request_quit;
		}
		if (done()) {
			++i;// to add one turn
			ostringstream file_name;
			file_name << game_name << ".txt";
			ofstream save_file(file_name.str());
			save_file << "game completed!" << endl;
			cout << "There are " << i << " turns played" << endl;
			cout << "game is completed successfully" << endl;
			return success;
		}
		if (stalemate()) {
			++i;// to add one turn
			cout << "There are " << i << " turns played" << endl;
			cout << "There are no valid moves, game ends" << endl;
			return no_valid_move;
		}
		++i;//in this case, one turn is made and game is not over
	}
	return success;
};

shared_ptr<Game> Game::smart_pointer = nullptr;

shared_ptr<Game> Game::instance() {
	if (smart_pointer == nullptr)
	{
		throw no_game_exist;
		return smart_pointer;
	}
	else {
		return smart_pointer;
	}
};

int Game::save_or_not(string game_name) {
	string yrn;
	cout << " Do you want to save the game ?( 'yes' to save, 'no' to quit )" << endl;
	cin >> yrn;
	to_lower_case(yrn);
	while (yrn != "yes"&&yrn != "no") {
		cout << "please type in yes or no." << endl;
		cin >> yrn;
		to_lower_case(yrn);
	}
	ostringstream file_name;
	file_name << game_name << ".txt";
	ofstream save_file(file_name.str());
	if (yrn == "no") {
		save_file << "NO DATA" << endl;
		return not_saving_game;
	}
	else {
		save_file << game_name << endl;
		save_file << this->width << " " << this->height << endl;
		for (game_piece i : game_board) {
			save_file << enum_to_label(i.color) << " " << i.name << " " << i.rule << endl;
		}
		save_file.close();
		return success;
	}
}
int Game::prompt(unsigned int & first, unsigned int & second) {
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
				cout << "please type in a right coordinate or type quit" << endl;
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
					cout << "please type in a right coordinate or type quit" << endl;
				}
			}
			else {
				continue;
			}
		}
	}
	return success;
}