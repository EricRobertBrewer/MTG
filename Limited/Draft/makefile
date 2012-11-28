draft.x : main.cpp BoosterBox.o Pack.o
	g++ -g main.cpp BoosterBox.o Pack.o -lcurses -ltermcap -o draft.x

BoosterBox.o : ../BoosterBox.cpp ../BoosterBox.hpp ../Pack.hpp
	g++ -c ../BoosterBox.cpp

Pack.o : ../Pack.cpp ../Pack.hpp
	g++ -lcurses -ltermcap -c ../Pack.cpp

clean :
	rm *.o *.x *~

