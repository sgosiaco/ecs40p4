#ifndef FLIGHT_H
#define	FLIGHT_H

#include <iostream>
#include <fstream>
#include "plane.h"

using namespace std;
#define MAX_CITY_LENGTH 20

class Flight
{
  int flightNum;
  char origin[MAX_CITY_LENGTH];
  char destination[MAX_CITY_LENGTH];
  Plane *plane;
public:
  void addPassenger();
  ~Flight();
  Flight();
  int getFlightNumber() const;
  void printFlightInfo() const;
  void readFlight(ifstream &inf);
  Flight& operator=(const Flight &in);
} ;




#endif	// FLIGHT_H
