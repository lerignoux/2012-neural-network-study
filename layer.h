#ifndef LAYER
#define LAYER

#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "neuron.h"

using namespace std;

class Neuron;
class StartNeuronLink;
class DoubleNeuronLink;
class EndNeuronLink;
class ResultProcessor;

class Layer
{
private:
  static const unsigned int defaultLayerSize=5;
  Neuron** neurons;
  unsigned int nbNeurons;
  
public:
    Layer(unsigned int nbNeurones);
    ~Layer();
    
    void linkSubLayer(Layer*);
    void addParentNeuron(Neuron*);
    
    StartNeuronLink** setStartLayer();
    EndNeuronLink* setEndLayer(ResultProcessor*);
    
    unsigned int getNbNeuron();
    Neuron* getNeuron(unsigned int);
    
    void processLayer(void);
    void clean();  
    
  friend ostream& operator << (ostream& s, Layer&);
};

#endif