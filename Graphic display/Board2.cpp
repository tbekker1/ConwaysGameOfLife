/*****************************************************************
 * File: Board2.cpp
 * Author: Sean Elia
 * 
 * An alternate implimentation of the Board class created by Thomas
******************************************************************/ 
#include "Board2.h"
#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <time.h>

using namespace std;

Board2::Board2(int dimension) {
	m_dimension = dimension;
	m_size = dimension * dimension;
	m_board = new Cell[m_size];

	for (int i = 0; i < m_dimension; i++){
		for (int j = 0; j < m_dimension; j++){
			m_board[getIndex(i,j)].init(i,j);
		}
	}

}

Cell* Board2::next(Cell* cell){

	if (cell == NULL){
		return &m_board[0];
	}

	int cellIndex = getIndex(cell->getxCoord(), cell->getyCoord());

	if (cellIndex == -1 || cellIndex == m_size - 1){
		return NULL;
	}

	return &m_board[cellIndex + 1];

}

//returns index into an array. If not a valid input, return -1
int Board2::getIndex(int x, int y){

	 if ((x < 0 || x > m_dimension - 1) || (y < 0 || y > m_dimension - 1)){
	    return -1;
	  }

	 int index = (x * m_dimension + y);
	 return index;
}


void Board2::init(int density){

	Cell* cell = next(NULL);
	srand(time(NULL));
	do{
		int randNum = rand() % 100;
		if (randNum < density){
			cell->setaliveNow(true);
		}
		else{
			cell->setaliveNow(false);
		}
		cell = next(cell);

	}while(cell != NULL);

}

void Board2::updateBoard(){
	Cell* cell = next(NULL);

	while(cell != NULL){
		cell->setaliveNow(cell->getaliveNextCycle());
		cell->setaliveNextCycle(false);
		cell = next(cell);
	}

}

int Board2::getAliveNeighborCount(Cell* cell){
	int count = 0;
	count += aliveOrNot(cell->getxCoord() - 1,cell -> getyCoord() - 1);
	count += aliveOrNot(cell->getxCoord()    ,cell -> getyCoord() - 1);
	count += aliveOrNot(cell->getxCoord() + 1,cell -> getyCoord() - 1);
	count += aliveOrNot(cell->getxCoord() - 1,cell -> getyCoord());
	count += aliveOrNot(cell->getxCoord() + 1,cell -> getyCoord());
	count += aliveOrNot(cell->getxCoord() - 1,cell -> getyCoord() + 1);
	count += aliveOrNot(cell->getxCoord()    ,cell -> getyCoord() + 1);
	count += aliveOrNot(cell->getxCoord() + 1,cell -> getyCoord() + 1);

	return count;

}

int Board2::aliveOrNot(int x, int y){

	int index = getIndex(x, y);
	if (index < 0){
		return 0;
	}

	if (m_board[index].getaliveNow() == true){
		return 1;
	}

	else{
		return 0;
	}
}

int Board2::getSize(){
	return m_size;
}

int Board2::getDim(){
	return m_dimension;
}

Cell* Board2::getElementAtIndex(int index){

	if (index < 0 || index >= m_size){
		return NULL;
	}

	return &m_board[index];
}


void Board2::display(){

	for (int i = 0; i < m_size; i++){

		Cell* currCell = getElementAtIndex(i);

		if (currCell->getaliveNow() == true){
			cout << '*';
		}

		else{
			cout << '-';
		}

		if ((i + 1) % m_dimension == 0){
			cout << endl;
		}

	}

	cout << endl;
}


