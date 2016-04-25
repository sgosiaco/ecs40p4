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
  Plane(ifstream &inf, int num);
  ~Plane();
  Plane();
  Plane(Plane const &in);
  int addPassenger(int num);
  void writePlane(ofstream &outf, int num) const;
  void addFlight();
  void removePassenger(int num);
  void removeFlight(int num);
}; // class Plane

#endif	// PLANE_H
