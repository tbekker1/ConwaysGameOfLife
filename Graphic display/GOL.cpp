/**********************************************************************
 * File: GOL.cpp
 * Author: Sean Elia
 * 
 * Class implimentations of all GOL algorithms
**********************************************************************/
#include "GOL.h"

// ----------------------- Sequential Algorithm -----------------------
void sGOL::nextStep() {
    auto start = std::chrono::high_resolution_clock::now();
    calc();
    auto end = std::chrono::high_resolution_clock::now();
    m_timer.addTime((end-start).count());
}

void sGOL::calc() {
for (int j = 0; j < this->getSize(); j++){
	Cell* currCell = this->getElementAtIndex(j);

	int neighborCount = this->getAliveNeighborCount(currCell);

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
}


// ----------------------- Recursive Algorithm ------------------------
void rGOL::nextStep() {
    auto start = std::chrono::high_resolution_clock::now();
    divideBoard(0, this->getSize(), m_partition);    
    auto end = std::chrono::high_resolution_clock::now();
    m_timer.addTime((end-start).count());
}

void rGOL::divideBoard(int start, int end, int partitions) {
    if (end - start == 1) {
        // base case
        Cell* currCell = this->getElementAtIndex(start);

        int neighborCount = this->getAliveNeighborCount(currCell);

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
                        divideBoard(start + (i * size), start + ((i + 1) * size), p);
                    } else {
                        divideBoard(start + (i * size), end, p);
                    }
                }
                done = true;
            } else {
                p /= 2;
            }
        } while(!done);
    }
}