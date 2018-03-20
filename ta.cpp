/*********************************************************************
** Program Filename: ta.cpp
** Author: Joshua Wentzel
** Date: 3/18/2018
** Description: Escape from CS162.
** Input: path to .txt containing maze data
** Output: Escape from CS162 gameplay
*********************************************************************/
#include <iostream>

#include "ta.hpp"

using namespace std;

TA::TA(){
	isAppeased = false;
}
char TA::get_move(){
	int num = rand()%4;
	if(num == 0){
		return 'W';
	}else if(num == 1){
		return 'D';
	}else if(num == 2){
		return 'S';
	}else{
		return 'A';
	}	
}
void TA::set_is_appeased(bool b){isAppeased = b;}
bool TA::is_appeased(){return isAppeased;}