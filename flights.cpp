#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

#include "flights.h"
#include "flight.h"
#include "utilities.h"

using namespace std;

bool sortByNum(const Flight &lhs, const Flight &rhs)
{
  return lhs.getFlightNumber() < rhs.getFlightNumber();
}

Flights::Flights()
{
  readFlights();
} // readFlights()

void Flights::insert()
{
}

void Flights::readFlights()
{
  int i;
  ifstream inf  ("reservations.txt");
  inf >> size;
  flights = new Flight[size];

  for(i = 0; i < size; i++)
    flights[i].readFlight(inf);

  inf.close();
  sort(flights, flights + size, sortByNum);
}
void Flights::addPassengers()
{
  int i, flightNumber;

  cout << "Flt# Origin               Destination\n";

  for(i = 0; i < size; i++)
    flights[i].printFlightInfo();

  do
  {
    cout << "\nFlight number (0 = exit): ";
    flightNumber = getNumber();

    if(flightNumber > 0)
    {

      for(i = 0; i < size; i++)
        if(flights[i].getFlightNumber() == flightNumber)
        {
          flights[i].addPassenger();
          break;
        }  // if found match of flight

      if(i == size)
      {
        cout << "We do not have a flight number " << flightNumber << ".\n";
        cout << "Please try again.\n";
      }  // if flightNumber not found
    }  // if flightNumber > 0
    else // if flightNumer <= 0
      if(flightNumber == ERROR)
        cout << "That is an invalid flight number.\nPlease try again.\n";
  }  while((flightNumber != 0 && i == size) || flightNumber == ERROR);
}  // addPassenger()

Flights::~Flights()
{
  int i;
  ofstream outf ("reservations2.txt");
  outf << size << endl;

  for(i = 0; i < size; i++)
    flights[i].writeFlight(outf);

  outf.close();

  delete [] flights;
}
