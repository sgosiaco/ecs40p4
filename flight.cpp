// Author: Sean Davis
// Edited by: Sean Gosiaco
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "flight.h"

using namespace std;

Flight::Flight()
{
  flightNum = NEG;
  strcpy(origin, "");
  strcpy(destination, "");
  plane = NULL;
}//Flight()

void Flight::readFlight(ifstream &inf)
{
  inf >> flightNum;
  inf.ignore(TEN, ',');
  inf.getline(origin, MAX_CITY_LENGTH, ',');
  inf.getline(destination, MAX_CITY_LENGTH, ',');
  plane = new Plane(inf, flightNum);
}  // readFlight()

void Flight::printFlightInfo() const
{
  cout << left << setw(4) << flightNum << ' ' << setw(20)
    << origin << ' '  << destination << endl;
}  // printFlightInfo()

void Flight::addPassenger() const
{
  if(!plane->addPassenger(flightNum))
    cout << "We are sorry but Flight #" << flightNum << " is full.\n";

}  // addPassenger()

void Flight::removePassenger() const
{
  plane->removePassenger(flightNum);
}//removePassenger()

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
}//addFlight()

void Flight::removeFlight()
{
  plane->removeFlight(flightNum);
  flightNum = NEG;
}//removeFlight

int Flight::getFlightNumber() const
{
  return flightNum;
}  // getFlightNumber()

Flight::~Flight()
{
  if(flightNum != NEG)
  {
    ofstream outf;
    outf.open("flights2.csv", ios::app);
    outf << flightNum << ',' << origin << ',' << destination << ',' << flush;
    plane->writePlane(outf, flightNum);
    outf.close();
  }//if not remove flight

  delete plane;
}  // ~Flight()
