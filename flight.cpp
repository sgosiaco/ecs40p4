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
  //if(in.plane)
    //plane = new Plane(*in.plane);
  //else
    //plane = NULL;
  return *this;
}

Flight::Flight()
{
  flightNum = -1;
  strcpy(origin, "");
  strcpy(destination, "");
  //plane = NULL;
}

void Flight::addPassenger()
{
  if(!plane->addPassenger(flightNum))
    cout << "We are sorry but Flight #" << flightNum << " is full.\n";

}  // addPassenger()


Flight::~Flight()
{
  ofstream outf;
  outf.open("flights2.csv", ios::app);
  outf << flightNum << ',' << origin << ',' << destination << ',' << flush;
  plane->writePlane(outf, flightNum);
  outf.close();
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
  inf.ignore(TEN, ',');
  inf.getline(origin, MAX_CITY_LENGTH, ',');
  inf.getline(destination, MAX_CITY_LENGTH, ',');
  plane = new Plane(inf, flightNum);
}  // readFlight()
