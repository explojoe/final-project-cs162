#ifndef _INTREPIDSTUDENT_
#define _INTREPIDSTUDENT_

#include "maze_person.hpp"

class IntrepidStudent: public MazePerson {
	private:
		int skills;
	public:
		IntrepidStudent();
		

		void set_skills(int);
		int get_skills();
	
		char get_move();
		//void set_location(int, int);
		//int get_row();
		//int get_col();
};
#endif