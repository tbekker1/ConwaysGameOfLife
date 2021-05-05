/*****************************************************************
 * File: Board2.h
 * Author: Sean Elia
 * 
 * An alternate implimentation of the Board class created by Thomas
******************************************************************/ 
#ifndef BOARD2_H_483
#define BOARD2_H_483

#include "Cell.h"
#include "timer.h"

class Board2 {
public:
	Board2(int dimension);
	Cell* next(Cell* cell);
	void init(int density);
	void updateBoard();
	int getAliveNeighborCount(Cell* cell);
	int getSize();
	int getDim();
	Cell* getElementAtIndex(int index);
	void display();
    virtual void nextStep() = 0;
protected:
	int getIndex(int x, int y);
	int aliveOrNot(int x, int y);
	int m_size;
	int m_dimension;
	Cell* m_board;
    timer m_timer;
};

#endif /* BOARD_2_H_483 */
