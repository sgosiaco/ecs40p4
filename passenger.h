#ifndef PASSENGER_H
#define	PASSENGER_H
#include <fstream>

#include "plane.h"

using namespace std;

class Passenger
{
  static const int THIRTY = 30;
  friend class Plane;
  private:
    short flightNum;
    short row;
    char seat;
    char name[THIRTY];
  public:
    Passenger();
    Passenger(short fn, short r, char s, char* n);
    static void copyPassengers();
}; // class Passenger

#endif	// PASSENGER_H
