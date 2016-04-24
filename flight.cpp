// Author: Sean Davis

#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "flight.h"

using namespace std;
#define TEN 10

Flight& Flight::operator=(const Flight &in)
{
  if(&in == this)
    return *this;
  flightNum = in.flightNum;

  if(in.origin)
    strcpy(origin, in.origin);
  else
    strcpy(origin, "");

  if(in.destination)
    strcpy(destination, in.destination);
  else
    strcpy(destination, "");

  plane = new Plane(*in.plane);
  return *this;
}

Flight::Flight()
{
  flightNum = -1;
  strcpy(origin, "");
  strcpy(destination, "");
  plane = NULL;
}

void Flight::addPassenger()
{
  if(!plane->addPassenger())
    cout << "We are sorry but Flight #" << flightNum << " is full.\n";

}  // addPassenger()


Flight::~Flight()
{
  delete plane;
}  // freeFlight()


int Flight::getFlightNumber() const
{
  return flightNum;
}  // getFlightNumber()


void Flight::printFlightInfo() const
{
  cout << left << setw(4) << flightNum << ' ' << setw(20)
    << origin << ' '  << destination << endl;
}  // printFlightInfo()


void Flight::readFlight( ifstream &inf)
{
  inf >> flightNum;
  inf.ignore(TEN, '\n');
  inf.getline(origin, MAX_CITY_LENGTH);
  inf.getline(destination, MAX_CITY_LENGTH);
  plane = new Plane(inf);
}  // readFlight()


void Flight::writeFlight( ofstream &outf) const
{
  outf << flightNum << endl << origin << endl << destination << endl;
  plane->writePlane(outf);
}  // readFlight()
