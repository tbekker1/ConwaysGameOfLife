/*
 * speculativeGOL.cpp
 *
 *  Created on: Apr 21, 2021
 *      Author: thomas
 *
 * Compile as: g++ -fopenmp speculativeGOL.cpp Board.cpp Cell.cpp -o specGOL
 */

#include <iostream>
#include <omp.h>
#include <time.h>
#include <string>
#include <cstddef>

#include "Board.h"
#include "Cell.h"

using namespace std;


/*
 * Arguments:
 * ./executable
 * dimension of array (if dimension = 8, size = 64)
 * number of iterations
 * initial density of live cells (a percentage from 1 to 100)
 * number of threads to run
 */


int main(int argc, char * argv[]){

	if (argc != 5){
		cerr << "Must provide arguments" << endl;
		return -1;
	}

	int dimension = atoi(argv[1]);
	int numIterations = atoi(argv[2]);
	int density = atoi(argv[3]);
	int numThreads = atoi(argv[4]);

	if (density < 1 || density > 100){
		cerr <<"Density percentage must be between 1 and 100" << endl;
		return -1;
	}

	omp_set_num_threads(numThreads);

	Board board(dimension);
	board.init(density);

	board.display();


	double begin;
	double end;

	begin = omp_get_wtime();

	for (int i = 0; i < numIterations; i++){

#pragma omp parallel for schedule(static)
		for (int j = 0; j < board.getSize(); j++){
			Cell* currCell = board.getElementAtIndex(j);

			int neighborCount = board.getAliveNeighborCount(currCell);

			switch(neighborCount){
			case 2:
				currCell->setaliveNextCycle(currCell->getaliveNow());
				break;

			case 3:
				currCell->setaliveNextCycle(true);
				break;

			default:
				currCell->setaliveNextCycle(false);
				break;

			}
		}

		if (i == numIterations - 1){
			end = omp_get_wtime();
		}

		board.updateBoard();

		board.display();

	}

	double time = end - begin;
	cout << "Runtime taken for simulation to finish: " << time << " seconds" << endl;
}



