/*********************************************************************
** Program Filename: main.cpp
** Author: Joshua Wentzel
** Date: 3/18/2018
** Description: Escape from CS162.
** Input: path to .txt containing maze data
** Output: Escape from CS162 gameplay
*********************************************************************/
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <time.h> 
#include <sstream>
#include <ctime>
#include <typeinfo>
#include <string>
#include <exception>
#include <stdexcept>

#include "maze.hpp"
#include "maze_location.hpp"

using namespace std;

int main(int argc, char *argv[]){
	if(argc == 2){
		ifstream input_file(argv[1]);
		if(input_file.is_open()){
			srand (time(NULL));	// give the random numbers a unique seed
			Maze* maze;
			try{
				maze = new Maze(input_file);
			}catch(const std::runtime_error& ex){
				cout << ex.what() << endl;
				delete maze;
				return 0;
			}catch(...){
				cout << "Unidentified exception caught" << endl;
			}
			string name;
			while(true){
				cout << "\033[2J"; // clear the screen
				cout << "Welcome to Escape from CS 162!" << endl;
				cout << "Prepare to be a-maze-d!" << endl;
				
				cout << "You ('*') must navigate the floors of the maze." << endl;
				cout << "Collect programming skills ('$') to appease ";
				cout << "the TAs ('T')." << endl;
				cout << "Climb ladders ('^') to ascend floors." << endl;
				cout << "The instructor ('%') is found on the final floor." << endl;
				cout << "Reach the instructor with three skills to pass the ";
				cout << "class." << endl;
				cout << "Reach him with fewer, and YOU FAIL, RETAKE THE CLASS!" << endl;

				cout << endl << endl;
				cout << "Enter your name to register for CS 162" << endl;
				std::cin.ignore();	// prevents getline() from being skipped in edge cases
				getline(cin,name);
				
				bool didWin = false;

				didWin = maze->play();

				int length = name.length();
				int leftRegionLength = 24;
				int rightRegionLength = 24;
				
				int leftNameLength = length/2;
				int rightNameLength = length - leftNameLength;
				
				std::stringstream nameStream;
				nameStream << ">";
				for(int i = 0; i < (leftRegionLength-leftNameLength); i++){
					nameStream << "-";
				}
				nameStream << name;
				for(int i = 0; i < (rightRegionLength-rightNameLength); i++){
					nameStream << "-";
				}
				nameStream << "<\n";
				
				if(didWin){
					cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
					cout << ">-------------OREGON STATE UNIVERSITY------------<" << endl;
					cout << ">------------------------------------------------<" << endl;
					cout << ">---------------This Certifies That--------------<" << endl;
					cout << ">------------------------------------------------<" << endl;
					cout << nameStream.str();
					cout << ">------------------------------------------------<" << endl;
					cout << ">-----------Has Demonstrated Excellence----------<" << endl;
					cout << ">-------------In Computer Science 162------------<" << endl;
					cout << ">------------------------------------------------<" << endl;
					cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
					cout << endl;
					cout << "Congratulations! To play again, enter 'y' or 'Y'" << endl;
				}else{
					cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
					cout << ">-------------OREGON STATE UNIVERSITY------------<" << endl;
					cout << ">------------------------------------------------<" << endl;
					cout << ">---------------This Certifies That--------------<" << endl;
					cout << ">------------------------------------------------<" << endl;
					cout << nameStream.str();
					cout << ">------------------------------------------------<" << endl;
					cout << ">--------------------Has Failed------------------<" << endl;
					cout << ">--------------Computer Science 162--------------<" << endl;
					cout << ">----------------Retake The Class----------------<" << endl;
					cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
					cout << endl;
					cout << "Game over. To play again, enter 'y' or 'Y'" << endl;
				}
				char response;
				cin >> response;
				if((response != 'y')&&(response != 'Y'))
					break;
			}
			delete maze;
		}else{
			cout << "Error: There was a problem opening the file." << endl;
		}
	}else{
		cout << "Please enter a valid path to the data file." << endl;
	}
	return 0;
}