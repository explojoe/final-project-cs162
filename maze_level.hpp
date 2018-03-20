#ifndef _MAZELEVEL_
#define _MAZELEVEL_
#include <vector>
#include <fstream>
#include <iostream>

#include "maze_location.hpp"
#include "ta.hpp"
#include "intrepid_student.hpp"
#include "instructor.hpp"
//#include "intrepid_student.hpp"

class MazeLevel {
	private:
		//MazeLocation* locations2;
		std::vector<std::vector<MazeLocation*>> locations;
		int height;
		int width;

	public:
		bool isFinished;
	
		MazeLevel(std::ifstream&, int, int);
		~MazeLevel();
	
		MazeLocation* get_location(int, int);
	
		void display_level();
		
		void placeStudent(IntrepidStudent*);
		void placeInstructor(Instructor*);
		void placeTAs(TA*);
		void placeSkill();
		
		void clearLevel();
		
		void check_for_instructor();
		void check_for_ladder();
		
				
		int get_height();
		int get_width();
};
#endif