/*********************************************************************
** Program Filename: maze_level.cpp
** Author: Joshua Wentzel
** Date: 3/18/2018
** Description: Escape from CS162.
** Input: path to .txt containing maze data
** Output: Escape from CS162 gameplay
*********************************************************************/
#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stdexcept>

#include "maze_level.hpp"
#include "maze_person.hpp"
#include "ta.hpp"
#include "intrepid_student.hpp"
#include "instructor.hpp"
#include "maze_location.hpp"
#include "wall.hpp"

#include "open_space.hpp"

MazeLevel::MazeLevel(std::ifstream& floorData, int width, int height){
	
	this->width = width;
	this->height = height;
	
	int startPoints = 0;
	int endPoints = 0;
	
	locations = std::vector<std::vector<MazeLocation*>>
		(height, std::vector<MazeLocation*>(width, NULL));
	std::string line;
	
	for(int r = 0; r < height; r++){
		std::getline(floorData, line);
		if(line.length()-1 != width){
			throw std::runtime_error("Data file error: maze width not uniform");
		}
		
		for(int c = 0; c < width; c++){
			if(line[c] == '#'){
				// wall
				locations[r][c] = new Wall();
			}else if(line[c] == '^'){
				// ladder
				endPoints++;
				locations[r][c] = new OpenSpace();
				locations[r][c]->set_has_ladder(true);
			}else if(line[c] == '@'){
				// player start
				startPoints++;
				locations[r][c] = new OpenSpace();
				locations[r][c]->set_has_start(true);
				locations[r][c]->set_has_student(true);
			}else if(line[c] == '%'){
				// instructor
				endPoints++;
				locations[r][c] = new OpenSpace();
				locations[r][c]->set_has_instructor(true);
			}else{
				// empty space
				locations[r][c] = new OpenSpace();
			}
		}
	}
	if(endPoints != 1)
		throw std::runtime_error("Data file error: floor requires single end");
	if(startPoints != 1)
		throw std::runtime_error("Data file error: floor requires single start ('@')");
}
void MazeLevel::check_for_instructor(){
	bool ladderFlag = false;
	bool instructorFlag = false;
	
	for(int r = 0; r < height; r++){
		for(int c = 0; c < width; c++){
			if(locations[r][c]->has_ladder())
				ladderFlag = true;
			if(locations[r][c]->has_instructor())
				instructorFlag = true;
		}
	}
	if(ladderFlag)
		throw std::runtime_error("Data file error: final floor has ladder ('^')");
	if(!instructorFlag)
		throw std::runtime_error("Data file error: final floor has no instructor ('%')");
}
void MazeLevel::check_for_ladder(){
	bool ladderFlag = false;
	bool instructorFlag = false;
	for(int r = 0; r < height; r++){
		for(int c = 0; c < width; c++){
			if(locations[r][c]->has_ladder())
				ladderFlag = true;
			if(locations[r][c]->has_instructor())
				instructorFlag = true;
		}
	}
	if(!ladderFlag)
		throw std::runtime_error("Data file error: non final floor has no ladder ('^')");
	if(instructorFlag)
		throw std::runtime_error("Data file error: non final floor has instructor ('%')");
}
void MazeLevel::clearLevel(){
	for(int r = 0; r < height; r++){
		for(int c = 0; c < width; c++){
			locations[r][c]->reset();
		}
	}
}
void MazeLevel::placeStudent(IntrepidStudent* student){
	for(int r = 0; r < height; r++){
		for(int c = 0; c < width; c++){
			if(locations[r][c]->has_start()){
				student->set_location(r,c);
			}
		}
	}
}
void MazeLevel::placeInstructor(Instructor* instructor){
	for(int r = 0; r < height; r++){
		for(int c = 0; c < width; c++){
			if(locations[r][c]->has_instructor()){
				instructor->set_location(r,c);
			}
		}
	}
}
void MazeLevel::placeTAs(TA* tas){
	int validSpots = 0;
	for(int r = 0; r < height; r++){
		for(int c = 0; c < width; c++){
			if(!(locations[r][c]->is_occupiable()))
				continue;
			if(locations[r][c]->has_instructor())
				continue;
			if(locations[r][c]->has_start())
				continue;
			if(locations[r][c]->has_ta())
				continue;
			validSpots++;
		}
	}
	int randIdx = rand()%validSpots;
	int idx = 0;
	for(int r = 0; r < height; r++){
		for(int c = 0; c < width; c++){
			if(idx >= validSpots) 
				break;
			if(!(locations[r][c]->is_occupiable()))
				continue;
			if(locations[r][c]->has_instructor())
				continue;
			if(locations[r][c]->has_start())
				continue;
			if(locations[r][c]->has_ta())
				continue;
			if(idx == randIdx){
				locations[r][c]->set_has_ta(true);
				std::cout << locations[r][c]->is_occupiable() << std::endl;
				tas[0].set_location(r,c);
				validSpots--;
			}
			idx++;
		}
	}
	randIdx = rand()%validSpots;
	idx = 0;
	for(int r = 0; r < height; r++){
		for(int c = 0; c < width; c++){
			if(idx >= validSpots)
				break;
			if(!(locations[r][c]->is_occupiable()))
				continue;
			if(locations[r][c]->has_instructor())
				continue;
			if(locations[r][c]->has_start())
				continue;
			if(locations[r][c]->has_ta())
				continue;
			if(idx == randIdx){
				locations[r][c]->set_has_ta(true);
				tas[1].set_location(r,c);
			}
			idx++;
		}
	}
}
void MazeLevel::placeSkill(){
	int validSpots = 0;
	for(int r = 0; r < height; r++){
		for(int c = 0; c < width; c++){
			if(!locations[r][c]->is_occupiable())
				continue;
			if(locations[r][c]->has_instructor())
				continue;
			if(locations[r][c]->has_start())
				continue;
			if(locations[r][c]->has_ta())
				continue;
			if(locations[r][c]->has_skill())
				continue;
			if(locations[r][c]->has_ladder())
				continue;
			validSpots++;
		}
	}
	int randIdx = rand()%validSpots;
	int idx = 0;
	for(int r = 0; r < height; r++){
		for(int c = 0; c < width; c++){
			if(idx >= validSpots)
				break;
			if(!locations[r][c]->is_occupiable())
				continue;
			if(locations[r][c]->has_instructor())
				continue;
			if(locations[r][c]->has_start())
				continue;
			if(locations[r][c]->has_ta())
				continue;
			if(locations[r][c]->has_skill())
				continue;
			if(locations[r][c]->has_ladder())
				continue;
			if(idx == randIdx){
				locations[r][c]->set_has_skill(true);
				validSpots--;
			}
			idx++;
		}
	}
}
int MazeLevel::get_height(){
	return height;
}
int MazeLevel::get_width(){
	return width;
}
MazeLevel::~MazeLevel(){
	for(int r = 0; r < height; r++){
		for(int c = 0; c < width; c++){
			delete locations[r][c];
		}
	}
}
MazeLocation* MazeLevel::get_location(int r,int c){
	return locations[r][c];
}
void MazeLevel::display_level(){
	for(int r = 0; r < height; r++){
		for(int c = 0; c < width; c++){
			std::cout << locations[r][c]->get_display_character();
		}
		std::cout << std::endl;
	}
}