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

static const int DONE = 0;
static const int MAX_CHOICE = 4;

enum
{
  EXIT,
  ADD_PASSENGER,
  REMOVE_PASSENGER,
  ADD_FLIGHT,
  REMOVE_FLIGHT
};  //enum

int getChoice()
{
  int choice;
  cout << "\nECS Flight Reservation Menu\n";
  cout << "0. Exit.\n";
  cout << "1. Add Passenger.\n2. Remove Passenger.\n";
  cout << "3. Add Flight.\n4. Remove Flight.\n";

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

  while((in = getChoice()) != EXIT)
  {
    switch(in)
    {
      case ADD_PASSENGER:
        flight->addPassengers();
        break;
      case REMOVE_PASSENGER:
        flight->removePassengers();
        break;
      case ADD_FLIGHT:
        flight->addFlights();
        break;
      case REMOVE_FLIGHT:
        flight->removeFlights();
        break;
    }//switch
  }//while

  delete flight;
  //Passenger::read();
  return 0;
} // main())
