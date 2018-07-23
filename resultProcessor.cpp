#include "resultProcessor.h"

/*********************************************************************************
 * 	Initialisation
 * ******************************************************************************/

ResultProcessor::ResultProcessor(Layer** layers,unsigned int nbLayers, char* mode)
{
  learning=true;
  learningRate=0.1;
  
  this->layers=layers;
  this->nbLayers=nbLayers;
  
  if (mode == "batch") {this->mode = "batch";}
  else {mode = "normal";}
}

ResultProcessor::~ResultProcessor()
{
}


/*********************************************************************************
 * 	Set
 * ******************************************************************************/

void ResultProcessor::setLearning(bool learn)
{
  learning = learn;
}


void ResultProcessor::setExpectedResult(double result)
{
  expected = result;
}

void ResultProcessor::setBatchMode()
{
  batchMode = true;
}

/*********************************************************************************
 * 	Get
 * ******************************************************************************/

double ResultProcessor::getResult()
{
  return result;
}

bool ResultProcessor::getLearning()
{
  return learning;
}


/*********************************************************************************
 * 	Misc
 * ******************************************************************************/

void ResultProcessor::processResult(double result)
{
  if (learning)
  {
    cycle++;
    // modif output Neuron
    Neuron* currentNeuron = layers[nbLayers-1]->getNeuron(0);
    double currentGradient=0;
    double currentError=expected-result;
          
    double squareError = 0.5*currentError*currentError;
    averageError = (averageError*((double)cycle-1.0) + squareError)/(double)cycle;
    
    if (batchMode)
    {
      cout << endl << " ********* Starting Batch Mode : ************" << endl << endl;
      currentGradient = averageError*currentNeuron->dActivationFunction(currentNeuron->getLocalField());
      
      currentNeuron->setGradient(currentGradient);
    }
    
    else
    {
      cout << endl << " ********* Starting FeedBack : ************" << endl << " expected result = " << expected << " Error = " << currentError << endl;
      currentGradient = currentError*currentNeuron->dActivationFunction(currentNeuron->getLocalField());
      
      currentNeuron->setGradient(currentGradient);
      
      currentNeuron->changeParentsWeight(learningRate);

      
      cout << "Current average error : " << averageError << endl;
      
      // modif inner Neurons

      for (unsigned int i=nbLayers-2;i>0;i--)
      {
	cout << endl << endl << " **** Retroprocessing Layer : " << i << " ****" << endl;
	for (unsigned int j=0;j<layers[i]->getNbNeuron();j++)
	{
	  currentNeuron = layers[i]->getNeuron(j);
	  currentNeuron->setGradient();
	  
	  for (unsigned int parent=0;parent<currentNeuron->getNbParents();parent++)
	  {
	    currentNeuron->changeParentsWeight(learningRate);
	  }
	}
      }
    }
    if (averageError < 0.001) learning = false;
  }
  this->result = result;
}

void ResultProcessor::batchTrain()
{
  Neuron* currentNeuron;
  for (unsigned int i=nbLayers-2;i>0;i--)
      {
	cout << endl << endl << " **** Retroprocessing Layer : " << i << " ****" << endl;
	for (unsigned int j=0;j<layers[i]->getNbNeuron();j++)
	{
	  currentNeuron = layers[i]->getNeuron(j);
	  currentNeuron->setGradient();
	  
	  for (unsigned int parent=0;parent<currentNeuron->getNbParents();parent++)
	  {
	    currentNeuron->changeParentsWeight(learningRate);
	  }
	}
      }
}

void ResultProcessor::cleanLayers()
{
  for (unsigned int i=0;i<nbLayers;i++)
  {
    layers[i]->clean();
  }
}
