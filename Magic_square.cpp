#include "stdafx.h"
#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include"Game.h"
#include"utility.h"
#include "Magic_square.h"
#include "Game_board.h"
#include "math.h"


using namespace std;

int  MagicSquare::strToNum(string s)
{
	istringstream iss(s);
	int result;
	if (iss >> result)
	{
		return result;

	}
	else {
		return not_a_number;
		//error  : game piece is not a number  
	}

}



void MagicSquare::printAvailable(vector<int> available_piece, ostream & out=cout)
{
	ostringstream oss;
	oss << "Still Available pieces: ";
	for (int i : available_piece)
	{
		if (i != difference)
		{
			oss << i << " ";
		}
	}
	out << oss.str()<<	endl; 
}


bool MagicSquare::stalemate()
{

	for (game_piece g : game_board)
	{
		if (!containsPiece(g))
		{
			return false;
		}
	}
	return(!done());
}

void MagicSquare::print()
{
	cout << *this << endl; 
	printAvailable(available_piece);
}



bool MagicSquare::containsPiece(game_piece g) {

	for (unsigned int i = 0; i < (height*width); ++i) { 
		if (game_board[i] == empty) {
			return false;
		}
	}
	return true;

}
int MagicSquare::prompt(int & piece)
{
	cout << "Entering Number or Quit" << endl;
	unsigned int i = 0;
	while (true)
	{
		string input; 
		cin >> input;
		if (input == "quit")
		{
			throw  user_request_quit;  //exception
			return user_request_quit;
		}
		int content = strToNum(input);
		i =content-difference; 
		if ((i <= width*height) && (available_piece[i] == content)) //available piece
		{
			piece = content;
			return success;
		}
		else
		{
			cout << "Entered number is not valid" << endl;
			return not_a_number;
		}
	}
}


bool MagicSquare::done()
{
	int magicSum = width*(width*height + 1) / 2+difference*width;
	for (game_piece g : game_board)
	{
		if (!containsPiece(g))
		{
			return false;
		}
	}
	for (unsigned int i = 0; i< width*height; i += width)
	{
		int sum = 0;
		for (unsigned int j = i; j< i + width; ++j)
		{
			sum += strToNum(game_board[j].rule);
		}
		if (sum != magicSum)
		{
			return false;
		}
	}


	for (unsigned int i = 0; i< width; ++i)
	{
		int sum = 0;
		for (unsigned int j = i; j<height*width; j += width)
		{
			sum += strToNum(game_board[j].rule);
		}
		if (sum != magicSum)
		{
			return false;
		}
	}

	int sum = 0;
	for (unsigned int i = 0; i<width*height; i = i + width + 1)
	{

		sum += strToNum(game_board[i].rule);

	}
	if (sum != magicSum)
	{
		return false;
	}

	sum = 0;
	for (unsigned int i = width*(height - 1); i > 0; i = i - width + 1)
	{
		sum += strToNum(game_board[i].rule);

	}

	return (sum == magicSum);
}

bool MagicSquare::is_vaild(unsigned int s_width, unsigned int s_height) {
	if ((s_width <= width) && (s_height <= height)) {
		int s_pos=s_height*width+s_width;
		if (game_board[s_pos].name == "") {
			return true;
		}
		else {
			cout << "This position has been occupied!" << endl;
			return false;
		}
	}
	else {
		return false;
	}
}

int MagicSquare::turn() {
	unsigned int s_width;
	unsigned int s_height;
	int i = no_valid_input;
	while (i == no_valid_input) {
		cout <<endl<< "Please enter a cordinate or enter quit" << endl;
		if (Game::prompt(s_width, s_height) == user_request_quit) {
			return user_request_quit;
		}
		if (is_vaild(s_width,s_height)) {
			int number = 0;
			unsigned int num_pos = 0;
			while (available_piece[num_pos] == difference) {
				cout << endl;
				try {
					if (prompt(number) == success) {
						num_pos = number - difference;
					}
				}
				catch (return_type a) {
					if (a == user_request_quit) { return user_request_quit; }
				}
			}
			//update i
			++i;
			//update the gameboard
			int s_pos = s_width + s_height*width;
			game_board[s_pos].name = to_string(number);
			game_board[s_pos].rule = to_string(number);
			//update available pieces
			num_pos = number -difference;
			available_piece[num_pos] = difference;
			//print game board
			cout << endl;
			print();
		}
		else {
			cout << "The move take in is not valid!" << endl;
		}
	}
	if (stalemate()) {
		return no_valid_move;
	}
	else {
		return success;
	}
}

MagicSquare::MagicSquare(){
	 *this=MagicSquare(3, 1);
}
MagicSquare::MagicSquare(int n){
	*this = MagicSquare(n, 1);
}

MagicSquare::MagicSquare(int n,int start) {
	if (n <= 0) { throw dim_not_positive; }
	width = n;
	height = n;
	game_name = "MagicSquare";
	empty.color = none;
	empty.name = "";
	empty.rule = " ";
	difference = --start;
	ostringstream file_name;
	file_name << this->game_name << ".txt";
	cout << file_name.str() << endl;
	ifstream read_file(file_name.str());
	string first_line=" ";
	if (read_file.is_open()) {
		getline(read_file, first_line);// in case
	}
	if (first_line == game_name) {
		read_game_board(read_file, width, height);
	}
	int size = width*height;
	for (int i = 0; i <= size; ++i) {
		available_piece.push_back(i + difference);
	}
	for (int i = 0; i < size; ++i) {
		game_board.push_back(empty);
	}
	if (first_line == game_name) {
		for (game_piece & i : game_board) {
			string temp_line;
			string color;
			getline(read_file, temp_line);
			istringstream  temp(temp_line);
			if (temp >> color >> i.name >> i.rule) {
				i.color = label_to_enum(color);
			}
		}
		string temp_line;
		getline(read_file, temp_line);
		istringstream  temp(temp_line);
		for (int & i : available_piece) {
			temp >> i;
		}
		difference = *available_piece.begin();
		}
	int num = size + difference;
	++num;//to get the digit number of the maximum number
	max_string_length = (int)ceil(log10(abs(num)));
	if (num < 0) {
		++max_string_length;
	}
}

ostream &operator << (ostream & out, const MagicSquare & game) {
	//use an overload of print function written in lab1
	print_game_board(out, game.game_board, game.width, game.height,game.max_string_length);
	return out;
}

int MagicSquare::save_or_not(string game_name) {
	string yrn;
	cout << " Do you want to save the magicsquare game ?( 'yes' to save, 'no' to quit )" << endl;
	cin >> yrn;
	to_lower_case(yrn);
	while (yrn != "yes"&&yrn != "no") {
		cout << "please type in yes or no." << endl;
		cin >> yrn;
		to_lower_case(yrn);
	}
	ostringstream file_name;
	file_name<<game_name<<".txt";
	ofstream save_file(file_name.str());
	if (yrn == "no") {
		save_file << "NO DATA" << endl;
		return not_saving_game;
	}
	else {
		save_file << game_name << endl;
		save_file << this->width << " " << this->height << endl;
		for (game_piece i : game_board) {
			save_file <<enum_to_label( i.color )<< " " << i.name << " " << i.rule << endl;
		}
		for (int i : available_piece) {
				save_file << i << " ";
		}
		save_file << endl;
		save_file.close();
		return success;
	}
}

