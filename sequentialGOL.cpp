/*
 * sequentialGOL.cpp
 *
 *  Created on: Apr 17, 2021
 *      Author: thomas
 */

#include <iostream>
#include <omp.h>
#include <time.h>
#include <string>
#include <cstddef>

using namespace std;


/*
 * Arguments:
 * ./executable
 * dimension of array (if dimension = 8, size = 64)
 * number of iterations
 * initial density of live cells (a percentage from 1 to 100)
 *
 */
int main(int argc, char * argv[]){

	if (argc != 4){
		cerr << "Must provide arguments" << endl;
		return -1;
	}

	int dimension = atoi(argv[1]);
	int numIterations = atoi(argv[2]);
	int density = atoi(argv[3]);

	if (density < 1 || density > 100){
		cerr <<"Density percentage must be between 1 and 100" << endl;
		return -1;
	}

	Board board(dimension);


}


