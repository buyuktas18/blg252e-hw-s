/*Deniz BÜYÜKTAŞ
150180006*/

#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
using namespace std;

class Neuron{
    public:
    float value;
    float activated;
    virtual void activate() = 0;
};

class SigmoidNeuron : public Neuron{
    public: 
    void activate();
};

void SigmoidNeuron::activate(){
    activated = 1 / (1 + exp(-value));
    
}

class ReluNeuron : public Neuron{
    public: 
    void activate();
};

void ReluNeuron::activate(){
    activated = max(0.0, double(value));
    
}

class LReluNeuron : public Neuron{
    public: 
    void activate();
};

void LReluNeuron::activate(){
    activated = max(0.1 * value, double(value));
}

class Layer{
    public:
    Neuron *neurons = NULL;
    ~Layer();
};

Layer::~Layer(){
    delete [] neurons;
}

class Network{
    public:
    Layer *layers = NULL;
    ~Network();
};

Network::~Network(){
    delete [] layers;
}

int main(int argc, char *argv[]){
    Network network1;
    int data;
    ifstream myfile;
    myfile.open(argv[1]);
    myfile>>data;
    int numOfLayer = data;
    
    network1.layers = new Layer[numOfLayer];
    int layers[numOfLayer];
    for(int i = 0; i < numOfLayer; i++){
        myfile>>data;
        layers[i] = data;
    }
    try{
    for(int i = 0; i < numOfLayer; i++){
        
        myfile>>data;
        if(data == 0){
            network1.layers[i].neurons = new SigmoidNeuron[layers[i]];
        }
        else if(data == 1){
            network1.layers[i].neurons = new LReluNeuron[layers[i]];
        }
        else if(data == 2){
            network1.layers[i].neurons = new ReluNeuron[layers[i]];
        }
        else{
            throw "Unidentified activation function!";
        }
    }
   
    
        for(int i = 0; i < numOfLayer; i++){ 
            
            myfile>>data;
            network1.layers[0].neurons[i].activated = data;
            
        }
        if(!(myfile.eof())){
            throw "Input shape does not match!";
        }

    for(int i = 0; i < numOfLayer - 1; i++){
        float w_matrix[layers[i + 1]][layers[i]];
        for(int a = 0; a < layers[i + 1]; a++){
            for(int b = 0; b < layers[i]; b++){
                w_matrix[a][b] = 0.1;
            }
        }
        float x_matrix[layers[i]];
        for(int a = 0; a < layers[i]; a++){
            x_matrix[a] = network1.layers[i].neurons[a].activated;
        }
        float b_matrix[layers[i + 1]];
        for(int a = 0; a < layers[i + 1]; a++){
            b_matrix[a] = 0.1;
        }
        float z_matrix[layers[i + 1]];
        for(int a = 0; a < layers[i + 1]; a++){
            z_matrix[a] = 0;
        }
        for(int a = 0; a < layers[i + 1]; ++a){
            for(int k = 0; k < layers[i]; ++k)
            {
                z_matrix[a] += w_matrix[a][k] * x_matrix[k];
            }
        }
        for(int a = 0; a < layers[i+1]; a++){
            z_matrix[a] += b_matrix[a];
        }

         for(int a = 0; a < layers[i+1]; a++){
            network1.layers[i + 1].neurons[a].value = z_matrix[a];
            network1.layers[i + 1].neurons[a].activate();

        }
    }
    for(int i = 0; i < numOfLayer; i++){
        cout<<"Layer "<<i<<":"<<endl;
        for(int j = 0; j < layers[i]; j++){
            cout<<network1.layers[i].neurons[j].activated<<endl;
        }
    }
        
    }
    catch(const char *result){
        cout<<result<<endl;
    }
}