/*********************************************************************
** Program Filename: maze.cpp
** Author: Joshua Wentzel
** Date: 3/18/2018
** Description: Escape from CS162.
** Input: path to .txt containing maze data
** Output: Escape from CS162 gameplay
*********************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "maze.hpp"
#include "ta.hpp"
#include "additional.hpp"

using namespace std;

Maze::Maze(std::ifstream& input){
	numFloors = 0;
	currFloor = 0;
	safeTurns = 0;

	std::string line;
	std::getline(input, line);
	int floors, height, width, num;
	
	std::stringstream ss;
	ss << line;
	ss >> floors >> height >> width;
	
	if(floors <= 0)
		throw std::runtime_error("Data file error: invalid num floors");
	if(height <= 0)
		throw std::runtime_error("Data file error: invalid height");
	if(width <= 0)
		throw std::runtime_error("Data file error: invalid width");
	
	numFloors = floors;
	student = new IntrepidStudent();
	instructor = new Instructor();
	tas = new TA[2];
	lvls = new MazeLevel*[floors];
	
	try{
		for(int i = 0; i < floors; i++){
			lvls[i] = new MazeLevel(input, height, width);
			if(i != floors-1)
				lvls[i]->check_for_ladder();
			else
				lvls[i]->check_for_instructor();
		}
		
	}catch(const std::runtime_error& ex){
		throw ex;	// pass the exception up the chain to be handled
	}catch(...){
		cout << "Unidentified exception caught" << endl;
	}
}
Maze::~Maze(){
	for(int i = 0; i < numFloors; i++){
		delete lvls[i];
	}
	delete [] lvls;
	delete student;
	delete instructor;
	delete [] tas;
}
void Maze::printMaze(string info){
	cout << "\033[2J"; // clear the screen
	
	cout << "---- Escape from CS162 ----" << endl << endl << endl;
	
	lvls[currFloor]->display_level();
	
	cout << endl << info << endl << endl;
	
	if(safeTurns > 0)
		cout << "Turns before TAs become hostile: " << safeTurns << endl;
	else
		cout << "TAs are currently hostile." << endl;
		
	int skills = student->get_skills();
	cout << "Programming skills: " << skills << endl;
	
	if(skills > 0){
		cout << "Press 'P' to demonstrate a programming skill and";
		cout << " appease the TAs for 10 turns." << endl;
	}else{
		cout << "You have no programming skills left to demonstrate." << endl;
	}
	cout << "Use WASD keys to move." << endl;
	cout << "Press 'U' to go up ladders." << endl;
}
bool Maze::play(){
	student->set_skills(0);
	bool winFlag;
	string knowledge;
	while(true){	// floor loop
		bool instructorFlag = false;
		safeTurns = 0;
		winFlag = false;
		lvls[currFloor]->clearLevel();
		lvls[currFloor]->placeStudent(student);
		lvls[currFloor]->placeTAs(tas);
		lvls[currFloor]->placeInstructor(instructor);
		lvls[currFloor]->placeSkill();
		lvls[currFloor]->placeSkill();
		lvls[currFloor]->placeSkill();
		
		int targRow;
		int targCol;
		int initRow;
		int initCol;
		
		int height = lvls[currFloor]->get_height();
		int width = lvls[currFloor]->get_width();
		
		while(true){				// input loop
			printMaze(knowledge);	// print the maze with a possible message
			knowledge = "";			// clear the possible message after printing
			bool ladderFlag = false;
			targRow = student->get_row();
			targCol = student->get_col();
			initRow = student->get_row();
			initCol = student->get_col();
			
			switch(toupper(student->get_move())){
				case 'W': {
					targRow--;
					break;
				}
				case 'A': {
					targCol--;
					break;
				}
				case 'S': {
					targRow++;
					break;
				}
				case 'D': {
					targCol++;
					break;
				}
				case 'U': {
					if(lvls[currFloor]->get_location(targRow,targCol)->has_ladder()){
						ladderFlag = true;
					}
					else
					{
						continue;
					}
					break;
				}
				case 'P': {
					if(student->get_skills() > 0){
						safeTurns = 10;
						student->set_skills(student->get_skills()-1);
					}else{
						continue;
					}
					break;
				}
				default:
					continue;
			}
			if(targRow >= width)
				continue;
			if(targRow < 0)
				continue;
			if(targCol >= height)
				continue;
			if(targCol < 0)
				continue;
			if(!lvls[currFloor]->get_location(targRow,targCol)->is_occupiable())
				continue;
			if(ladderFlag){
				currFloor++;
				break;	// go to the next floor
			}
				
			lvls[currFloor]->get_location(initRow,initCol)->set_has_student(false);
			lvls[currFloor]->get_location(targRow,targCol)->set_has_student(true);
			student->set_location(targRow,targCol);
				
			if(lvls[currFloor]->get_location(targRow,targCol)->has_skill()){
				student->set_skills(student->get_skills()+1);
				lvls[currFloor]->get_location(targRow,targCol)->set_has_skill(false);
				knowledge = printRandomSkillName();
			}
			
			// check TA touching student
			
			if(safeTurns == 0){
				if(lvls[currFloor]->get_location(targRow,targCol)->has_ta()){
					student->set_skills(0);
					knowledge = "A hostile TA forced you to restart the lab.";
					break;
				}
				if(lvls[currFloor]->get_location(targRow+1,targCol)->has_ta()){
					student->set_skills(0);
					knowledge = "A hostile TA forced you to restart the lab.";
					break;
				}
				if(lvls[currFloor]->get_location(targRow-1,targCol)->has_ta()){
					student->set_skills(0);
					knowledge = "A hostile TA forced you to restart the lab.";
					break;
				}
				if(lvls[currFloor]->get_location(targRow,targCol+1)->has_ta()){
					student->set_skills(0);
					knowledge = "A hostile TA forced you to restart the lab.";
					break;
				}
				if(lvls[currFloor]->get_location(targRow,targCol-1)->has_ta()){
					student->set_skills(0);
					knowledge = "A hostile TA forced you to restart the lab.";
					break;
				}
			}
			
			// check for instructor
			if(lvls[currFloor]->get_location(targRow+1,targCol)->has_instructor()){
				instructorFlag = true;
			}
			if(lvls[currFloor]->get_location(targRow-1,targCol)->has_instructor()){
				instructorFlag = true;
			}
			if(lvls[currFloor]->get_location(targRow,targCol+1)->has_instructor()){
				instructorFlag = true;
			}
			if(lvls[currFloor]->get_location(targRow,targCol-1)->has_instructor()){
				instructorFlag = true;
			}
			if(instructorFlag){
				// instructor was detected, end the game
				if(student->get_skills() >= 3){
					winFlag = true;
				}else{
					winFlag = false;
				}
				break;
			}
			
			while(true){	// try moving first ta until the move is valid
				cout << "moving ta11" << endl;
				targRow = tas[0].get_row();
				targCol = tas[0].get_col();
				initRow = tas[0].get_row();
				initCol = tas[0].get_col();
				switch(toupper(tas[0].get_move())){
					case 'W': {
						targRow--;
						break;
					}
					case 'A': {
						targCol--;
						break;
					}
					case 'S': {
						targRow++;
						break;
					}
					case 'D': {
						targCol++;
						break;
					}
				}
				// check for validity
				if(targRow >= width){
					cout << "targRow >= width" << endl;
					continue;
				}
				if(targRow < 0){
					cout << "targRow < 0" << endl;
					continue;
				}
				if(targCol >= height){
					cout << "targCol >= height" << endl;
					continue;
				}
				if(targCol < 0){
					cout << "targCol < 0" << endl;
					continue;
				}
				if(!lvls[currFloor]->get_location(targRow,targCol)->is_occupiable()){
					cout << "occupied" << endl;
					continue;
				}
				// move was valid
				lvls[currFloor]->get_location(initRow,initCol)->set_has_ta(false);
				lvls[currFloor]->get_location(targRow,targCol)->set_has_ta(true);
				tas[0].set_location(targRow,targCol);
				break;
			}
			if(safeTurns == 0){	// has TA touched student
				if(lvls[currFloor]->get_location(targRow,targCol)->has_student()){
					student->set_skills(0);
					knowledge = "A hostile TA forced you to restart the lab.";
					break;
				}
				if(lvls[currFloor]->get_location(targRow+1,targCol)->has_student()){
					student->set_skills(0);
					knowledge = "A hostile TA forced you to restart the lab.";
					break;
				}
				if(lvls[currFloor]->get_location(targRow-1,targCol)->has_student()){
					student->set_skills(0);
					knowledge = "A hostile TA forced you to restart the lab.";
					break;
				}
				if(lvls[currFloor]->get_location(targRow,targCol+1)->has_student()){
					student->set_skills(0);
					knowledge = "A hostile TA forced you to restart the lab.";
					break;
				}
				if(lvls[currFloor]->get_location(targRow,targCol-1)->has_student()){
					student->set_skills(0);
					knowledge = "A hostile TA forced you to restart the lab.";
					break;
				}
			}
			
			while(true){	// try moving second ta until the move is valid
				cout << "moving ta2" << endl;
				targRow = tas[1].get_row();
				targCol = tas[1].get_col();
				initRow = tas[1].get_row();
				initCol = tas[1].get_col();
				switch(toupper(tas[1].get_move())){
					case 'W': {
						targRow--;
						break;
					}
					case 'A': {
						targCol--;
						break;
					}
					case 'S': {
						targRow++;
						break;
					}
					case 'D': {
						targCol++;
						break;
					}
				}
				// check for validity
				if(targRow >= width){
					cout << "targRow >= width" << endl;
					continue;
				}
				if(targRow < 0){
					cout << "targRow < 0" << endl;
					continue;
				}
				if(targCol >= height){
					cout << "targCol >= height" << endl;
					continue;
				}
				if(targCol < 0){
					cout << "targCol < 0" << endl;
					continue;
				}
				if(!lvls[currFloor]->get_location(targRow,targCol)->is_occupiable()){
					cout << "occupied" << endl;
					continue;
				}
				// move was valid
				lvls[currFloor]->get_location(initRow,initCol)->set_has_ta(false);
				lvls[currFloor]->get_location(targRow,targCol)->set_has_ta(true);
				tas[1].set_location(targRow,targCol);
				break;
			}	
			if(safeTurns == 0){	// has TA touched student
				if(lvls[currFloor]->get_location(targRow,targCol)->has_student()){
					student->set_skills(0);
					knowledge = "A hostile TA forced you to restart the lab.";
					break;
				}
				if(lvls[currFloor]->get_location(targRow+1,targCol)->has_student()){
					student->set_skills(0);
					knowledge = "A hostile TA forced you to restart the lab.";
					break;
				}
				if(lvls[currFloor]->get_location(targRow-1,targCol)->has_student()){
					student->set_skills(0);
					knowledge = "A hostile TA forced you to restart the lab.";
					break;
				}
				if(lvls[currFloor]->get_location(targRow,targCol+1)->has_student()){
					student->set_skills(0);
					knowledge = "A hostile TA forced you to restart the lab.";
					break;
				}
				if(lvls[currFloor]->get_location(targRow,targCol-1)->has_student()){
					student->set_skills(0);
					knowledge = "A hostile TA forced you to restart the lab.";
					break;
				}
			}
			if(safeTurns > 0)
				safeTurns--;
		}
		if(instructorFlag) // instructor was detected, end the game
			break;
	}
	return winFlag;
}