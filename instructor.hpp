#ifndef _INSTRUCTOR_
#define _INSTRUCTOR_

#include "maze_person.hpp"

class Instructor: public MazePerson {
	public:
		Instructor();
	
		char get_move();
		//void set_location(int, int);
		//int get_row();
		//int get_col();
};
#endif