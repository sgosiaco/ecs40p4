#ifndef FLIGHTS_H
#define	FLIGHTS_H

#include <iostream>
#include <fstream>
#include "flight.h"
#include "utilities.h"

using namespace std;

class Flights
{
  static const int TWO = 2;
  static const int TEN = 10;
  private:
    int size;
    int capacity;
    Flight **flights;
    void dble();
    void sorttwo();
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
