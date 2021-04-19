/*
 * Board.h
 *
 *  Created on: Apr 17, 2021
 *      Author: thomas
 */
#include "Cell.h"

#ifndef BOARD_H_
#define BOARD_H_

class Board {
public:
	Board(int dimension);
	Cell* next(Cell* cell);
	void init(int density);
	void updateBoard();
	int getAliveNeighborCount(Cell* cell);
	int getSize();
	Cell* getElementAtIndex(int index);
	void display();
private:
	int getIndex(int x, int y);
	int aliveOrNot(int x, int y);
	int m_size;
	int m_dimension;
	Cell* m_board;
};

#endif /* BOARD_H_ */
