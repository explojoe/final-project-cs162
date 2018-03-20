#ifndef _MAZEPERSON_
#define _MAZEPERSON_

class MazePerson {
	private:
		int row;
		int col;
	public:
		//Explorer();
	
		virtual char get_move() = 0;
		void set_location(int, int);
		int get_row();
		int get_col();
};
#endif