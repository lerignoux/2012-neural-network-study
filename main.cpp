#include "main.h"

using namespace std;


/*********************************************************************************
 * 	Main program : create and launch the process.
 * ******************************************************************************/

int main (int argc, char * const argv[]) {
  
  /************************************* initialisation ***********************************************/
  srand( time(NULL) );
  
  /* creation of the Data */
  
  cout << " Starting the propgram. the input Data will be read on the file \"inputImage.bmp\"" << endl;
  
  Data* data = new Data("inputImage.bmp");
  Data* testData = new Data(data->getSizeX(),data->getSizeY());
//   cout << *data;
    
  unsigned int nbNeurons = 10; // two neurons per layer
  
  cout << "how many Neurons do you want in each Layer ?" << endl;
//   cin >> nbNeurons ;

  
  unsigned int hiddenLayers;
  
  cout << "How many hidden Layers do you want ?" << endl;
//   cin >> hiddenLayers;
  
  unsigned int nbLayers = 3;

  /* creation of the layers */
  
  Layer** layers = new Layer*[nbLayers];
  layers[0] = new Layer(2);
  for (unsigned int i=1; i<nbLayers-1;i++)
  {
    layers[i] = new Layer(nbNeurons);
  }
  layers[nbLayers-1] = new Layer(1);
  
  /* initialisation of the feedBack manager (for learning) */
  
  ResultProcessor *resultProcessor = new ResultProcessor(layers,nbLayers, "normal");
  
  /************************************* initialisation of the network ***********************************************/
  
  cout << endl << endl << " ************* settings start layers ************* " << endl << endl;
  StartNeuronLink** inputLinks = layers[0]->setStartLayer();
  
  cout << endl << endl << " ************* settings end layers ************* " << endl << endl;
  EndNeuronLink * endLink = layers[nbLayers-1]->setEndLayer(resultProcessor);
  
  cout << endl << endl << " ************* connecting 0-1 layers ************* " << endl << endl;
  layers[0]->linkSubLayer(layers[1]);
  
  cout << endl << endl << " ************* connecting 1-2 layers ************* " << endl << endl;
  layers[1]->linkSubLayer(layers[2]);

  cout << "What learning Mode do you want ? batch or normal" << endl;
  
  char* mode=new char[20];
  cin >> mode;
  
  
  /************************************* initialisation of the signal ***********************************************/

  cout << endl << endl << " ************* Initialising signal ************* " << endl << endl;

  unsigned int count=0; // avoid a possible infinite loop
  while (resultProcessor->getLearning() and count<1000)
  {
    
    if (mode=="batch")
    {
      unsigned int batchSize = 20;
      double** currentSet = data->getSet(batchSize);
      
      resultProcessor->setBatchMode();
      
      for (unsigned int i=0;i<batchSize;i++)
      {
	
	double* current = currentSet[i];
	inputLinks[0]->processSignal((2.0*current[0])/(double)data->getSizeX() - (double)data->getSizeX());
	inputLinks[1]->processSignal((2.0*current[1])/(double)data->getSizeY() - (double)data->getSizeX());
	resultProcessor->setExpectedResult(current[2]);
	
	  /************************************* processing the signal in the layers ***********************************************/
	  cout << endl << endl << " *************************************************** " << endl << "processing input data : "<< endl ;
	  for (unsigned int k=0; k<nbLayers;k++)
	  {
	    cout << "          starting processing layer " << k << endl;
	    layers[k]->processLayer();
	  }
	resultProcessor->cleanLayers();
      }
      resultProcessor->batchTrain();
      
    }
    else // normal mode
    {
      double* current = data->get();
      inputLinks[0]->processSignal((2.0*current[0])/(double)data->getSizeX() - (double)data->getSizeX());
      inputLinks[1]->processSignal((2.0*current[1])/(double)data->getSizeY() - (double)data->getSizeX());
      resultProcessor->setExpectedResult(current[2]);
    
      /************************************* processing the signal in the layers ***********************************************/
      cout << endl << endl << " *************************************************** " << endl << "processing input data : "<< endl ;
      for (unsigned int k=0; k<nbLayers;k++)
      {
	cout << "          starting processing layer " << k << endl;
	layers[k]->processLayer();
      }
      resultProcessor->cleanLayers();
    }
    count++;
  };
  
  
    /************************************* application on a blanc data to see the classification ***********************************************/
  
  resultProcessor->setLearning(false);
  for (unsigned int i=0;i<testData->getSizeX();i++)
  {
    for (unsigned int j=0;j<testData->getSizeY();j++)
    {
      inputLinks[0]->processSignal(i);
      inputLinks[1]->processSignal(j);
      for (unsigned int k=0; k<nbLayers-1;k++)
      {
	cout << "processing input data : i = " << i << " j = " << j << endl << "starting processing layer " << k << endl;
	layers[k]->processLayer();
      }
      testData->set(i,j,resultProcessor->getResult());
      resultProcessor->cleanLayers();
    }
  }
  testData->writeImage("result.bmp");
  return 0;
}
