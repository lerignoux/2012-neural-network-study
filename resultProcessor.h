#ifndef DEF_RESULTPROCESS
#define DEF_RESULTPROCESS

#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cmath>

#include "layer.h"
#include "neuron.h"

using namespace std;

class Neuron;
class Layer;

class ResultProcessor
{
private:
  bool learning;
  bool batchMode;
  double learningRate;
  double expected;
  double result;
  Layer** layers;
  unsigned int nbLayers;
  
  unsigned int cycle;
  double averageError;
  
  char* mode;
  
public:
  ResultProcessor(Layer**, unsigned int, char*);
  ~ResultProcessor();
  
  void setLearning(bool);
  void setExpectedResult(double);
  void processResult(double);
  void cleanLayers();
  double getResult();
  
  void setBatchMode();
  void batchTrain();
  
  bool getLearning();
};

#endif