CC = g++
CFLAGS = -lm 
# -O3 -pipe -fomit-frame-pointer -funroll-all-loops -s
OBJECTS = main.o data.o neuronLink.o layer.o neuron.o resultProcessor.o EasyBMP.o

NeuralNetwork : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o neuralNetwork

main.o : main.cpp
	$(CC) $(CFLAGS) -c main.cpp

data.o : data.cpp EasyBMP.h
	$(CC) $(CFLAGS) -c data.cpp

neuronLink.o : neuronLink.cpp
	$(CC) $(CFLAGS) -c neuronLink.cpp

layer.o : layer.cpp
	$(CC) $(CFLAGS) -c layer.cpp

neuron.o : neuron.cpp
	$(CC) $(CFLAGS) -c neuron.cpp

resultProcessor.o : resultProcessor.cpp
	$(CC) $(CFLAGS) -c resultProcessor.cpp

EasyBMP.o: ./EasyBMP.cpp ./EasyBMP*.h
	g++ $(CFLAGS) -c EasyBMP.cpp
