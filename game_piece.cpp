#include "stdafx.h"
#include "game_piece.h"
#include "utility.h"
#include <sstream>
#include <iostream>

using namespace std;

//This overloads operator ==
bool game_piece::operator== (game_piece a) {
	if ((color == a.color) && (name == a.name) && (rule == a.rule)) {
		return true;
	}
	else {
		return false;
	}
}

// This function convert a piece_color type to a string, essentially explaining what a enumeration means.
string enum_to_label(piece_color color) {
	if (color == piece_color::red) {
		return "red";
	}
	else if (color == piece_color::black) {
		return "black";
	}
	else if (color == piece_color::white) {
		return "white";
	}
	else if (color == piece_color::none) {
		return "none";
	}
	else {
		return "invalid";
	}
}

//This function converts a string to a piece_color, essentially enumarating a label.
piece_color label_to_enum(string name) {
	to_lower_case(name);
	if (name == "red") {
		return piece_color::red;
	}
	else if (name == "black") {
		return piece_color::black;
	}
	else if (name == "white") {
		return piece_color::white;
	}
	else if (name == "none") {
		return piece_color::none;
	}
	else {
		return piece_color::invalid;
	}
}
game_piece::game_piece() {
	color = none;
    name = "";
	rule = " ";
}


game_piece::game_piece(piece_color c, string n, string r) :color(c), name(n), rule(r) {}