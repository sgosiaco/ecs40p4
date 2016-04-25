#include "passenger.h"

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
    }
  }
  inf.close();
  outf.close();
}
