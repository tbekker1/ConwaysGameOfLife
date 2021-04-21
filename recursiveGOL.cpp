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
 * [optional] number of partitions made per recursive step
 * 
 */


int main(int argc, char * argv[]){

	if (argc < 4 || argc > 5){
		cerr << "Must provide arguments" << endl;
		return -1;
	}

	int dimension = atoi(argv[1]);
	int numIterations = atoi(argv[2]);
	int density = atoi(argv[3]);
    int partitions;
    if (argc == 4) {
        partitions = dimension;
    } else {
        partitions = atoi(argv[4]);
    }

	if (density < 1 || density > 100){
		cerr <<"Density percentage must be between 1 and 100" << endl;
		return -1;
	}

	Board board(dimension);
	board.init(density);

	board.display();

	for (int i = 0; i < numIterations; i++){

        divideBoard(board, 0, board.getSize(), partitions);

		board.updateBoard();

		board.display();
	}

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
		#pragma omp for
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

