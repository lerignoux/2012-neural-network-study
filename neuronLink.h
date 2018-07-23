#ifndef NLINK
#define NLINK

#include <cstdlib>
#include <iostream>
#include "neuron.h"
#include "resultProcessor.h"

using namespace std;

class Neuron;
class ResultProcessor;




class NeuronLink{

protected:
  double lastSignal;
  double weight;
  double alpha;
  double previousWeight;
  Neuron* childNeuron;
  Neuron* parentNeuron;
  
  public:
  NeuronLink();
  ~NeuronLink();
  
  virtual void processSignal(double signal);
  virtual string getParentNeuronName();
  virtual string getChildNeuronName();
  void changeWeight(double, double);
  
  double getWeight();
  void setWeight(double);
  
  Neuron* getChildNeuron();
  Neuron* getParentNeuron();
  
  friend ostream& operator << (ostream& s, NeuronLink&);
};




class DoubleNeuronLink : public NeuronLink{
  
public:
  DoubleNeuronLink(Neuron* parent, Neuron* child);
  ~DoubleNeuronLink();
};




class EndNeuronLink : public NeuronLink{
  
private:
  ResultProcessor* resultProcessor;
  
public:
  EndNeuronLink(Neuron* parent, ResultProcessor*);
  ~EndNeuronLink();
  
  void processSignal(double signal);
  string getChildNeuronName();
};




class StartNeuronLink : public NeuronLink{
  
public:
  StartNeuronLink(Neuron* child);
  ~StartNeuronLink();
  
  string getParentNeuronName();
};

#endif