#ifndef FLIGHTS_H
#define	FLIGHTS_H

#include <iostream>
#include <fstream>
#include "flight.h"

using namespace std;

class Flights
{
private:
  int size;
  Flight *flights;

public:
  Flights();
  ~Flights();
  void insert();
  void readFlights();
  void addPassengers();
} ;




#endif	// FLIGHTS_H
