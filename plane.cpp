// Author: Sean Davis

#include <string.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "plane.h"
#include "utilities.h"
#include "passenger.h"

using namespace std;

Plane::Plane()
{

}//Default

Plane::Plane(Plane const &in)
{
  rows = in.rows;
  width = in.width;
  reserved = in.reserved;
  passengers = new int* [rows];

  for(int row = 0; row < rows; row++)
  {
    passengers[row] = new int[width];

    for(int seatNum = 0; seatNum < width; seatNum++)
      passengers[row][seatNum] = NEG;
  } // for each row

  for(int row = 0; row < rows; row++)
  {
    for(int seatNum = 0; seatNum < width; seatNum++)
    {
      if(in.passengers[row][seatNum] != NEG)
        passengers[row][seatNum] = in.passengers[row][seatNum];
    }//for
  }  // for row
}//Copy const

Plane::Plane(ifstream &inf, int num)
{
  inf >> rows;
  inf.ignore(TEN, ',');
  inf >> width;
  inf.ignore(TEN, '\n');
  reserved = 0;
  passengers = new int*[rows];

  for(int row = 0; row < rows; row++)
  {
    passengers[row] = new int[width];

    for(int seatNum = 0; seatNum < width; seatNum++)
      passengers[row][seatNum] = NEG;
  } // for each row

  readIn(num);
}  // Plane()

void Plane::readIn(int num)
{
  fstream in("passengers2.dat", ios::binary | ios::in);

  if(in.is_open())
  {
    while(!in.eof())
    {
      Passenger pass;
      in.read( (char *) &pass, sizeof(pass));

      if(pass.flightNum == num)
      {
        if(!in.eof())
        {
          passengers[pass.row - 1][pass.seat - 'A'] = in.tellg();
          reserved++;
        }//if not eof
      }//if match
    }//while not eof
  }//if file open

  in.close();
}//readIn()

Plane::~Plane()
{
  for(int row = 0; row < rows; row++)
  {
    delete [] passengers[row];
  }  // for row

  delete [] passengers;
}  // ~Plane()

void Plane::addFlight()
{
  cout << "Rows: ";
  cin >> rows;
  cin.ignore(TEN, '\n');
  cout << "Width: ";
  cin >> width;
  cin.ignore(TEN, '\n');
  reserved = 0;
  passengers = new int* [rows];

  for(int row = 0; row < rows; row++)
  {
    passengers[row] = new int[width];

    for(int seatNum = 0; seatNum < width; seatNum++)
      passengers[row][seatNum] = NEG;
  } // for each row
}//addFlight

int Plane::addPassenger(int num)
{
  Passenger pass;
  pass.flightNum = num;

  if(reserved == rows * width)
    return 0;  // false

  cout << "Please enter the name of the passenger: ";
  cin.getline(pass.name, MAX_NAME_SIZE);
  showGrid();

  while(TRUE)
  {
    pass.row = getRow();
    cout << "Please enter the seat letter you wish to reserve: ";
    pass.seat = cin.get();

    while(cin.get() != '\n');

    if(passengers[pass.row - FIRST_ROW][pass.seat - 'A'] == NEG)
      break;

    printf("That seat is already occupied.\nPlease try again.\n");
  } // while occupied seat

  fstream out("passengers2.dat", ios::binary | ios::out | ios::app);
  out.write( (char *) &pass, sizeof(pass));
  passengers[pass.row - FIRST_ROW][pass.seat - 'A'] = out.tellg();
  reserved++;
  out.close();
  return 1;
}  // addPassenger()


int Plane::getRow() const
{
  int row;

  do
  {
    cout << "\nPlease enter the row of the seat you wish to reserve: ";
    row = getNumber();

    if(row == ERROR)
      cout << "That is an invalid row number.\nPlease try again.\n";
    else  // valid row number
      if(row < 1 || row > rows)
        cout << "There is no row #" << row
          << " on this flight.\nPlease try again.\n";

  }  while(row < 1 || row > rows);

  return row;
} // getRow()


void Plane::showGrid() const
{
  int row, seatNum = 0;

  printf("ROW# ");

  for(seatNum = 0; seatNum < width; seatNum++)
    cout << char(seatNum + FIRST_SEAT);

  putchar('\n');

  for(row = 0; row < rows; row++)
  {
    printf("%2d   ", row + 1);

    for(seatNum = 0; seatNum < width; seatNum++)
      if(passengers[row][seatNum] != NEG)
        putchar('X');
      else  // empty seat
        putchar('-');

    putchar('\n');
  }  // for each row

  printf("\nX = reserved.\n");
}  // showGrid()

void Plane::removePassenger(int num)
{
  cout << "Passengers on Flight #" << num << endl;
  fstream in("passengers2.dat", ios::binary | ios::in | ios::out);
  Passenger pass;
  char n[MAX_NAME_SIZE];
  showPassengers();
  cout << "\nName of passenger to remove: ";
  cin.getline(n, MAX_NAME_SIZE);

  for(int row = 0; row < rows; row++)
  {
    for(int seatNum = 0; seatNum < width; seatNum++)
    {
      if(passengers[row][seatNum] != NEG)
      {
        in.seekg(passengers[row][seatNum] - sizeof(pass));
        in.read( (char *) &pass, sizeof(pass));

        if(strcmp(pass.name, n) == 0)
        {
          pass.flightNum = NEG;
          in.seekp(passengers[row][seatNum] - sizeof(pass));
          in.write( (char *) &pass, sizeof(pass));
          passengers[row][seatNum] = NEG;
        }//if match
      }//if not null
    }//for
  }//for

  in.close();
}//removePassenger()

void Plane::showPassengers()
{
  Passenger pass;
  fstream in("passengers2.dat", ios::binary | ios::in );

  for(int row = 0; row < rows; row++)
  {
    for(int seatNum = 0; seatNum < width; seatNum++)
    {
      if(passengers[row][seatNum] != NEG)
      {
        in.seekg(passengers[row][seatNum] - sizeof(pass));
        in.read( (char *) &pass, sizeof(pass));
        cout << pass.name << endl;
      }//if
    }//for
  }//for

  in.close();
}//showPassengers()

void Plane::removeFlight(int num)
{
  fstream in("passengers2.dat", ios::binary | ios::in | ios::out);
  Passenger pass;

  for(int row = 0; row < rows; row++)
  {
    for(int seatNum = 0; seatNum < width; seatNum++)
    {
      if(passengers[row][seatNum] != NEG)
      {
        in.seekg(passengers[row][seatNum] - sizeof(pass));
        in.read( (char *) &pass, sizeof(pass));

        if(pass.flightNum == num)
        {
          pass.flightNum = NEG;
          in.seekp(passengers[row][seatNum] - sizeof(pass));
          in.write( (char *) &pass, sizeof(pass));
          passengers[row][seatNum] = NEG;
        }//if match
      }//if not null
    }//for
  }//for

  in.close();
}//removeFlight()

void Plane::writePlane(ofstream &outf, int num) const
{
  outf << rows << ',' << width << endl;
  fstream out("passengers3.dat", ios::binary | ios::out | ios::app);
  fstream in("passengers2.dat", ios::binary | ios::in);
  Passenger pass;

  for(int row = 0; row < rows; row++)
  {
    for(int seatNum = 0; seatNum < width; seatNum++)
    {
      if(passengers[row][seatNum] != NEG)
      {
        in.seekg(passengers[row][seatNum] - sizeof(pass));
        in.read( (char *) &pass, sizeof(pass));

        if(pass.flightNum == num)
          out.write( (char *) &pass, sizeof(pass));
      }//if not null
    }//for
  }//for

  in.close();
  out.close();
} //writePlane
