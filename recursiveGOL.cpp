/*
 * recursiveGOL.cpp
 *
 *  Created on: Apr 18, 2021
 *      Author: Sean
 *
 * Modified from: sequentialGOL.cpp, by thomas
 *
 * Compile as: g++ -fopenmp recursiveGOL.cpp Board.cpp Cell.cpp -o rGOL
 */


#include <iostream>
#include <omp.h>
#include <time.h>
#include <string>
#include <cstddef>

#include "Board.h"
#include "Cell.h"

using namespace std;


void divideBoard(Board &, int, int, int);

/*
 * Arguments:
 * ./executable
 * dimension of array (if dimension = 8, size = 64)
 * number of iterations
 * initial density of live cells (a percentage from 1 to 100)
 * number of threads to run
 * [optional] number of partitions made per recursive step
 * 
 */

int main(int argc, char * argv[]){

	if (argc < 5 || argc > 6){
		cerr << "Must provide arguments" << endl;
		return -1;
	}

	int dimension = atoi(argv[1]);
	int numIterations = atoi(argv[2]);
	int density = atoi(argv[3]);
    int partitions;
    int numThreads = atoi(argv[4]);

    if (argc == 5) {
        partitions = dimension;
    } else {
        partitions = atoi(argv[5]);
    }

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

        divideBoard(board, 0, board.getSize(), partitions);

    	if (i == numIterations - 1){
    		end = omp_get_wtime();
    	}


		board.updateBoard();

		board.display();

	}

	double time = end - begin;
	cout << "Runtime taken for simulation to finish: " << time << " seconds" << endl;

}

void divideBoard(Board &board, int start, int end, int partitions) {

    if (end - start == 1) {
        // base case
        Cell* currCell = board.getElementAtIndex(start);

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
	    }
    } else {
        int p = partitions;
        bool done = false;
        do {
            if(end - start >= p) {
                int size = (end - start) / p;
		#pragma omp parallel for
                for(int i = 0; i < p; i ++) {
                    if (i+1 < p) {
                        divideBoard(board, start + (i * size), start + ((i + 1) * size), p);
                    } else {
                        divideBoard(board, start + (i * size), end, p);
                    }
                }
                done = true;
            } else {
                p /= 2;
            }
        } while(!done);
    }
}

