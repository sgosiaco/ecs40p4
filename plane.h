#ifndef PLANE_H
#define	PLANE_H
#include <fstream>

using namespace std;
#define MAX_NAME_SIZE 30
#define FIRST_ROW 1
#define FIRST_SEAT 'A'

class Plane
{
  int rows;
  int width;
  int reserved;
  int **passengers;
  int getRow() const;
  void showGrid() const;
public:
  Plane();
  Plane(Plane const &in);
  Plane(ifstream &inf, int num);
  ~Plane();
  void readIn(int num);
  int addPassenger(int num);
  void removePassenger(int num);
  void showPassengers();
  void addFlight();
  void removeFlight(int num);
  void writePlane(ofstream &outf, int num) const;
}; // class Plane

#endif	// PLANE_H
