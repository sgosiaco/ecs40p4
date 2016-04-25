airline.out : flight.o flights.o main.o plane.o utilities.o passenger.o
	g++ -ansi -Wall -g -o airline.out flight.o flights.o main.o plane.o utilities.o

flight.o : flight.cpp flight.h
	g++ -ansi -Wall -g -c flight.cpp

flights.o : flights.cpp flights.h
	g++ -ansi -Wall -g -c flights.cpp

main.o : main.cpp flight.h utilities.h
	g++ -ansi -Wall -g -c main.cpp

plane.o : plane.cpp plane.h utilities.h
	g++ -ansi -Wall -g -c plane.cpp

utilities.o : utilities.cpp utilities.h
	g++ -ansi -Wall -g -c utilities.cpp

passenger.o : passenger.cpp passenger.h
	g++ -ansi -Wall -g -c passenger.cpp

clean :
	rm -f airline.out flight.o flights.o main.o  plane.o  utilities.o passenger.o
