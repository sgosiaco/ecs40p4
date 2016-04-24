#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>

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
  capacity = 2;
  flights = new Flight[capacity];
  readFlights();
} // readFlights()

void Flights::insert(Flight *in)
{
  if(capacity == size)
  {
    capacity *= 2;
    Flight *f = new Flight[capacity/2];
    f = flights;
    flights = new Flight[capacity];
    copy(f, f + capacity/2, flights);
    delete [] f;
  }
  flights[capacity - 1] = *in;
  size++;
  sort(flights, flights + capacity, sortByNum);
}

void Flights::readFlights()
{
  int tSize;
  ifstream inf  ("reservations.txt");
  inf >> tSize;

  for(int i = 0; i < tSize; i++)
  {
    Flight *f = new Flight();
    f->readFlight(inf);
    insert(f);
    delete f;
  }

  inf.close();
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

  delete [] &flights;
}
