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

#define TRUE 1
#define TEN 10

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
      passengers[row][seatNum] = -1;
  } // for each row

  for(int row = 0; row < rows; row++)
  {
    for(int seatNum = 0; seatNum < width; seatNum++)
    {
      if(in.passengers[row][seatNum] != -1)
        passengers[row][seatNum] = in.passengers[row][seatNum];
    }
  }  // for row
}

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
      passengers[row][seatNum] = -1;
  } // for each row

  fstream in("passengers2.dat", ios::binary | ios::in);
  if(in.is_open())
  {
    while(!in.eof())
    {
      Passenger pass;
      in.read( (char *) &pass, sizeof(pass));
      if(pass.flightNum == num)
      {
        passengers[pass.row - 1][pass.seat - 'A'] = in.tellg();
        reserved++;
      }
    }
  }
  in.close();
}  // Plane()


Plane::~Plane()
{
  for(int row = 0; row < rows; row++)
  {
    delete [] passengers[row];
  }  // for row

  delete [] passengers;
}  // ~Plane()



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

    if(passengers[pass.row - FIRST_ROW][pass.seat - 'A'] == -1)
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
      if(passengers[row][seatNum] != -1)
        putchar('X');
      else  // empty seat
        putchar('-');

    putchar('\n');
  }  // for each row

  printf("\nX = reserved.\n");
}  // showGrid()


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
      if(passengers[row][seatNum] != -1)
      {
        in.seekg(passengers[row][seatNum]);
        in.read( (char *) &pass, sizeof(pass));
        if(pass.flightNum == num)
          out.write( (char *) &pass, sizeof(pass));
      }
    }
  }
  in.close();
  out.close();
}  // readPlane()
