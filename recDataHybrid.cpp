/*
 * recDataHybrid.cpp
 *
 *
 * Author: Thomas
 *
 * Modified from: recursiveGOL.cpp by Sean and dataGOL.cpp by Thomas
 *
 * Compile as: g++ -fopenmp recDataHybrid.cpp Board.cpp Cell.cpp -o h1GOL
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
void dataAlgorithm(Board &, int, int);
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

    if (end - start <= 10) {
        // base case
    		int length = end - start / partitions;
    		//call data algorithm with this partition
    		dataAlgorithm(board, start, length);
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


void dataAlgorithm(Board &board, int start, int length){
		Cell* aliveCells[length];
		Cell* deadCells[length];
		int aliveNumber = 0;
		int deadNumber = 0;

		for (int i = start; i < length; i++){
			Cell* currCell = board.getElementAtIndex(i);

			if (currCell->getaliveNow() == true){
				aliveCells[aliveNumber] = currCell;
				aliveNumber++;
			}
			else{
				deadCells[deadNumber] = currCell;
				deadNumber++;
			}
		}


#pragma omp parallel for schedule(static)
		for (int j = 0; j < aliveNumber; j++){
			Cell* currCell = aliveCells[j];

			int neighborCount = board.getAliveNeighborCount(currCell);

			switch(neighborCount){
			case 2:
			case 3:
				currCell->setaliveNextCycle(true);
				break;

			default:
				currCell->setaliveNextCycle(false);
				break;
			}

		}

#pragma omp parallel for schedule(static)
		for (int j = 0; j < deadNumber; j++){
			Cell* currCell = deadCells[j];

			int neighborCount = board.getAliveNeighborCount(currCell);

			switch(neighborCount){
				case 3:
					currCell->setaliveNextCycle(true);
					break;

				default:
					currCell->setaliveNextCycle(false);
					break;
			}
		}

}

