/*********************************************************************
** Program Filename: maze_person.cpp
** Author: Joshua Wentzel
** Date: 3/18/2018
** Description: Escape from CS162.
** Input: path to .txt containing maze data
** Output: Escape from CS162 gameplay
*********************************************************************/
#include <iostream>

#include "maze_person.hpp"

using namespace std;

void MazePerson::set_location(int r, int c){
	row = r;
	col = c;
}
int MazePerson::get_row(){return row;}
int MazePerson::get_col(){return col;}