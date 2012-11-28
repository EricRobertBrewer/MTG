game.x : main.o Deck.o Card.o Scanner.o getMenuInput.o
	g++ -g main.cpp Deck.o Card.o Scanner.o getMenuInput.o -lcurses -ltermcap -o game.x

main.o : main.cpp Deck.hpp Scanner.hpp getMenuInput.hpp
	g++ -c main.cpp

Deck.o : Deck.cpp Deck.hpp Card.hpp
	g++ -c -lcurses -ltermcap Deck.cpp

Card.o : Card.cpp Card.hpp
	g++ -c -lcurses -ltermcap Card.cpp

Scanner.o : Scanner.cpp Scanner.hpp Deck.hpp
	g++ -c Scanner.cpp

getMenuInput.o : getMenuInput.cpp getMenuInput.hpp
	g++ -c getMenuInput.cpp

clean :
	rm *~ *# *.o *.x
