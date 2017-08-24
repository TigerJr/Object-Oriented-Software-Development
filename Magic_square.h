#pragma once
#ifndef MAGIC_SQUARE_H
#define MAGIC_SQUARE_H
#include "Game.h"
using namespace std;

enum magicSquareConstants { MAGICROWS = 4, MAGICCOLS = 4 };

const string MAGIC_EMPTY_DISPLAY = " ";
class MagicSquare : public Game
{
	friend ostream &operator << (ostream &, const MagicSquare &);

public:
	MagicSquare();
	MagicSquare(int);
	MagicSquare(int, int);
	virtual void print() override;
	virtual bool done() override;
	virtual bool stalemate() override;
	virtual int prompt(int &);
	virtual int turn() override;
	bool containsPiece(game_piece);
	int strToNum(string);
	void printAvailable(vector<int>, ostream &);
	virtual int save_or_not(string) override;
protected:
	int difference;
	int max_string_length;
	vector<int> available_piece;
	game_piece empty;
	virtual bool is_vaild(unsigned int, unsigned int) override;
};
ostream &operator << (ostream &, const MagicSquare &);
#endif
