// Author: Sean Gosiaco
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

#include "flights.h"

using namespace std;

Flights::Flights()
{
  size = 0;
  capacity = TWO;
  flights = new Flight*[capacity];

  for(int i = 0; i < capacity; i++)
    flights[i] = new Flight();
} // readFlights()

void Flights::insert(Flight * const in)
{
  if(capacity == size)
  {
    capacity *= TWO;
    dble();
  }//if full

  for(int i = 0; i < capacity; i++)
  {
    if(flights[i]->getFlightNumber() == NEG)
    {
      Flight *temp = flights[i];
      flights[i] = in;
      delete temp;
      size++;
      break;
    }//if null
  }//for

  sorttwo();
}//insert()

void Flights::sorttwo()
{
  for (int i = 0; i < capacity; i++)
  {
    int j = i;

    while (j > 0 && flights[j]->getFlightNumber()
           < flights[j - 1]->getFlightNumber()
           && (flights[j]->getFlightNumber() != NEG
           && flights[j - 1]->getFlightNumber() != NEG))
    {
      Flight *temp = flights[j];
      flights[j] = flights[j - 1];
      flights[j - 1] = temp;
      j--;
    }//while
  }//for
}//sorttwo

void Flights::dble()
{
  int old = capacity / TWO;
  Flight **f = new Flight*[old];

  for(int i = 0; i < old; i++)
    f[i] = flights[i];

  delete [] flights;
  flights = new Flight*[capacity];

  for(int k = 0; k < old; k++)
    flights[k] = f[k];

  for(int l = old; l < capacity; l++)
    flights[l] = new Flight();

  delete [] f;
}//dble()

void Flights::readFlights()
{
  int tSize;
  ifstream inf("flights.csv");
  inf >> tSize;

  for(int i = 0; i < tSize; i++)
  {
    Flight *f = new Flight();
    f->readFlight(inf);
    insert(f);
  }//for

  inf.close();
}//readFlights()

void Flights::addPassengers()
{
  int i, flightNumber;

  cout << "Flt# Origin               Destination\n";

  for(i = 0; i < size; i++)
    flights[i]->printFlightInfo();

  do
  {
    cout << "\nFlight number (0 = exit): ";
    flightNumber = getNumber();

    if(flightNumber > 0)
    {

      for(i = 0; i < size; i++)
        if(flights[i]->getFlightNumber() == flightNumber)
        {
          flights[i]->addPassenger();
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

void Flights::addFlights()
{
  cout << "Existing Flights:\n\n";
  cout << "Flt# Origin               Destination\n";

  for(int i = 0; i < size; i++)
    flights[i]->printFlightInfo();

  Flight *f = new Flight();
  f->addFlight();
  insert(f);
}//addFlights()

void Flights::removePassengers()
{
  int num;
  cout << "Existing Flights:\n\n";
  cout << "Flt# Origin               Destination\n";

  for(int i = 0; i < size; i++)
    flights[i]->printFlightInfo();

  cout << "\nFlight number of passenger remove: ";
  cin >> num;
  cin.ignore(TEN, '\n');

  for(int i = 0; i < size; i++)
  {
    if(flights[i]->getFlightNumber() == num)
    {
      flights[i]->removePassenger();
      break;
    }//if match
  }//for
}//removePassengers()

void Flights::removeFlights()
{
  int num;
  cout << "Existing Flights:\n\n";
  cout << "Flt# Origin               Destination\n";

  for(int i = 0; i < size; i++)
    flights[i]->printFlightInfo();

  cout << "\nFlight number to remove: ";
  cin >> num;
  cin.ignore(TEN, '\n');

  for(int i = 0; i < size; i++)
  {
    if(flights[i]->getFlightNumber() == num)
    {
      flights[i]->removeFlight();
      delete flights[i];
      size--;
      flights[i] = new Flight();
      sortthree();
      break;
    }//if match
  }//for
}//removeFlights()

void Flights::sortthree()
{
  for(int i = 0; i < size; i++)
  {
    if(flights[i]->getFlightNumber() == NEG)
    {
      Flight *temp = flights[i];
      flights[i] = flights[size];
      flights[size] = temp;
      sorttwo();
      break;
    }//if
  }//for
}//sortthree

Flights::~Flights()
{
  fstream out("passengers3.dat", ios::binary | ios::out | ios::trunc);
  out.close();
  ofstream outf("flights2.csv");
  outf << size << endl;

  for(int i = 0; i < capacity; i++)
    delete flights[i];

  outf.close();

  delete[] flights;
}//~Flights()
