#ifndef _ADDITIONAL_
#define _ADDITIONAL_
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

const string skillList[] = {
	"vectors",
	"dynamic allocation",
	"arrays",
	"file I/O",
	"header guards",
	"random numbers",
	"loops",
	"code style",
	"the GNU project debugger (gdb)",
	"pointers",
	"references",
	"polymorphism",
	"abstract classes",
	"virtual functions",
	"makefiles",
	"using stackoverflow because it's easy",
	"structs",
	"inheritance",
	"unnecessary object orientation"
	};
	
int totalUniqueSkills = 19;

string printRandomSkillName(){
	int num = rand()%totalUniqueSkills;
	stringstream ss;
	ss << "You have discovered knowledge of " << skillList[num] << ".";
	return ss.str();
}
#endif