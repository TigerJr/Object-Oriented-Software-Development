#include "stdafx.h"
#include "game_piece.h"
#include "game_board.h"
#include "ReversiGame.h"
#include "utility.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

string ReversiGame::current = "";

ostream& operator<< (ostream& o, const ReversiGame & game)
{

	print_game_board(o, game.game_board, 8, 8, game.max_string_length);

		return o;
}

ReversiGame::ReversiGame(string playerBlack, string playerWhite)
	:Game(8, 8), pB(playerBlack), pW(playerWhite)
{
	game_name = "ReversiGame";

	current = pB;

	ostringstream file_name;
	file_name << game_name << ".txt";

	ifstream ifsInitial(file_name.str());

	ifstream&& ifs=move(ifsInitial);
	string name ;
	getline(ifs, name);
	if ((!ifs.is_open())||(name == "NO DATA"))
	{
		for (unsigned int i = 0; i < width; ++i)
		{
			for (unsigned int j = 0; j < height; ++j)
			{
				game_piece p = game_piece();

				game_board.push_back(p);

				if (int(p.rule.size()) > max_string_length)
				{
					max_string_length = p.rule.size();
				}
			}
		}
		game_board[unsigned(.5*width*height + .5*height)] = BLACK_PIECE;
		game_board[unsigned((.5*width - 1)*height + (.5*height - 1))] = BLACK_PIECE;
		game_board[unsigned((.5*width - 1)*height + .5*height)] = WHITE_PIECE;
		game_board[unsigned((.5*width)*height + .5*height - 1)] = WHITE_PIECE;
	}
	else
	{
		if (current != pB && current != pW)
		{
			string input;
			cout << "Wrong name supplied !!" << endl;
			cout << "type \"Terminate\" " << endl;
			cin >> input;
			if (input == "Terminate")
			{
				ofstream ofs(game_name);
				if (!ofs.is_open())
				{
					cout << "cannot open the file"<< endl;
				}
				ofs << "NO DATA" << endl;

			}

		}

		string ints;
		getline(ifs, ints);
		istringstream iss(ints);
		if (!(iss >> width))
		{
			cout << "row error " << endl;
		}



		if (!(iss >> height))
		{
			cout << "column error " << endl;
		}

		string pc;
		while (getline(ifs, pc))
		{
			istringstream iss5(pc);
			game_piece gPiece;
			string temp;
			iss5 >> temp;
			gPiece.color = label_to_enum(temp);
			iss5 >> gPiece.name;
			iss5 >> gPiece.rule;
			game_board.push_back(gPiece);
		}
		int counter = 0;
		for (game_piece g : game_board) {
			if (g.name != "") { ++counter; }
		}
		if (counter % 2) {
			current = pW;
		}
	}
}

void ReversiGame::print()
{
		cout << *this << endl;
	

}


bool ReversiGame::done()
{
	bool hasWhite = false;
	int whiteCount = 0;
	bool hasBlack = false;
	int blackCount = 0;
	for (game_piece gp : game_board)
	{
		if (gp.color == white)
		{
			hasWhite = true;
			++whiteCount;
		}

		if (gp.color == black)
		{
			hasBlack = true;
			++blackCount;
		}
	}


	if ((hasWhite || hasBlack) && !(hasWhite && hasBlack))
	{
		if (blackCount > whiteCount)
		{
			cout << "Winner! " << pB << endl;
		}
		else
			cout << "Winner! " << pW << endl;
		return true;
	}

	else if (whiteCount != blackCount)
	{
		if ((whiteCount + blackCount) == 64)
		{
			if (blackCount > whiteCount)
			{
				cout << "Winner! " << pB << endl;
			}
			else
				cout << "Winner! " << pW << endl;
			return true;
		}
		else
		{
			if (!(this->movesRemain()))
			{
				if (blackCount > whiteCount)
				{
					cout << "Winner! " << pB << endl;
				}
				else
					cout << "Winner! " << pW << endl;
				return true;
			}
			else
				return false;
		}
	}
	else
		return false;
}


bool ReversiGame::stalemate()
{
	int whiteCount = 0;
	int blackCount = 0;
	for (game_piece gp : game_board)
	{
		if (gp.color == white)
			++whiteCount;
		if (gp.color == black)
			++blackCount;
	}


	return ((whiteCount == blackCount) && (whiteCount + blackCount == 64 || !(this->movesRemain())));
}

bool ReversiGame::movesRemain()
{
	game_piece current;
	int index;
	for (unsigned int i = 0; i < width; ++i)
	{
		for (unsigned int j = 0; j < height; ++j)
		{
			index = i*height + j;
			current = game_board[index];
			if (current.color != none)
			{
      				if (bound(i, j, current, index))
					return true;
			}
		}
	}
	return false;
}

bool ReversiGame::movesRemain(string player)
{
	game_piece current;
	int index;
	for (unsigned int i = 0; i < width; ++i)
	{
		for (unsigned int j = 0; j < height; ++j)
		{
			index = i*height + j;
			current = game_board[index];
			if (player == pB)
			{
				if (current.color == black)
				{
					if (bound(i, j, current, index))
						return true;
				}
			}
			else if (player == pW)
			{
				if (current.color == white)
				{
					if (bound(i, j, current, index))
						return true;
				}
			}
		}
	}
	return false;
}

bool ReversiGame::bound(int i, int j, game_piece current, int index)
{
	int low_y, up_y, low_x, up_x;

	if (i == 0)
	{
		low_y = i;
		up_y = i + 1;
	}
	else if (i == width - 1)
	{
		up_y = i;
		low_y = i - 1;
	}
	else {
		up_y = i + 1;
		low_y = i - 1;
	}
	if (j == 0)
	{
		low_x = j;
		up_x = j + 1;
	}
	else if (j == height - 1)
	{
		up_x = j;
		low_x = j - 1;
	}
	else {
		up_x = j + 1;
		low_x = j - 1;
	}
	return findValidNeighbor(low_y, up_y, low_x, up_x, current, index);
}

bool ReversiGame::findValidNeighbor(int low_y, int up_y, int low_x, int up_x, game_piece current, int index)
{
	for (int k = low_y; k <= up_y; ++k)
	{
		for (int l = low_x; l <= up_x; ++l)
		{
			int neighbor_index = (height * k) + l;
			game_piece neighbor = game_board[neighbor_index];
			if (neighbor.color != current.color)
			{
				if (iterateThroughNeighbor(k, l, neighbor, index, neighbor_index))
					return true;
			}
		}
	}
	return false;
}

bool ReversiGame::iterateThroughNeighbor(int i, int j, game_piece current, int index, int currIndex)
{
	int low_y, up_y, low_x, up_x;

	if (i == 0)
	{
		low_y = i;
		up_y = i + 1;
	}
	else if (i == width - 1)
	{
		up_y = i;
		low_y = i - 1;
	}
	else {
		up_y = i + 1;
		low_y = i - 1;
	}
	if (j == 0)
	{
		low_x = j;
		up_x = j + 1;
	}
	else if (j == height - 1)
	{
		up_x = j;
		low_x = j - 1;
	}
	else {
		up_x = j + 1;
		low_x = j - 1;
	}

	game_piece neighbor;
	int neighbor_index = currIndex + (currIndex - index);

	for (int k = low_y; k <= up_y; ++k)
	{
		for (int l = low_x; l <= up_x; ++l)
		{

			if (neighbor_index == k* height + l)
			{
				neighbor = game_board[neighbor_index];
				if (neighbor.color == none)
					return true;
				else if (neighbor.color == current.color)
				{
					i = neighbor_index / height;
					j = neighbor_index % height;
					return iterateThroughNeighbor(i, j, neighbor, currIndex, neighbor_index);
				}
				else
					return false;
			}
		}
	}

	return false;

}

bool ReversiGame::isValidMove(game_piece current, int index, int j, int i, piece_color curCol, vector<int> & toChange)
{
	int low_y, up_y, low_x, up_x;

	if (i == 0)
	{
		low_y = i;
		up_y = i + 1;
	}
	else if (i == width - 1)
	{
		up_y = i;
		low_y = i - 1;
	}
	else {
		up_y = i + 1;
		low_y = i - 1;
	}
	if (j == 0)
	{
		low_x = j;
		up_x = j + 1;
	}
	else if (j == height - 1)
	{
		up_x = j;
		low_x = j - 1;
	}
	else {
		up_x = j + 1;
		low_x = j - 1;
	}


	for (int k = low_y; k <= up_y; ++k)
	{
		for (int l = low_x; l <= up_x; ++l)
		{
			int neighbor_index = (height * k) + l;
			game_piece neighbor = game_board[neighbor_index];
			if (curCol != neighbor.color && neighbor.color != none)
			{
				if (iterateThroughNeighbor(k, l, neighbor, index, neighbor_index)) {
					int dest = neighbor_index;
					while (game_board[dest].color != curCol)
					{
						toChange.push_back(dest);
						dest += neighbor_index - index;
					}
				}

			}
		}
	}
	return !toChange.empty();

}

int ReversiGame::turn()
{

	bool invalidInput = true;
	unsigned int x, y;

	if (current == pB)
	{
		cout << endl;
		cout << current << "'s turn   BLACK (X)" << endl;
		while (invalidInput == true)
		{
			cout << "select the location that you wanna take a place" << endl;
			if (prompt(x, y) == user_request_quit) {
				return user_request_quit;
			};
			if (is_vaild(x, y)) {
				cout << "move successfully" << endl;
				invalidInput = false;
			}
			else
			{
				cout << "Not valid coordinate , please select a valid one" << endl;
			}
		}
		current = pW;
		invalidInput = true;
		print();
		}

		if (current == pW)
		{
			cout << current << "s turn   WHITE (O)" << endl;
			while (invalidInput)
			{
				cout << "select the location that you wanna take a place" << endl;
				if (prompt(x, y) == user_request_quit) {
					return user_request_quit;
				};
				if (is_vaild(x, y)) {
					cout << "move successfully" << endl;
					invalidInput = false;
				}
				else
				{
					cout << "Not valid coordinate , please select a valid one" << endl;
				}
			}
			current = pB;
			invalidInput = true;
			print();
		}
		if (current != pB && current != pW) {
			cout << "PLAYER NAME ERROR" << endl;
		}


		return success;
	}

	bool ReversiGame::is_vaild(unsigned int i, unsigned int j) {
		bool indicator = false;
		if (i < 0 || i >= width || j < 0 || j >= height) { return indicator; }
		else if (game_board[i + j*width].color != none) { return indicator; }
		vector<int> neighborhood = neighbor(i, j);
		for (int a : neighborhood) {
			if (is_boundary(a)) {
				continue;
			}
			piece_color currcol;
			if (current == pB) {
				currcol = black;
			}
			else {
				currcol = white;
			}
			int difference = i + j*width - a;// use substraction afterwards!!!
			int pos = a - difference;
			int counter = 1;
			while (pos > 0 && pos < game_board.size()) {
				if (game_board[pos].color == currcol) {
					indicator = true;
					// update gameboard
					for (int b = 0; b <= counter; ++b) {
						game_board[pos+difference+ b*difference] = game_board[pos];
					}
					pos = difference;//make sure it will jump out of while loop
				}
				else if (game_board[pos].color == none) {
					pos = difference;//make sure it will jump out of while loop
				}
				if (is_boundary(pos)) {
					pos = difference;//make sure it will jump out of while loop
				}
				pos -= difference;
				//add counter
				++counter;
			}
		}
		return indicator;
	}

vector<int> ReversiGame::neighbor(unsigned int j, unsigned int i) {
	vector<int> v;
	int low_y, up_y, low_x, up_x;

	if (i == 0)
	{
		low_y = i;
		up_y = i + 1;
	}
	else if (i == width - 1)
	{
		up_y = i;
		low_y = i - 1;
	}
	else {
		up_y = i + 1;
		low_y = i - 1;
	}
	if (j == 0)
	{
		low_x = j;
		up_x = j + 1;
	}
	else if (j == height - 1)
	{
		up_x = j;
		low_x = j - 1;
	}
	else {
		up_x = j + 1;
		low_x = j - 1;
	}
	piece_color difcol;
	if (current == pB) {
		difcol = white;
	}
	else {
		difcol = black;
	}
	for (int a = low_x; a <= up_x; ++a) {
		for (int b = low_y; b <= up_y; ++b) {
			int pos = a + b*width;
			if (game_board[pos].color == difcol) {
				v.push_back(pos);
			}
		}
	}
	return v;
};
bool ReversiGame::is_boundary(unsigned int i) {
	if (i % width == 0 || i%width == width - 1) { return true; }
	else if (i > 0 && i < width) { return true; }
	else if (i > width*height - width&&i < width*height) { return true; }
	else { return false; }
}

ReversiGame::ReversiGame() {};