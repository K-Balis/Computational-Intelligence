#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include <time.h>   

/*	User can change those below	*/
#define H1 12							/*	Number of neuron in first hidden layer	*/
#define H2 8							/*	Number of neuron in second hidden layer	*/
#define H3 10							/*	Number of neuron in third hidden layer	*/
#define ACTIVATION_FUNC 0				/*	Use 0 for logistic, 1 for tanh and 2 for relu	*/
#define n 0.005							/*	Learning rate	*/
#define B 40							/*	Number of min-batches	*/
#define TERMINATION_THRESHOLD 0.0001

/*	Should not be changed	*/
#define TOTAL_POINTS 8000
#define d 2								/*	Input	*/
#define K 3								/*	Categories/Output	*/
#define MAX 1
#define MIN -1

struct point{
    float x1;
    float x2;
    int category;
};

struct neuronLayer1{					/*	define architecture of neurons in each layer	*/
    float bias; 
    float partialDerivativeBias;
    float weights[d];
    float partialDerivativeWeights[d];
    float y;
    float output;
    float delta;
};
struct neuronLayer2{
    float bias; 
    float partialDerivativeBias;
    float weights[H1];
    float partialDerivativeWeights[H1];
    float y;
    float output;
    float delta;
};

struct neuronLayer3{
    float bias; 
    float partialDerivativeBias;
    float weights[H2];
    float partialDerivativeWeights[H2];
    float y;
    float output;
    float delta;
};

struct neuronOutputLayer{
    float bias; 
    float partialDerivativeBias;
    float weights[H3];
    float partialDerivativeWeights[H3];
    float y;
    float output;
    float delta;
};

struct point points[TOTAL_POINTS];
struct neuronLayer1 hiddenLayer1[H1];		/*	Each layer is a ccollection of neurons with the architecture of the layer	*/
struct neuronLayer2 hiddenLayer2[H2];
struct neuronLayer3 hiddenLayer3[H3];
struct neuronOutputLayer outputLayer[K];

void loadPoints(){							/*	Read data from file data.txt	*/
	int i = 0;
	FILE *f;
	f = fopen("data.txt", "r");
	if(f == NULL){
    	printf("Error while opening file data.txt for read\n");
    	exit(1);
	}
	while (!feof(f)){  
    	fscanf (f, "%f %f %d", &points[i].x1, &points[i].x2, &points[i].category);
    	i++;   
    }
	fclose (f); 
}

void initializeWeights(){					/*	Random initialization of weights and bias in (-1,1)	*/
    for(int i = 0; i < H1; i++){
        for(int j = 0; j < d; j++){
            hiddenLayer1[i].weights[j] = (((float)rand()) / RAND_MAX) * (MAX - MIN) + MIN;
        }
        hiddenLayer1[i].bias = (((float)rand()) / RAND_MAX) * (MAX - MIN) + MIN;
    }
    for(int i = 0; i < H2; i++){
        for(int j = 0; j < H1; j++){ 
            hiddenLayer2[i].weights[j] = (((float)rand()) / RAND_MAX) * (MAX - MIN) + MIN;
        }
        hiddenLayer2[i].bias = (((float)rand()) / RAND_MAX) * (MAX - MIN) + MIN;
    }
	for(int i = 0; i < H3; i++){
        for(int j = 0; j < H2; j++){ 
            hiddenLayer3[i].weights[j] = (((float)rand()) / RAND_MAX) * (MAX - MIN) + MIN;
        }
        hiddenLayer3[i].bias = (((float)rand()) / RAND_MAX) * (MAX - MIN) + MIN;
    }
    for(int i = 0; i < K; i++){
        for(int j = 0; j < H3; j++){ 
            outputLayer[i].weights[j] = (((float)rand()) / RAND_MAX) * (MAX - MIN) + MIN;
        }
        outputLayer[i].bias = (((float)rand()) / RAND_MAX) * (MAX - MIN) + MIN;
    }
}

void clearDerivatives(){					/*	After update of weights clear dE/dwi	*/
	int i, j;
    for(int i = 0; i < H1; i++){
        for(int j = 0; j < d; j++){
            hiddenLayer1[i].partialDerivativeWeights[j] = 0.0;
        }
        hiddenLayer1[i].partialDerivativeBias = 0.0;
    }
    for(int i = 0; i < H2; i++){
        for(int j = 0; j < H1; j++){ 
            hiddenLayer2[i].partialDerivativeWeights[j] = 0.0;
        }
        hiddenLayer2[i].partialDerivativeBias = 0.0;
    }
	for(int i = 0; i < H3; i++){
        for(int j = 0; j < H2; j++){ 
            hiddenLayer3[i].partialDerivativeWeights[j] = 0.0;
        }
        hiddenLayer3[i].partialDerivativeBias = 0.0;
    }
    for(int i = 0; i < K; i++){
        for(int j = 0; j < H3; j++){ 
            outputLayer[i].partialDerivativeWeights[j] = 0.0;
        }
        outputLayer[i].partialDerivativeBias = 0.0;
    }
}

/*	Define Activation functions	*/
float logistic(float input){
    return (1 / (1 + exp((double)-input)));
}

float derivativeLogistic(float input){
	return logistic(input) * (1 - logistic(input));
}

float derivativeTanh(float input){
	return (1 - pow(tanh(input), 2));
}

float relu(float input){
	if (input >= 0)
		return input;
	else
		return 0.0;
}

float derivativeRelu(float input){
	if (input >= 0)
		return 1.0;
	else
		return 0.0;
}

float computeOutput(float input){
	if(ACTIVATION_FUNC == 0){
		return logistic(input);
	}
	else if(ACTIVATION_FUNC == 1){
		return tanh(input);
	}
	else if(ACTIVATION_FUNC == 2){
		return relu(input);
	}
}

float computeDelta(float y){
	if(ACTIVATION_FUNC == 0){
		return derivativeLogistic(y);	
	}
	else if(ACTIVATION_FUNC == 1){
		return derivativeTanh(y);
	}
	else if(ACTIVATION_FUNC == 2){
		return derivativeRelu(y);
	}
}

void forwardpass(struct point point){
    for(int i = 0; i < H1; i++){
        hiddenLayer1[i].y = 0.0;
        hiddenLayer1[i].y += hiddenLayer1[i].weights[0] * point.x1;
        hiddenLayer1[i].y += hiddenLayer1[i].weights[1] * point.x2;
        hiddenLayer1[i].y += hiddenLayer1[i].bias; 
        hiddenLayer1[i].output = computeOutput(hiddenLayer1[i].y);
    }
	for(int i = 0; i < H2; i++){
        hiddenLayer2[i].y = 0.0;
        for(int j = 0; j < H1; j++){
            hiddenLayer2[i].y += hiddenLayer2[i].weights[j] * hiddenLayer1[j].output;
        }
        hiddenLayer2[i].y += hiddenLayer2[i].bias;
		hiddenLayer2[i].output = computeOutput(hiddenLayer2[i].y);
    }
	for(int i = 0; i < H3; i++){
        hiddenLayer3[i].y = 0.0;
        for(int j = 0; j < H2; j++){
            hiddenLayer3[i].y += hiddenLayer3[i].weights[j] * hiddenLayer2[j].output;
        }
        hiddenLayer3[i].y += hiddenLayer3[i].bias;
		hiddenLayer3[i].output = computeOutput(hiddenLayer3[i].y);
    }
	for(int i = 0; i < K; i++){
        outputLayer[i].y = 0.0;
        for(int j = 0; j < H3; j++){
            outputLayer[i].y += outputLayer[i].weights[j] * hiddenLayer3[j].output;
        }
        outputLayer[i].y += outputLayer[i].bias;
        outputLayer[i].output = logistic(outputLayer[i].y);
    }
}

void backprop(struct point point){
    for(int i = 0; i < K; i++){
		if((i+1) == point.category){
			outputLayer[i].delta = derivativeLogistic(outputLayer[i].y) * (outputLayer[i].output - 1);
		}
		else{
			outputLayer[i].delta = derivativeLogistic(outputLayer[i].y) * (outputLayer[i].output - 0);
		}
        for(int j = 0; j < H3; j++){
        	outputLayer[i].partialDerivativeWeights[j] += outputLayer[i].delta * hiddenLayer3[j].output;
        }
        outputLayer[i].partialDerivativeBias += outputLayer[i].delta;
    }
	for(int i = 0; i < H3; i++){
        hiddenLayer3[i].delta = 0.0;
        for(int j = 0; j < K; j++){
            hiddenLayer3[i].delta += outputLayer[j].delta * outputLayer[j].weights[i];
        }
		hiddenLayer3[i].delta = hiddenLayer3[i].delta * computeDelta(hiddenLayer3[i].y);
        for(int j = 0; j < H2; j++){
        	hiddenLayer3[i].partialDerivativeWeights[j] += hiddenLayer3[i].delta * hiddenLayer2[j].output;
        }
        hiddenLayer3[i].partialDerivativeBias += hiddenLayer3[i].delta;
    }
    for(int i = 0; i < H2; i++){
        hiddenLayer2[i].delta = 0.0;
        for(int j = 0; j < H3; j++){
            hiddenLayer2[i].delta += hiddenLayer3[j].delta * hiddenLayer3[j].weights[i];
        }
		hiddenLayer2[i].delta = hiddenLayer2[i].delta * computeDelta(hiddenLayer2[i].y);
        for(int j = 0; j < H1; j++){
        	hiddenLayer2[i].partialDerivativeWeights[j] += hiddenLayer2[i].delta * hiddenLayer1[j].output;
        }
        hiddenLayer2[i].partialDerivativeBias += hiddenLayer2[i].delta;
    }
    for(int i = 0; i < H1; i++){
        hiddenLayer1[i].delta = 0.0;
        for(int j = 0; j < H2; j++){
            hiddenLayer1[i].delta += hiddenLayer2[j].delta * hiddenLayer2[j].weights[i];
        }
		hiddenLayer1[i].delta = hiddenLayer1[i].delta * computeDelta(hiddenLayer1[i].y);
        hiddenLayer1[i].partialDerivativeWeights[0] += hiddenLayer1[i].delta * point.x1;
        hiddenLayer1[i].partialDerivativeWeights[1] += hiddenLayer1[i].delta * point.x2;
        hiddenLayer1[i].partialDerivativeBias += hiddenLayer1[i].delta;
    }
}

float calculateError(struct point point){
	float squareError;
	for(int i = 0; i < K; i++){
		if(point.category == (i + 1)){
			squareError = pow(1 - outputLayer[i].output, 2);
		}
	}
    return squareError;
}

void updateWeights(){
	for(int i = 0; i < K; i++){
    	for(int j = 0; j < H3; j++){
            outputLayer[i].weights[j] = outputLayer[i].weights[j] - (n * outputLayer[i].partialDerivativeWeights[j]);
        }
        outputLayer[i].bias = outputLayer[i].bias - (n * outputLayer[i].partialDerivativeBias);
    }
	for(int i = 0; i < H3; i++){
        for(int j = 0; j < H2; j++){
            hiddenLayer3[i].weights[j] = hiddenLayer3[i].weights[j] - (n * hiddenLayer3[i].partialDerivativeWeights[j]);
        }
        hiddenLayer3[i].bias = hiddenLayer3[i].bias - (n * hiddenLayer3[i].partialDerivativeBias);
    }
	for(int i = 0; i < H2; i++){
        for(int j = 0; j < H1; j++){
            hiddenLayer2[i].weights[j] = hiddenLayer2[i].weights[j] - (n * hiddenLayer2[i].partialDerivativeWeights[j]);
        }
        hiddenLayer2[i].bias = hiddenLayer2[i].bias - (n * hiddenLayer2[i].partialDerivativeBias);
    }
	for(int i = 0; i < H1; i++){
        for(int j = 0; j < d; j++){
            hiddenLayer1[i].weights[j] = hiddenLayer1[i].weights[j] - (n * hiddenLayer1[i].partialDerivativeWeights[j]);
        }
        hiddenLayer1[i].bias = hiddenLayer1[i].bias - (n * hiddenLayer1[i].partialDerivativeBias);
    }
}

int prediction(struct point point){				/*	Find MLPs prediction for the category of the input	*/
	float max_output = -1.0;
	int prediction;
	for(int i = 0; i < K; i++){
		if(outputLayer[i].output > max_output){
			max_output = outputLayer[i].output;
			prediction = (i+1);
		}
	}											/*	If prediction is the actual category return 1 else 0	*/
	if(prediction == point.category){
		return 1;
	}
	else{
		return 0;
	}
}

int main(){
	srand(time(NULL));
	int epoch = 0, correct_predictions = 0, false_predictions = 0;
	float currentError = 0.0, previousError = 0.0;
	struct point errors[TOTAL_POINTS/2];
	FILE *results;
	loadPoints();
	initializeWeights();
	do{
		epoch++;
		previousError = currentError;
		currentError = 0.0;
		for(int i = 0; i < (TOTAL_POINTS / 2); i+=B){				/*	First half of the point will be used for training	*/
			clearDerivatives();
			for(int j = i; j < B+i; j++){							/*	Work in batches	*/
				forwardpass(points[j]);
				backprop(points[j]);
				currentError += calculateError(points[j]); 
			}
			updateWeights();
		}
		currentError /= B;
		printf("Epoch : %d with error : %f\n", epoch, currentError);	/*	Print current epoch's error	*/
	}while(epoch < 700 || fabs(currentError - previousError) > TERMINATION_THRESHOLD);
	
	results = fopen("results.txt", "w");								/*	Write results in file so we can create a plot	*/
	if(results == NULL){
    	printf("Error opening file!\n");
    	exit(1);
	}
	for(int i = (TOTAL_POINTS / 2); i < TOTAL_POINTS; i++){			/*	Second half will be used for validation	*/
        forwardpass(points[i]);
        if(prediction(points[i]) == 1){
        	fprintf(results, "%f %f %d\n", points[i].x1, points[i].x2, points[i].category);		/*	For correct predictions write category too	*/
        	correct_predictions++;
        }
        else if(prediction(points[i]) == 0){
        	errors[false_predictions] = points[i];
			false_predictions++;
        }
    }
	for(int i = 0; i < false_predictions; i++){
		fprintf(results, "%f %f\n", errors[i].x1, errors[i].x2);
	}
	rewind(results);
	fprintf(results, "%d\n", correct_predictions);
    printf("Generalization of Neural Network (Percentage of correct predictions) : %f\n", (float)correct_predictions/(TOTAL_POINTS / 2));	/*	After training print percentage of correct predictions	*/
	return 0;
}