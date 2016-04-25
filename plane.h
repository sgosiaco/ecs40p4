#ifndef PLANE_H
#define	PLANE_H
#include <fstream>

using namespace std;

class Plane
{
  static const int MAX_NAME_SIZE = 30;
  static const int FIRST_ROW = 1;
  static const char FIRST_SEAT = 'A';
  static const int TRUE = 1;
  static const int TEN = 10;
  static const int NEG = -1;
  private:
    int rows;
    int width;
    int reserved;
    int **passengers;
    int getRow() const;
    void showGrid() const;
    void showPassengers();
    void readIn(int num);
  public:
    Plane();
    Plane(Plane const &in);
    Plane(ifstream &inf, int num);
    ~Plane();
    int addPassenger(int num);
    void removePassenger(int num);
    void addFlight();
    void removeFlight(int num);
    void writePlane(ofstream &outf, int num) const;
}; // class Plane

#endif	// PLANE_H
