// TO COMPILE:
// g++ -fopenmp display.cpp GOL.cpp Board.cpp Cell.cpp -o GOL

// TO RUN:
// GOL [argument list]
// -se -re -da -sp -h1 -h2

#define OLC_PGE_APPLICATION
#include <iostream>
#include <omp.h>
#include <time.h>
#include <string>
#include <cstddef>

#include "olcPixelGameEngine.h"
#include "Cell.h"
#include "Board2.h"
#include "GOL.h"

using namespace std;

class Display : public olc::PixelGameEngine {
    public:
	Display(Board2* gol, int numIterations) {
		sAppName = "Game of Life Display";
		m_gol = gol;
		m_iter = numIterations;
	}

	int calcIndex(int x, int y) {
		int row = x / (int)(ScreenWidth() / m_gol->getDim());
		int col = y / (int)(ScreenHeight() / m_gol->getDim());

		return row * m_gol->getDim() + col;
	}

	void drawBoard() {
		for (int x = 0; x < ScreenWidth(); x++) {
			for (int y = 0; y < ScreenHeight(); y++) {
				// has the wrong indexing logic, WIP
				if (m_gol->getElementAtIndex(calcIndex(x, y))->getaliveNow()) {
					Draw(x, y, olc::Pixel(255, 255, 255));
				} else {
					Draw(x, y, olc::Pixel(0, 0, 0));
				}
			}
		}
	}

	bool OnUserCreate() override {
		drawBoard();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		this_thread::sleep_for(50ms);
		
		// called once per 50 milliseconds
		if (m_iter > 0) {
			m_iter --;
			m_gol->nextStep();
			m_gol->updateBoard();
			drawBoard();
		}
		return true;
	}

    private:
    Board2 * m_gol;
	int m_iter;
};


int main(int argc, char * argv[]){

	if (argc != 4) {
		cerr << "Must provide arguments" << endl;
		return -1;
	}

	int dimension = atoi(argv[1]);
	int numIterations = atoi(argv[2]);
	int density = atoi(argv[3]);

	if (density < 1 || density > 100) {
		cerr <<"Density percentage must be between 1 and 100" << endl;
		return -1;
	}

	Board2* board = new sGOL(dimension);
	board->init(density);

	Display gol(board, numIterations);
	if (gol.Construct(1024, 1024, 1, 1)) {
		gol.Start();
	}

	delete board;
	return 0;
}
