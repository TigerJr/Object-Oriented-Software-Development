#ifndef REVERSIGAME_H
#define REVERSIGAME_H
#include <string>
#include "Game.h"
using namespace std;

const game_piece BLACK_PIECE = game_piece(black, "Black_Piece", "X");
const game_piece WHITE_PIECE = game_piece(white, "White_Piece", "O");

class ReversiGame : public Game {
	friend ostream & operator<< (ostream&, const ReversiGame&);

public:
	
	ReversiGame();

	ReversiGame(string, string);

	virtual void print() override;

	virtual bool done() override;

	virtual bool stalemate()override;

	virtual int turn()override;

private:
	
protected:
	string pB;
	string pW;
	virtual bool is_vaild(unsigned int, unsigned int) override;
	static string current;
	vector<int> neighbor(unsigned int i, unsigned int j);
	bool is_boundary(unsigned int);

	bool movesRemain();
	bool isValidMove(game_piece, int, int, int, piece_color, vector<int> &);


	bool movesRemain(string);

	bool bound(int, int, game_piece, int);

	bool findValidNeighbor(int, int, int, int, game_piece, int);

	bool iterateThroughNeighbor(int, int, game_piece, int, int);
};

ostream & operator<< (ostream&, const ReversiGame&);
#endif 
