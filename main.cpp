// Author: Sean Davis
// Edited by: Sean Gosiaco
#include <iostream>
#include <fstream>
#include <iomanip>

#include "flights.h"
#include "flight.h"
#include "utilities.h"

using namespace std;

#define DONE 0
#define MAX_CHOICE 1

int getChoice()
{
  int choice;
  cout << "\nECS Flight Reservation Menu\n";
  cout << "0. Exit.\n";
  cout << "1. Add Passenger.\n";

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
  Flights *flights = new Flights();

  while(getChoice() != DONE)
    flights->addPassengers();

  delete flights;

  return 0;
} // main())
