// Author: Sean Gosiaco
#include <cstring>
#include <iostream>

#include "passenger.h"

using namespace std;

Passenger::Passenger()
{

}//Default

Passenger::Passenger(short fn, short r, char s, char* n)
{
  flightNum = fn;
  row = r;
  seat = s;
  strcpy(name, n);
}//Full

void Passenger::copyPassengers()
{
  fstream outf("passengers2.dat", ios::binary | ios::out);
  fstream inf("passengers.dat", ios::binary | ios::in);

  if(inf.is_open() && outf.is_open())
  {
    while(!inf.eof())
    {
      Passenger temp;
      inf.read( (char *) &temp, sizeof(temp));

      if(!inf.eof())
        outf.write( (char*) &temp, sizeof(temp));
    }//while not eof
  }//if files open

  inf.close();
  outf.close();
}//copyPassengers();
