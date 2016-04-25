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
  Flight **flights;
  void dble();
public:
  Flights();
  ~Flights();
  void insert(Flight *in);
  void readFlights();
  void addPassengers();
  void addFlights();
  void removePassengers();
  void removeFlights();
} ;




#endif	// FLIGHTS_H
