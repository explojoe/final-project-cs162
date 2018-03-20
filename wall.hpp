#ifndef _WALL_
#define _WALL_

#include "maze_location.hpp"

class Wall: public MazeLocation {
	private:
	public:
		Wall();
	
		bool is_occupiable();
		char get_display_character();
};
#endif