#include "neuronLink.h"


/*********************************************************************************
 * 	Initialisation
 * ******************************************************************************/


NeuronLink::NeuronLink()
{
  weight= ((double) rand())/RAND_MAX-0.5;
  alpha=(double) 0.1;
  previousWeight=weight;
  cout << "starting weight = " << weight;
}

DoubleNeuronLink::DoubleNeuronLink(Neuron* parent, Neuron* child)
{
  NeuronLink();
  childNeuron = child;
  childNeuron->addParentLink(this);
  parentNeuron = parent;
  parentNeuron->addChildLink(this);
  cout << "doubleNeuron " << this << " created connecting " << parent->getName() << " to " << child->getName() << endl;
}


StartNeuronLink::StartNeuronLink(Neuron* child)
{
  NeuronLink();
  childNeuron = child;
  childNeuron->addParentLink(this);
  cout << "startNeuron " << this << " created connecting " << child->getName() << endl;
}


EndNeuronLink::EndNeuronLink(Neuron* parent,ResultProcessor* processor)
{
  NeuronLink();
  parentNeuron = parent;
  parentNeuron->addChildLink(this);
  cout << "endNeuron " << this << " created connecting " << parent->getName() << endl;
  resultProcessor = processor;
  weight=1;
}

NeuronLink::~NeuronLink()
{
}



/*********************************************************************************
 * 	Set
 * ******************************************************************************/

void NeuronLink::setWeight(double newWeight)
{
  previousWeight=weight;
  weight=newWeight;
}



/*********************************************************************************
 * 	Get
 * ******************************************************************************/

string NeuronLink::getParentNeuronName(){
  return parentNeuron->getName();
}


string NeuronLink::getChildNeuronName()
{
  return childNeuron->getName(); 
}


string StartNeuronLink::getParentNeuronName(){
  return string("no parent");
}


string EndNeuronLink::getChildNeuronName(){
  return string("no children");
}


double NeuronLink::getWeight()
{
  return weight;
}


Neuron* NeuronLink::getChildNeuron()
{
  return childNeuron;
}


Neuron* NeuronLink::getParentNeuron()
{
  return parentNeuron;
}



/*********************************************************************************
 * 	Misc
 * ******************************************************************************/

void NeuronLink::processSignal(double signal)
{
  lastSignal = signal;
  childNeuron->addInput(signal*weight);
}


void EndNeuronLink::processSignal(double signal)
{
  cout << "end neuron found, transmitting output : " << signal << " to result processor" << endl << endl;
  resultProcessor->processResult(signal);
}


void NeuronLink::changeWeight(double delta, double learningRate)
{
  double newWeight = weight+alpha*(weight-previousWeight)+learningRate*delta*lastSignal;
  cout << "changing Link weight of : " << learningRate*delta*lastSignal << " new = " << newWeight << endl;
  setWeight(newWeight);
}



/*********************************************************************************
 * 	Cout
 * ******************************************************************************/

ostream& operator << (ostream& s, NeuronLink& l)  //display
{
  s << "neuron Link id = " << &l << " of weight " << l.weight << endl;
  return s;
}  