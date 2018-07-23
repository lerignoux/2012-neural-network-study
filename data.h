#ifndef DATA
#define DATA

#include <cstdlib>
#include <iostream>
#include <string>

#include "EasyBMP.h"
#include "EasyBMP_BMP.h"

using namespace std;

class Data{
  
private :
  
  BMP inputImage;
  BMP *outputImage;
  static const unsigned defaultSize=10;
  unsigned int sizeX;
  unsigned int sizeY;
  double** dataArray; /* Array containing the data : 0=blank, -0.5=black, 0.5=white */
  double** trainingSet;
  unsigned int setSize;
    
  void setSet();
  
public :
  Data();
  Data(char*);
  Data(unsigned int);
  Data(unsigned int, unsigned int);
  ~Data();
  
  /* accessors */
  
  double get(unsigned int, unsigned int);
  double* get();
  double** getSet(unsigned int);
  
  unsigned int getSizeX();
  unsigned int getSizeY();
  
  void set(unsigned int, unsigned int, double);
  
  void writeImage(char*); // save the current data to a 3 color image
  
  friend ostream& operator << (ostream& s, Data&);
  
};

#endif