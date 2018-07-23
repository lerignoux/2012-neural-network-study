#include "neuron.h"

/*********************************************************************************
 * 	Initialisations
 * ******************************************************************************/

Neuron::Neuron()
{
  static unsigned int neuronNameInd = 0;
  
  bias = ((double) rand())/RAND_MAX-0.5;
  b=2.0/3.0;
  a=1.7159;
  nbParents=0;
  nbChildren=0;
  ++neuronNameInd;
  name << string("Neurone_") << neuronNameInd ;
  cout << "neuron created " << this->getName()  << endl;
  
  localField=bias;
  
  parentsLinks = new NeuronLink*[0];
  childrenLinks = new NeuronLink*[0];
}

Neuron::~Neuron()
{
  
}

/*********************************************************************************
 * 	Set
 * ******************************************************************************/

/* Unused, parents are added, not set */
void Neuron::setParentLink(NeuronLink* neuronLink)
{
  nbParents = 1;
  NeuronLink** parentsLinks = new NeuronLink*[nbParents];
  parentsLinks[0]=neuronLink;
}

void Neuron::setChildLink(NeuronLink* neuronLink)
{
  nbChildren = 1;
  NeuronLink** childrenLinks = new NeuronLink*[1];
  childrenLinks[0]=neuronLink;
}

void Neuron::setGradient(double gradient)
{
  this->gradient=gradient;
}

void Neuron::setGradient()
{
  cout << " ------- setting gradient of " << getName() ;
  double childSum = 0;
  for (unsigned int i=0;i<nbChildren;i++)
  {
    Neuron* child = this->getChild(i)->getChildNeuron();
    childSum += this->getChild(i)->getWeight()*child->getGradient();
  }
  
  gradient = dActivationFunction(localField)*childSum;
  cout << " my gradient is " << gradient << endl;
}
/*********************************************************************************
 * 	Get
 * ******************************************************************************/

string Neuron::getName()
{
  return name.str();
}

unsigned int Neuron::getNbChildren()
{
  return nbChildren;
}

NeuronLink* Neuron::getChild(unsigned int child)
{
  return (childrenLinks[child]);
}

NeuronLink* Neuron::getParent(unsigned int parent)
{
  return (parentsLinks[parent]);
}

unsigned int Neuron::getNbParents(void)
{
  return nbParents;
}

double Neuron::getLocalField()
{
  return localField;
}
double Neuron::getGradient()
{
  return gradient;
}
/*********************************************************************************
 * 	Create the network
 * ******************************************************************************/

void Neuron::addParentLink(NeuronLink* neuronLink)
{
  cout << "addParentLink to " << this->getName() << " link : " << neuronLink << endl;
  NeuronLink** newParents = new NeuronLink*[nbParents+1];
  for(unsigned int i=0;i<nbParents;i++)
  {
    newParents[i]=parentsLinks[i];
  }
  newParents[nbParents] = neuronLink;
  delete parentsLinks;
  parentsLinks=newParents;
  nbParents++;
}


void Neuron::addChildLink(NeuronLink* neuronLink)
{
  cout << "addChildLink to " << this->getName() << " link : " << neuronLink << endl;
  NeuronLink** newChildren = new NeuronLink*[nbChildren+1];
  for(unsigned int i=0;i<nbChildren;i++)
  {
    newChildren[i]=childrenLinks[i];
  }
  newChildren[nbChildren] = neuronLink;
  delete childrenLinks;
  childrenLinks=newChildren;
  nbChildren++;
}


/*********************************************************************************
 * 	Misc
 * ******************************************************************************/

double Neuron::addInput(double input)
{
  localField+=input;
//   cout << " local field updated : new = " << localField <<  endl;
}


void Neuron::processInputs()
{
  transmitSignal(activationFunction(localField));
}


void Neuron::transmitSignal(double signal)
{
  cout << "signal transmited : " << signal << endl;
  for (unsigned int i=0;i<nbChildren;i++)
  {
    childrenLinks[i]->processSignal(signal);
  }
}


void Neuron::changeParentsWeight(double learningRate)
{
  cout << "I have " << nbParents << " parents" << endl;
  for (unsigned int i=0;i<nbParents;i++)
  {
    cout << "     " << parentsLinks[i] << " changing is relative weight of : " << gradient << endl;
    parentsLinks[i]->changeWeight(gradient,learningRate);
  };
  bias = bias + learningRate*gradient;
}


void Neuron::clean()
{
  localField=bias;
  gradient=0;
}


double Neuron::activationFunction(double x)
{
//   cout << "activation function : input = " << x << ", output = "<< b*tanh(a*x) << endl;
  return a*tanh(b*x);
}


double Neuron::dActivationFunction(double x)
{
  return ((b/a)*(a-x)*(a+x));
}



/*********************************************************************************
 * 	Cout
 * ******************************************************************************/

ostream& operator << (ostream& s, Neuron& n)  //display
{
  s << "neuron " << n.name.str();
  s << " I have " << n.nbParents << " parents, they are :" << endl;
  for (unsigned int i=0;i<n.nbParents;i++)
  {
    s << " " << *n.parentsLinks[i];
  }
  s << endl;
  s << " I have " << n.nbChildren << " children they are :" << endl;
  for (unsigned int i=0;i<n.nbChildren;i++)
  {
    s << " " << *n.childrenLinks[i];
  }
  
//   cout << " My characteristics are :" << " local field = " << n.localField << " gradient = " << n.gradient << endl;
  
  return s;
}  