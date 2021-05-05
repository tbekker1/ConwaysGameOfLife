/*****************************************************************
 * File: GOL.h
 * Author: Sean Elia
 * 
 * Class implimentations of all GOL algorithms
******************************************************************/
#include <chrono>
#include <omp.h>

#include "Board2.h"

// sequential algorithm: initialy developed by Thomas
#ifndef SGOL_H_483
#define SGOL_H_483
class sGOL : public Board2 {
    public:
    sGOL(int dimension) : Board2(dimension) 
    {/* no additional implimentation needed for constructor*/}
    void nextStep();

    private:
    void calc();
};
#endif

// recutsive algorithm: initialy developed by Sean
#ifndef RGOL_H_483
#define RGOL_H_483
class rGOL : public Board2 {
    public:
    rGOL(int dimension, int partition) : Board2(dimension) 
    {this->m_partition = partition;}
    void nextStep();

    private:
    void divideBoard(int, int, int);
    int m_partition;
};
#endif