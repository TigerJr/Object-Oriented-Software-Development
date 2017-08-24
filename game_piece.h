#pragma once
#include <string>
enum piece_color
{
	none = 100, red, black, white, invalid = 999
};
std::string enum_to_label(piece_color);
piece_color label_to_enum(std::string);
struct game_piece
{
	piece_color color;
	std::string name;
	std::string rule;
	game_piece();
	game_piece(piece_color,std::string,std::string);
	bool operator == (game_piece);
};
