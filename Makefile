FLAGS = -std=c++11 -O3 -Wall

FILES = Sim_object.cpp Structure.cpp Geometry.cpp Farm.cpp Town_Hall.cpp Agent.cpp Moving_object.cpp Peasant.cpp Warriors.cpp Archer.cpp Soldier.cpp Commander.cpp Agent_factory.cpp Structure_factory.cpp Model.cpp View.cpp Views.cpp Controller.cpp main.cpp

all: Sim_object.h Structure.h Geometry.h Farm.h Town_Hall.h Agent.h Moving_object.h Peasant.h Warriors.h Archer.h Soldier.h Commander.h Agent_factory.h Structure_factory.h Model.h View.h Views.h Controller.h $(FILES)
	g++ $(FLAGS) $(FILES) -o test

run:	all
	./test

clean:
	rm -rf *.o out *.dSYM *~ test *.exe
