/*********************************************************************
** Program Filename: intrepid_student.cpp
** Author: Joshua Wentzel
** Date: 3/18/2018
** Description: Escape from CS162.
** Input: path to .txt containing maze data
** Output: Escape from CS162 gameplay
*********************************************************************/
#include <iostream>
#include <string>
#include "intrepid_student.hpp"

using namespace std;

IntrepidStudent::IntrepidStudent(){
	skills = 0;
}
void IntrepidStudent::set_skills(int s){skills = s;}
int IntrepidStudent::get_skills(){return skills;}
char IntrepidStudent::get_move(){
	string s;
	getline(cin,s);
	if(s.length() == 0)
		return ' ';
	return s.at(0);
}