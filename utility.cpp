#include "stdafx.h"
#include <iostream>
#include "utility.h"

using namespace std;

//This function convert all charactors of a string to lower case.
void to_lower_case(string & content)
{
	int difference = 'A' - 'a';
	for (unsigned int i = 0;i < content.size();++i) {
		if ((content[i] <= 'Z') && (content[i] >= 'A')) {
			content[i] -= difference;
		}
	}
}

//This funciton takes in the name of program, and outputs its usage message to guide the users to put in the information needed.
void usage_message(char * prog_name) {

	cout << "Usage:" << prog_name << '\n' << endl;
	cout << "Here's the instruction on how to run the program correctly" << '\n' << endl;
	cout << "This program will print out a game board of a game and allows user to play the game given the game name. " << endl;
	cout << "In order to run the program properly, the user should provide the name of game one wants to open," << endl;
	cout << " For example,"<< prog_name<<" NineAlmonds." << '\n' << endl;
	cout << "To start a Magic Square game, user could also type in the dimension and start value" << endl;
	cout << "Please type in as required above again" << '\n' << endl;
}