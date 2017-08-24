#include "stdafx.h"
#include "utility.h"
#include <iostream>
#include <sstream>
#include <vector>
#include "game_piece.h"
#include <fstream>
#include <iomanip>
#include"game_board.h"

using namespace std;

// This function takes in an input file stream and the reference of two unsigned integers, and pulls out
//the dimensions from the file, and save them into those two integers.
int read_game_board(ifstream & input_file, unsigned int & first, unsigned int & second) {
	if (input_file.is_open() == false) {
		cout << "file does not exist" << endl;
		return exception_file_not_exsit;
	}
	string content;
	if (getline(input_file, content)) {
		istringstream numbers(content);
		if ((numbers >> first) && (numbers >> second)) {
			cout << "read  game board success" << endl;
			return success;
		}
		else {
			return number_read_failure;
		}
	}
	else {
		cout << "cannot read dimensions from the file!" << endl;
		return file_get_failure;
	}
}

// This function takes in an input file stream , a game piece and the reference of two unsigned integers, and pulls out
//the game piece from the file.
int read_game_piece(ifstream & source, vector<game_piece> & piece, unsigned int & first_dim, unsigned int & second_dim) {
	string definition;
	//to count how many game pieces are read from the file.
	int i = 0; 
	while (getline(source,definition)) {
		istringstream def(definition);
		string color;
		string name;
		string rule;
		unsigned int width =0;
		unsigned int length =0;
		if (def  >> color >> name >> rule >> width >> length) {
			piece_color pcolor = label_to_enum(color);
			if ((pcolor == invalid) || (width >= first_dim) || (length >= second_dim)) {
				//if the information extrated does not satisfy the requirement, get to next line.
				continue;
			}
			else {
				int index = length*first_dim +width;
				piece[index].color = pcolor;
				piece[index].name = name;
				piece[index].rule = rule;
				++i;
			}
		}
		//in this case, either 1 of those 5 needed information is not extracted successfully.
		else {
			continue;
		}
	}
	if (i > 0) {
		cout << "read game piece cuccess" << endl;
		return success;
	}
	// in this case ,nothing is obtained from the file.
	else {
		cout << "no piece definition found!" << endl;
		return no_piece_definition;
	}
}
//This function will print out the layout of a game board.
int print_game_board(const vector<game_piece> & piece, unsigned int first_dim, unsigned int second_dim) {
	return print_game_board(cout, piece, first_dim, second_dim, 1);
}

//This is an overload of print_game_board for lab 2
int print_game_board(ostream & out,const vector<game_piece> & piece, unsigned int first_dim, unsigned int second_dim) {
	return print_game_board(out, piece, first_dim, second_dim, 1);
}

//This is an overload of pirnt_game_board for lab 3
int print_game_board(ostream & out, const vector<game_piece> & piece, unsigned int first_dim, unsigned int second_dim, int max_string_length) {
	if (piece.size() != first_dim*second_dim) {
		cout << "dimensions are not matched! " << endl;
		return dim_not_match;
	}
	else {
		for (int j = second_dim - 1; j >= 0; --j) {
			out << j << " ";
			for (unsigned int i = 0; i < first_dim; ++i) {
				int pos = j*first_dim + i;
				out << setw(max_string_length) << piece[pos].rule << " ";
			}
			out << endl << endl;
		}
		out << "X ";
		for (unsigned int i = 0; i < first_dim; ++i) {
			out << setw(max_string_length) << i << " ";
		}
		out << endl;
		return success;
	}
}


// This function will print out the neighbors of a game piece (if it has neighbors)
int print_game_board_neighbor (const vector<game_piece> & piece, unsigned int first_dim, unsigned int second_dim) {
	if (piece.size() != first_dim*second_dim) {
		cout << "dimensions are not matched! " << endl;
		return dim_not_match;
	}
	else {
		cout << "the game board neighborhood displays below" << endl;
		cout << "=======================================================================" << endl;
		for (unsigned int i= 0; i < first_dim; ++i) {
			for (unsigned int j = 0; j < second_dim; ++j) {
				ostringstream display;
				int pos = j*first_dim + i;
				if(piece[pos].rule!=" "){
					display << i << "," << j << " " << piece[pos].rule << ": ";
				}
				else {
					continue;
				}
				int k = 0;
				if (j > 0) {
					pos = (j-1)*first_dim + i ;
					if (piece[pos].rule != " ") {
						display << i << "," << j-1 << " " << piece[pos].rule;
						++k;
					}
				}
				if(j<second_dim-1){
					pos = (j+1)*first_dim + i;
					if (piece[pos].rule != " ") {
						if (k != 0) {
							display << "; ";
						}
						display << i << "," << j + 1 << " " << piece[pos].rule;
						++k;
					}
				}
				if(i>0){
					pos = j*first_dim + i-1;
					if (piece[pos].rule != " ") {
						if (k != 0) {
							display << "; ";
						}
						display <<  i - 1 << "," << j << " " << piece[pos].rule ;
						++k;
					}
				}
				if (i<first_dim-1) {
					pos = j*first_dim + i+1;
					if (piece[pos].rule != " ") {
						if (k != 0) {
							display << "; ";
						}
						display <<  i + 1 << "," << j  << " " << piece[pos].rule ;
						++k;
					}
				}
				if ((i < first_dim-1) && (j < second_dim-1)) {
					pos = (j + 1)*first_dim + i + 1;
					if (piece[pos].rule != " ") {
						if (k != 0) {
							display << "; ";
						}
						display << i + 1 << "," << j + 1 << " " << piece[pos].rule ;
						++k;
					}
				}
				if ((i > 0) && (j > 0)) {
					pos = (j - 1)*first_dim + i-1;
					if (piece[pos].rule != " ") {
						if (k != 0) {
							display << "; ";
						}
						display << i - 1 << "," << j-1 << " " << piece[pos].rule ;
						++k;
					}
				}
				if (k == 0)
				{
					continue;
				}
				else {
					cout << display.str() << endl;
				}
			}
		}
		return success;
	}
}