
#include <cuda.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include<iostream>

using namespace std;

// compute vector sum C = A+B
// each thread performs one pair-wise addition
__global__ // executed on the device, only callable from the host
void vecAddKernel(float *A, float *B, float *C, int n) {
	int i = blockDim.x * blockIdx.x + threadIdx.x;
	
	if (i < n) {
		C[i] = A[i] + B[i];
	}
}

// Compute vector sum h_C = h_A + h_B
void vecAdd(float *h_A, float *h_B, float *h_C, int n) {
	 
	// calculate the sum with a simple for loop
	/***************************
	*for (int i = 0; i < 100; i++)
	*	h_C[i] = h_A[i] + h_B[i];
	****************************/

	int size = n*sizeof(float);
	float *d_A, *d_B, *d_C;

	//1. Allocate global memory on the device for A, B and C
	cudaMalloc((void**)&d_A, size);
	cudaMalloc((void**)&d_B, size);
	cudaMalloc((void**)&d_C, size);

	// copy A and B to device memory
	cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

	//2. Kernel launch code - to have the device to perform the actual vector addition
	// Kernel invocation with 256 threads

	vecAddKernel<<<ceil(n/256.0), 256>>>(d_A, d_B, d_C, n);

	//3. copy C from the device memory
	cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

	// Free device vectors
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);
}

int main(void) {

	// create and host vectors
	float *h_A, *h_B, *h_C;
	int n = 2000000;

	// allocate memory for host vectors
	h_A = (float*)malloc(sizeof(float)*n);
	h_B = (float*)malloc(sizeof(float)*n);
	h_C = (float*)malloc(sizeof(float)*n);
	
	// fill A and B host vectors with a simple for loop
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		h_A[i] = ((((float)rand() / (float)(RAND_MAX)) * 100));
		h_B[i] = ((((float)rand() / (float)(RAND_MAX)) * 100));
	}
    cout<<"\n\nvectorA=";
    for (int i = 0; i < n; i++) {
		cout<< h_A[i] << " " ;
	}
    cout<<"\n\n\nvectorB=";
    for (int i = 0; i < n; i++) {
		cout<< h_B[i] ;
	}
	// call vecAdd to compute vector sum
	vecAdd(h_A, h_B, h_C, n);
    cout<<"\n\n\nvectorC=";
    for (int i = 0; i < n; i++) {
		cout<< h_C[i] ;
	}
	// check the result
	bool valid = true;
	for (int i = 0; i < n; i++) {
		if (h_A[i] + h_B[i] != h_C[i])
			valid = false;
			break;
	}

	if (!valid)
		printf("the result is not correct\n!");
	else
		printf("ok sum completed with success!\n");

	// Free host memory
	free(h_A);
	free(h_B);
	free(h_C);


	return 0;
}