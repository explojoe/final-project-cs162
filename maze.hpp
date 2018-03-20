#ifndef _MAZE_
#define _MAZE_
#include <fstream>
#include <iostream>

#include "maze_level.hpp"
#include "maze_person.hpp"
#include "ta.hpp"
#include "intrepid_student.hpp"
#include "instructor.hpp"

//#include "intrepid_student.hpp"

class Maze {
	private:
		MazeLevel** lvls;
		IntrepidStudent* student;
		Instructor* instructor;
		TA* tas;
		int numFloors;
		
		int currFloor;
		int safeTurns;

	public:

		Maze(std::ifstream&);
		~Maze();
		
		void printMaze(std::string);
		
		bool play();


};
#endif