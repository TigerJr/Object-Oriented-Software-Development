#pragma once
#include <string>
enum return_type {
	success = 0, file_get_failure, number_read_failure,game_not_exist,no_valid_input,not_a_number, dim_not_positive,
	no_piece_definition, dim_not_match, exception_file_not_exsit, user_request_quit,no_valid_move, no_game_exist,
	game_already_exist,out_of_memory, not_saving_game
};
enum usefulconstants {
	prog_name_pos = 0,game_name_pos = 1, no_input_game_name = 1,expected_command_line_size = 2
};
void to_lower_case(std::string &);
void usage_message(char *);
