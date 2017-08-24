#pragma once
#include "utility.h"
#include <iostream>
#include <sstream>
#include <vector>
#include "game_piece.h"
#include <fstream>
#include"game_board.h"
#include<memory>


using namespace std;

class Game {
public:
	Game();
	Game(int, int);
	virtual bool done() = 0;
	virtual bool stalemate() = 0;
	virtual int prompt(unsigned int &, unsigned int &);
	virtual int turn() = 0;
	virtual int play();
	virtual void print() = 0;
	static void operate(int, char *[]);
	static shared_ptr<Game> instance();
	virtual int save_or_not(string);
protected:
	unsigned int width;
	unsigned int height;
	vector<game_piece> game_board;
	string game_name;
	virtual bool is_vaild(unsigned int, unsigned int) = 0;
	unsigned int max_string_length;
	static shared_ptr<Game> smart_pointer;
};