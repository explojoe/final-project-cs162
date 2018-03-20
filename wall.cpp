/*********************************************************************
** Program Filename: wall.cpp
** Author: Joshua Wentzel
** Date: 3/18/2018
** Description: Escape from CS162.
** Input: path to .txt containing maze data
** Output: Escape from CS162 gameplay
*********************************************************************/
#include <iostream>

#include "wall.hpp"

using namespace std;

Wall::Wall(){}

bool Wall::is_occupiable(){return false;}
char Wall::get_display_character(){return '#';}