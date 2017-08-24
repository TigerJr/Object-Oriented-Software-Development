// lab4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"game_board.h"
#include"utility.h"
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include"Game.h"
#include"NineAlmondGame.h"
#include"Magic_square.h"
#include<memory>

int main(int argc, char* argv[])
{ 
	try { 
		Game::operate(argc, argv);
		Game::instance()->play();
	}
	catch (return_type n) {
		if (n == dim_not_positive) {
			usage_message(argv[prog_name_pos]);
			return dim_not_positive;
		}
		else if (n == user_request_quit) {
			return user_request_quit;
		}
		else if (n == game_already_exist) {
			cout << "game already exists !" << endl;
			return game_already_exist;
		}
		else if (n == no_valid_input) {
			return no_valid_input;
		}
		else if (n == file_get_failure) {
			return file_get_failure;
		}
		else {
			usage_message(argv[prog_name_pos]);
			return not_a_number;
		}
	}
	catch (const std::bad_alloc) {
		cout << "No enough memory space!" << endl;
		return out_of_memory;
	}
}
