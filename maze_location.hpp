#ifndef _MAZELOCATION_
#define _MAZELOCATION_

class MazeLocation {
	private:
	public:
		virtual bool is_occupiable() = 0;
		virtual char get_display_character() = 0;
		
		virtual void reset();
		
		virtual void set_has_student(bool);
		virtual void set_has_ta(bool);
		virtual void set_has_instructor(bool);
		virtual void set_has_ladder(bool);
		virtual void set_has_skill(bool);
		virtual void set_has_start(bool);

		virtual bool has_student();
		virtual bool has_ta();
		virtual bool has_instructor();
		virtual bool has_ladder();
		virtual bool has_skill();
		virtual bool has_start();
};
#endif