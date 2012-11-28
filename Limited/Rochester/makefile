rochester.x : main.cpp BoosterBox.o Pack.o
	g++ -g main.cpp BoosterBox.o Pack.o -lcurses -ltermcap -o rochester.x

BoosterBox.o : ../BoosterBox.cpp ../BoosterBox.hpp ../Pack.hpp
	g++ -c ../BoosterBox.cpp

Pack.o : ../Pack.cpp ../Pack.hpp
	g++ -c ../Pack.cpp

clean :
	rm *.o *.x *~

