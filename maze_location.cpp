/*********************************************************************
** Program Filename: maze_location.cpp
** Author: Joshua Wentzel
** Date: 3/18/2018
** Description: Escape from CS162.
** Input: path to .txt containing maze data
** Output: Escape from CS162 gameplay
*********************************************************************/
#include <iostream>

#include "maze_location.hpp"

using namespace std;

void MazeLocation::reset(){}

void MazeLocation::set_has_student(bool b){}
void MazeLocation::set_has_ta(bool b){}
void MazeLocation::set_has_instructor(bool b){}
void MazeLocation::set_has_ladder(bool b){}
void MazeLocation::set_has_skill(bool b){}
void MazeLocation::set_has_start(bool b){}

bool MazeLocation::has_student(){return false;}
bool MazeLocation::has_ta(){return false;}
bool MazeLocation::has_instructor(){return false;}
bool MazeLocation::has_ladder(){return false;}
bool MazeLocation::has_skill(){return false;}
bool MazeLocation::has_start(){return false;}