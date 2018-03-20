#ifndef _OPENSPACE_
#define _OPENSPACE_

#include "maze_location.hpp"

class OpenSpace: public MazeLocation {
	private:
		bool hasStudent;
		bool hasTA;
		bool hasInstructor;
		bool hasLadder;
		bool hasSkill;
		bool hasStart;
		
	public:
		OpenSpace();
		
		void reset();
		
		void set_has_student(bool);
		void set_has_ta(bool);
		void set_has_instructor(bool);
		void set_has_ladder(bool);
		void set_has_skill(bool);
		void set_has_start(bool b);

		bool has_student();
		bool has_ta();
		bool has_instructor();
		bool has_ladder();
		bool has_skill();
		bool has_start();
		
		bool is_occupiable();
		char get_display_character();
};
#endif