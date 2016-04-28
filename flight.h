#ifndef FLIGHT_H
#define	FLIGHT_H

#include <iostream>
#include <fstream>
#include "plane.h"

using namespace std;

class Flight
{
  static const int MAX_CITY_LENGTH = 20;
  static const int TEN = 10;
  static const int NEG = -1;
  private:
    int flightNum;
    char origin[MAX_CITY_LENGTH];
    char destination[MAX_CITY_LENGTH];
    Plane *plane;
  public:
    void addPassenger() const;
    ~Flight();
    Flight();
    int getFlightNumber() const;
    void printFlightInfo() const;
    void readFlight(ifstream &inf);
    void addFlight();
    void removePassenger() const;
    void removeFlight();
} ;

#endif	// FLIGHT_H
