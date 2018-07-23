#include "data.h"

/*********************************************************************************
 * 	Initialisations 
 * ******************************************************************************/

Data::Data()
{
  Data(defaultSize,defaultSize);
}

Data::Data(char* filename)
{
  inputImage.ReadFromFile(filename);
  sizeX=(unsigned int)inputImage.TellWidth();
  sizeY=(unsigned int)inputImage.TellHeight();
  
  cout << "open file : x = " << inputImage.TellWidth() << endl;
  
  dataArray = new double *[sizeX];
  
  for(unsigned int i=0;i<sizeX;i++)
  {
    dataArray[i]=new double[sizeY];
    for(unsigned int j=0;j<sizeY;j++)
    {
      int color = inputImage(i,j)->Red;
      if (color > 192) dataArray[i][j]=-1.0;
      else {
	if (color < 64 ) dataArray[i][j]=1.0;
	else dataArray[i][j]=0.0;
      }
    };
  };
  setSet(); 
}

Data::Data(unsigned int n)
{
  Data(n,n);
}

Data::Data(unsigned int n, unsigned int m)
{
  sizeX = n;
  sizeY = m;
  dataArray = new double *[sizeX];
  for(unsigned int i=0;i<sizeX;i++)
  {
    dataArray[i]=new double[sizeY];
  };
}

Data::~Data()
{
  delete dataArray;
}

/*********************************************************************************
 * 	Get
 * ******************************************************************************/

double Data::get(unsigned int x, unsigned int y)
{
  return dataArray[x][y];
}


unsigned int Data::getSizeX()
{
  return sizeX;
}

unsigned int Data::getSizeY()
{
  return sizeY;
}

void Data::setSet()
{
  setSize = 0;
  
  for (unsigned int i=0;i<sizeX; i++)
  {
    for (unsigned int j=0;j<sizeY;j++)
    {
      if (dataArray[i][j]!=0) setSize++;
    };
  };
  
  trainingSet = new double*[setSize];
  unsigned int current=0;
  
  for (unsigned int i=0;i<sizeX; i++)
  {
    for (unsigned int j=0;j<sizeY;j++)
    {
      trainingSet[current]= new double[3];
      if (dataArray[i][j]!=0.0)
      {
	trainingSet[current][0]=i;
	trainingSet[current][1]=j;
	trainingSet[current][2]=dataArray[i][j];
      }
      current++;
    };
  };
}

double** Data::getSet(unsigned int size)
{
  double **sample = new double*[size];
  for (unsigned int i=0; i<size;i++)
  {
    sample[i]=get();
  };
  return sample;
}

double* Data::get()
{
  return trainingSet[rand()%setSize];
}

/*********************************************************************************
 * 	Set
 * ******************************************************************************/


void Data::set(unsigned int i, unsigned int j, double r)
{
  dataArray[i][j]=r;
}

/*********************************************************************************
 * 	Misc
 * ******************************************************************************/

void Data::writeImage(char* fileName)
{
  RGBApixel pixel;
  pixel.Alpha=0;
  outputImage = new BMP();
  outputImage->SetSize( (int) sizeX, (int) sizeY);
  for (unsigned int i=0; i<sizeX; i++)
  {
    for (unsigned int j=0; j<sizeY;j++)
    {
      if (dataArray[i][j]>0.0)
      {
	pixel.Red = 250;
	pixel.Blue = 250;
	pixel.Green = 250;
      }
      else
      {
      pixel.Red = 0;
      pixel.Blue = 0;
      pixel.Green = 0;
      }
      outputImage->SetPixel( (int) i, (int) j, pixel);
    };
  };
  outputImage->WriteToFile(fileName);
}

/*********************************************************************************
 * 	Redefinition of cout
 * ******************************************************************************/

ostream& operator << (ostream& s, Data& d)  //display
{
  for(unsigned int i=0;i<d.sizeX;i++)
  {
    for(unsigned int j=0;j<d.sizeY;j++)
    {
    s << d.dataArray[i][j]<< " " ;
    }
    s << endl;
  }

return s;
}  
