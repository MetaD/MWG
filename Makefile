PATH := /usr/um/gcc-4.8.2/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-4.8.2/lib64
LD_RUN_PATH := /usr/um/gcc-4.8.2/lib64

FLAGS = -std=c++11 -pedantic -pedantic-errors -Wall -Wextra -Wconversion -Wno-unused-parameter
DEBUG = -std=c++11 -O0 -g3 -std=c++11 -pedantic -pedantic-errors -Wall -Wextra -Wconversion -Wno-unused-parameter


CC = g++
LD = g++
CFLAGS = -c -g -std=c++11 -pedantic-errors -Wall
LFLAGS = -g

OBJS = p6_main.o Model.o View.o Controller.o
OBJS += Grid_View.o Info_View.o Map_View.o Local_View.o Health_View.o Amount_View.o Overall_View.o
OBJS += Sim_object.o Structure.o Moving_object.o Agent.o
OBJS += Farm.o Town_Hall.o
OBJS += Peasant.o Warrior.o Soldier.o Commander.o Archer.o
OBJS += Agent_factory.o Structure_factory.o
OBJS += Geometry.o Utility.o
PROG = p6exe

default: $(PROG)

$(PROG): $(OBJS)
	$(LD) $(LFLAGS) $(OBJS) -o $(PROG)

p6_main.o: p6_main.cpp Model.h Controller.h
	$(CC) $(CFLAGS) p6_main.cpp

Model.o: Model.cpp Model.h View.h Sim_object.h Structure.h Agent.h Agent_factory.h Structure_factory.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Model.cpp

View.o: View.cpp View.h Geometry.h Utility.h
	$(CC) $(CFLAGS) View.cpp

Grid_View.o: Grid_View.cpp Grid_View.h View.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Grid_View.cpp

Info_View.o: Info_View.cpp Info_View.h View.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Info_View.cpp

Overall_View.o: Overall_View.cpp Overall_View.h Grid_View.h View.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Overall_View.cpp

Map_View.o: Map_View.cpp Map_View.h Grid_View.h View.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Map_View.cpp

Local_View.o: Local_View.cpp Local_View.h Map_View.h Grid_View.h View.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Local_View.cpp

Amount_View.o: Amount_View.cpp Amount_View.h Info_View.h View.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Amount_View.cpp

Health_View.o: Health_View.cpp Health_View.h Info_View.h View.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Health_View.cpp

Controller.o: Controller.cpp Controller.h Model.h View.h Sim_object.h Structure.h Agent.h Agent_factory.h Structure_factory.h Geometry.h Utility.h Map_View.h Local_View.h Amount_View.h Health_View.h
	$(CC) $(CFLAGS) Controller.cpp

Sim_object.o: Sim_object.cpp Sim_object.h Geometry.h
	$(CC) $(CFLAGS) Sim_object.cpp

Structure.o: Structure.cpp Structure.h Model.h Sim_object.h Geometry.h
	$(CC) $(CFLAGS) Structure.cpp

Farm.o: Farm.cpp Farm.h Structure.h Sim_object.h Geometry.h
	$(CC) $(CFLAGS) Farm.cpp

Town_Hall.o: Town_Hall.cpp Town_Hall.h Structure.h Sim_object.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Town_Hall.cpp

Agent.o: Agent.cpp Agent.h Model.h Moving_object.h Sim_object.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Agent.cpp

Peasant.o: Peasant.cpp Peasant.h Agent.h Moving_object.h Sim_object.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Peasant.cpp

Warrior.o: Warrior.cpp Warrior.h Agent.h Moving_object.h Sim_object.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Warrior.cpp

Soldier.o: Soldier.cpp Soldier.h Warrior.h Agent.h Moving_object.h Sim_object.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Soldier.cpp

Commander.o: Commander.cpp Commander.h Warrior.h Agent.h Moving_object.h Sim_object.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Commander.cpp


Archer.o: Archer.cpp Archer.h Warrior.h Agent.h Moving_object.h Sim_object.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Archer.cpp

Moving_object.o: Moving_object.cpp Moving_object.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Moving_object.cpp

Agent_factory.o: Agent_factory.cpp Agent_factory.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Agent_factory.cpp

Structure_factory.o: Structure_factory.cpp Structure_factory.h Geometry.h Utility.h
	$(CC) $(CFLAGS) Structure_factory.cpp

Geometry.o: Geometry.cpp Geometry.h
	$(CC) $(CFLAGS) Geometry.cpp

Utility.o: Utility.cpp Utility.h
	$(CC) $(CFLAGS) Utility.cpp


diff: default
	./p6exe < heavy3.txt > heavy3.out
	diff heavy3_out.txt heavy3.out
	diff heavy2_out.txt heavy2.out
	./p6exe < heavy.txt > heavy.out
	./p6exe < states_in.txt > states.out
	diff states_out.txt states.out
	./p6exe < name_validity_in.txt > name.out
	diff  name_validity_out.txt name.out
	./p6exe < fight_noshow_in.txt > fight.out
	diff fight_noshow_out.txt fight.out
	./p6exe < fight_in.txt > fight2.out
	diff fight_out.txt fight2.out
	./p6exe < workviolence_noshow_in.txt > work.out
	diff workviolence_noshow_out.txt work.out
	./p6exe < workviolence_in.txt > work2.out
	diff workviolence_out.txt work2.out
	./p6exe < views_in.txt > views.out
	diff views_out.txt views.out
	./p6exe < new_features_in.txt > new_features.out
	diff new_features_out.txt new_features.out
	./p6exe < heavy2.txt > heavy2.out
	diff heavy_out.txt heavy.out


submit:
	# modify please
	submit381 6 Makefile p6_main.cpp Model.h Model.cpp View.h View.cpp Controller.h Controller.cpp Sim_object.h Sim_object.cpp Structure.h Structure.cpp Farm.h Farm.cpp Town_Hall.h Town_Hall.cpp Agent.h Agent.cpp Peasant.h Peasant.cpp warrior.h Warriors.cpp Agent_factory.h Agent_factory.cpp Structure_factory.h Structure_factory.cpp Geometry.h Geometry.cpp Moving_object.h Moving_object.cpp Utility.h Utility.cpp


leak: default
	valgrind --leak-check=yes -v ./p6exe < views_in.txt > leak.out
	valgrind --leak-check=yes -v ./p6exe < workviolence_in.txt > leak.out
	valgrind --leak-check=yes -v ./p6exe < fight_in.txt > leak.out
	valgrind --leak-check=yes -v ./p6exe < name_validity_in.txt > leak.out
	valgrind --leak-check=yes -v ./p6exe < states_in.txt > leak.out
	valgrind --leak-check=yes -v ./p6exe < new_features_in.txt > leak.out
	valgrind --leak-check=yes -v ./p6exe < heavy.txt > leak.out
	valgrind --leak-check=yes -v ./p6exe < heavy2.txt > leak.out
	valgrind --leak-check=yes -v ./p6exe < heavy3.txt > leak.out


clean:
	rm -f $(PROG) *.o rotld *.out *.dSYM *~
