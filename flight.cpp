// Author: Sean Davis

#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "flight.h"

using namespace std;
#define TEN 10

Flight::Flight()
{
  flightNum = -1;
  strcpy(origin, "");
  strcpy(destination, "");
  plane = NULL;
}

void Flight::addPassenger()
{
  if(!plane->addPassenger(flightNum))
    cout << "We are sorry but Flight #" << flightNum << " is full.\n";

}  // addPassenger()

void Flight::removePassenger()
{
  plane->removePassenger(flightNum);
}

void Flight::removeFlight()
{
  plane->removeFlight(flightNum);
  flightNum = -1;
}

void Flight::addFlight()
{
  cout << "\nFlight number to add: ";
  cin >> flightNum;
  cin.ignore(TEN, '\n');
  cout << "Origin: ";
  cin.getline(origin, MAX_CITY_LENGTH);
  cout << "Destination: ";
  cin.getline(destination, MAX_CITY_LENGTH);
  plane = new Plane();
  plane->addFlight();
}

Flight::~Flight()
{
  if(flightNum != -1)
  {
    ofstream outf;
    outf.open("flights2.csv", ios::app);
    outf << flightNum << ',' << origin << ',' << destination << ',' << flush;
    plane->writePlane(outf, flightNum);
    outf.close();
  }
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


void Flight::readFlight(ifstream &inf)
{
  inf >> flightNum;
  inf.ignore(TEN, ',');
  inf.getline(origin, MAX_CITY_LENGTH, ',');
  inf.getline(destination, MAX_CITY_LENGTH, ',');
  plane = new Plane(inf, flightNum);
}  // readFlight()
