#ifndef FLIGHTS_H
#define	FLIGHTS_H

#include <iostream>
#include <fstream>
#include <vector>
#include "flight.h"

using namespace std;

class Flights
{
private:
  int size;
  int capacity;
  vector<Flight> flights;

public:
  Flights();
  ~Flights();
  void insert(Flight *in);
  void readFlights();
  void addPassengers();
} ;




#endif	// FLIGHTS_H
