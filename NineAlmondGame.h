#pragma once
#include"game_piece.h"
#include"Game.h"
#include<vector>
#include<iostream>
using namespace std;
class NineAlmondGame : public Game {
	friend ostream &operator << (ostream &, const NineAlmondGame &);
public:
	NineAlmondGame();
	virtual bool done() override;
	virtual bool stalemate() override;
	virtual int prompt(unsigned int &, unsigned int &) override;
	virtual int turn() override;
	virtual void print() override;
	
protected:
	game_piece brown_almond;
	game_piece empty;
	virtual bool is_vaild(unsigned int, unsigned int) override;
	int turn_next(unsigned int &, unsigned int &, ostringstream &);
};