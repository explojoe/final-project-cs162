/*********************************************************************
** Program Filename: open_space.cpp
** Author: Joshua Wentzel
** Date: 3/18/2018
** Description: Escape from CS162.
** Input: path to .txt containing maze data
** Output: Escape from CS162 gameplay
*********************************************************************/
#include <iostream>

#include "open_space.hpp"

using namespace std;

OpenSpace::OpenSpace(){
	hasStudent = false;
	hasTA = false;
	hasInstructor = false;
	hasLadder = false;
	hasSkill = false;
	hasStart = false;
}
void OpenSpace::reset(){
	if(hasStart)
		hasStudent = true;
	else
		hasStudent = false;
	hasTA = false;
	hasSkill = false;
}
void OpenSpace::set_has_student(bool b){hasStudent = b;}
void OpenSpace::set_has_ta(bool b){hasTA = b;}
void OpenSpace::set_has_instructor(bool b){hasInstructor = b;}
void OpenSpace::set_has_ladder(bool b){hasLadder = b;}
void OpenSpace::set_has_skill(bool b){hasSkill = b;}
void OpenSpace::set_has_start(bool b){hasStart = b;}

bool OpenSpace::has_student(){return hasStudent;}
bool OpenSpace::has_ta(){return hasTA;}
bool OpenSpace::has_instructor(){return hasInstructor;}
bool OpenSpace::has_ladder(){return hasLadder;}
bool OpenSpace::has_skill(){return hasSkill;}
bool OpenSpace::has_start(){return hasStart;}
bool OpenSpace::is_occupiable(){
	return true;
}
char OpenSpace::get_display_character(){
	if(hasStudent)
		return '*';
	if(hasTA)
		return 'T';
	if(hasInstructor)
		return '%';
	if(hasSkill)
		return '$';
	if(hasStart)
		return '@';
	if(hasLadder)
		return '^';
	return ' ';
}