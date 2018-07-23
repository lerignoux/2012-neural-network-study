#include "layer.h"

/*********************************************************************************
 * 	Initialisations
 * ******************************************************************************/

Layer::Layer(unsigned int nbNeurons)
{
  this->nbNeurons = nbNeurons;
  neurons = new Neuron*[nbNeurons];
  for(unsigned int i=0; i<this->nbNeurons;i++)
  {
    neurons[i]= new Neuron();
  }
}

Layer::~Layer()
{
}



/*********************************************************************************
 * 	Get
 * ******************************************************************************/

Neuron* Layer::getNeuron(unsigned int i)
{
  if (i>nbNeurons) return NULL;
  else return neurons[i];
}


unsigned int Layer::getNbNeuron()
{
  return nbNeurons;
}



/*********************************************************************************
 * 	Set
 * ******************************************************************************/

StartNeuronLink** Layer::setStartLayer()
{
  StartNeuronLink** startLinks = new StartNeuronLink*[nbNeurons];
  for(unsigned int i=0;i<nbNeurons;i++)
  {
    startLinks[i] = new StartNeuronLink(neurons[i]);
  }
  return startLinks;
}


EndNeuronLink* Layer::setEndLayer(ResultProcessor* resultProcessor)
{
  return new EndNeuronLink(neurons[0], resultProcessor);
}



/*********************************************************************************
 * 	Misc
 * ******************************************************************************/

void Layer::linkSubLayer(Layer* layer)
{
  for(unsigned int i=0;i<nbNeurons;i++)
  {
    layer->addParentNeuron(neurons[i]);
  }
}


void Layer::addParentNeuron(Neuron* neuron)
{
  DoubleNeuronLink *link;
  for(unsigned int i=0;i<nbNeurons;i++)
  {
    link = new DoubleNeuronLink(neuron,neurons[i]);
  };
}


void Layer::processLayer(void)
{
    for(unsigned int i=0;i<nbNeurons;i++)
  {
    cout << *neurons[i] << endl;
    neurons[i]->processInputs();
  }
}


void Layer::clean()
{
  for (unsigned int i=0;i<nbNeurons;i++)
  {
    neurons[i]->clean();
  }
  cout << "Layer cleaned." << endl;
}



/*********************************************************************************
 * 	Cout
 * ******************************************************************************/

ostream& operator << (ostream& s, Layer& l)  //display
{
  s << "nb Neurons in the layer : " << l.nbNeurons << endl;
  for (unsigned int i=0; i<l.nbNeurons;i++)
  {
    s << l.neurons[i]->getName() << endl;
  };
  return s;
}