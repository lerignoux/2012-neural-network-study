#ifndef NEURON
#define NEURON

#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream> 
#include "neuronLink.h"

using namespace std;

class NeuronLink;
class DoubleNeuronLink;
class StartNeuronLink;
class EndNeuronLink;

class Neuron{
  
private :
  NeuronLink **parentsLinks;
  unsigned int nbChildren;
  NeuronLink **childrenLinks;
  unsigned int nbParents;
  
  double bias;
  double b;
  double a;
  double gradient;
  double localField;

  
  
  stringstream name;

  
public :
  Neuron();
  ~Neuron();

    
  void addLink(NeuronLink* link);
  double addInput(double input);
  
  void processInputs();
  void transmitSignal(double);
  
  void addParentLink(NeuronLink*);
  void addChildLink(NeuronLink*);
  
  void setParentLink(NeuronLink*);
  void setChildLink(NeuronLink*);
  
  unsigned int getNbChildren();
  NeuronLink* getChild(unsigned int);
  
  unsigned int getNbParents();
  NeuronLink* getParent(unsigned int);

  void changeParentsWeight(double);
  
  double getLocalField();
  double getGradient();
  void setGradient();
  void setGradient(double);
  
  double activationFunction(double);
  double dActivationFunction(double);
  
  void clean();
  string getName();
  friend ostream& operator << (ostream& s, Neuron&);
};


#endif