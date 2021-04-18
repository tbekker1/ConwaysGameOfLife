/*
 * Cell.h
 *
 *  Created on: Apr 17, 2021
 *      Author: thomas
 */

#ifndef CELL_H_
#define CELL_H_

class Cell {
public:
	Cell();
	void init(int x, int y);
	void setaliveNow(bool aliveNow);
	bool getaliveNow();

	void setaliveNextCycle(bool aliveNextCycle);
	bool getaliveNextCycle();

	int getxCoord();
	int getyCoord();

private:
	bool m_aliveNow;
	bool m_aliveNextCycle;
	int m_x;
	int m_y;
};

#endif /* CELL_H_ */
