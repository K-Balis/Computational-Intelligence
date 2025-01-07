#include <stdio.h>
#include <stdlib.h> // for rand func
#include <math.h> // for math purposes (pow)
#include <time.h>

#define N 8000
#define MIN -1
#define MAX 1

int getCategory(float x1, float x2){
	if(pow(x1 - 0.5 , 2) + pow(x2 - 0.5 , 2) < 0.2){
		if(x2 > 0.5)
			return 1;
		else
			return 2;
	}
	else if(pow(x1 + 0.5 , 2) + pow(x2 + 0.5 , 2) < 0.2){
		if(x2 > -0.5)
			return 1;
		else
			return 2;
	}
	else if(pow(x1 - 0.5 , 2) + pow(x2 + 0.5 , 2) < 0.2){
		if(x2 > -0.5)
			return 1;
		else
			return 2;
	}
	else if(pow(x1 + 0.5 , 2) + pow(x2 - 0.5 , 2) < 0.2){
		if(x2 > 0.5)
			return 1;
		else
			return 2;
	}
	else
		return 3;
}

void createRandomData(){
	float scale, x1, x2;
	int category;
	FILE *f;
	f = fopen("data.txt", "w");
	if(f == NULL){
    	printf("Error opening file!\n");
    	exit(1);
	}
	for(int i = 0; i < N; i++){  
        scale = rand() / (float) RAND_MAX;   
		x1 = scale * (MAX - MIN) + MIN;
		scale = rand() / (float) RAND_MAX;
		x2 = scale * (MAX - MIN) + MIN;
		category = getCategory(x1, x2);
		fprintf(f, "%f %f %d\n", x1 ,x2, category);
	}
	fclose(f);
 }
 
 int main(){
	srand(time(NULL));
	createRandomData();
	return 0;
}