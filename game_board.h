#pragma once
#include <fstream>
#include<vector>
#include"game_piece.h"
using namespace std;
int read_game_board(ifstream &, unsigned int &, unsigned int &);
int read_game_piece(ifstream &, vector<game_piece> & , unsigned int & , unsigned int & );
int print_game_board(const vector<game_piece> & , unsigned int , unsigned int );
int print_game_board(ostream & , const vector<game_piece> &, unsigned int, unsigned int);
int print_game_board(ostream &, const vector<game_piece> &, unsigned int, unsigned int,int);
int print_game_board_neighbor(const vector<game_piece> &, unsigned int, unsigned int);