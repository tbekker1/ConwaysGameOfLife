/*
 * Cell.cpp
 *
 *  Created on: Apr 17, 2021
 *      Author: thomas
 */

#include "Cell.h"

Cell::Cell(){


}

void Cell::init(int coord1, int coord2) {
	// TODO Auto-generated constructor stub
	m_x = coord1;
	m_y = coord2;
	m_aliveNow = false;
	m_aliveNextCycle = false;

}

void Cell::setaliveNow(bool val){
	m_aliveNow = val;
}

bool Cell::getaliveNow(){
	return m_aliveNow;
}

void Cell::setaliveNextCycle(bool val){
	m_aliveNextCycle = val;
}

bool Cell::getaliveNextCycle(){
	return m_aliveNextCycle;
}

int Cell::getxCoord(){
	return m_x;
}

int Cell::getyCoord(){
	return m_y;
}



