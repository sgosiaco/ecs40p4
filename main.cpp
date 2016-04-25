// Author: Sean Davis
// Edited by: Sean Gosiaco
#include <iostream>
#include <fstream>
#include <iomanip>

#include "flights.h"
#include "flight.h"
#include "utilities.h"
#include "passenger.h"

using namespace std;

#define DONE 0
#define MAX_CHOICE 4

int getChoice()
{
  int choice;
  cout << "\nECS Flight Reservation Menu\n";
  cout << "0. Exit.\n";
  cout << "1. Add Passenger.\n2. Remove Passenger.\n";
  cout << "3. Add Flight.\n4. Remove Flight\n";

  do
  {
    cout << "\nPlease enter your choice: ";
    choice = getNumber();

    if(choice == ERROR)
    {
      cout << "Your choice is invalid.\n";
      cout << "Please try again.\n";
    }  // if invalid format
    else // choice is a valid number
      if(choice < DONE || choice > MAX_CHOICE)
      {
        cout << choice << " is not an available choice.\n";
        cout << "Please try again.\n";
      }  // if choice out of range.
  } while(choice < DONE || choice > MAX_CHOICE  || choice == ERROR);

  if(choice == DONE)
    cout << "Goodbye.\n";

  return choice;
} // getChoice()

int main(int argc, char** argv)
{
  int in = 0;
  Passenger::copyPassengers();
  Flights *flight = new Flights();
  flight->readFlights();

  while((in = getChoice()) != DONE)
  {
    switch(in)
    {
      case 1:
        flight->addPassengers();
        break;
      case 2:
        flight->removePassengers();
        break;
      case 3:
        flight->addFlights();
        break;
    }
  }

  delete flight;
  Passenger::read();
  return 0;
} // main())
