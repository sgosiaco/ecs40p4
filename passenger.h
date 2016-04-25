#ifndef PASSENGER_H
#define	PASSENGER_H
#include <fstream>
#include "plane.h"
using namespace std;
#define THIRTY 30

class Passenger
{
  friend class Plane;
  private:
    short flightNum;
    short row;
    char seat;
    char name[THIRTY];
  public:
    static void copyPassengers();
}; // class Passenger

#endif	// PASSENGER_H
