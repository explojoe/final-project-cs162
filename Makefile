CC=g++
EXE_FILE=program
HEADERS=maze_location.hpp wall.hpp open_space.hpp maze_level.hpp intrepid_student.hpp ta.hpp maze.hpp instructor.hp additional.hpp
OBJS=wall.o open_space.o maze.o maze_location.o maze_level.o maze_person.o intrepid_student.o ta.o main.o instructor.o
CXXFLAGS=-std=c++11 -g

all: $(EXE_FILE)

$(EXE_FILE): $(OBJS)
	$(CC) $^ -o $@ $(CXXFLAGS)

%.o: %.cpp $(HEADERS)
	$(CC) -c $< -o $@ $(CXXFLAGS)
	
clean: 
	rm -f $(OBJS) $(EXE_FILE)