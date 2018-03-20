#ifndef _TA_
#define _TA_

#include "maze_person.hpp"

class TA: public MazePerson {
	private:
		bool isAppeased;
	public:
		TA();
	
		char get_move();
		
		void set_is_appeased(bool);
		bool is_appeased();
		
		//void set_location(int, int);
		//int get_row();
		//int get_col();
};
#endif