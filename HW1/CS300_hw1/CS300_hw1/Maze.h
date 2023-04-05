#include <vector>
#include "Stack.h"
#include <string>
#include "stdlib.h"
#include <fstream>

using namespace std;


struct Cell {
	int left, right, up, down;
	int coordX, coordY;
	Cell() :left(1), right(1), up(1), down(1), coordX(0), coordY(0) {}
	Cell(int cor1, int cor2):left(1), right(1), up(1), down(1) ,coordX(cor1), coordY(cor2){}
};


class Maze
{
public:
	Maze(int X, int Y);

	
	bool isCellConvinient(Cell& cell_checking, const string& direc);
	bool oneCellConvinient(Cell& cell_checking, const string& direc); 

	
	bool DetailedStackChecker(int coordX, int coordY);

	void fillingOriginal();
	void PrintMaze(ofstream & write);

	int CountAppropriateCell(int coordX, int coordY);

	
	void ifNoneAppropriateCell(string prevdirection);
	void moveCurrent(int dx, int dy);
	void cellProcessing(int cor1, int cor2, string direc);
	int randomGenerator();

	void PathFinding(ofstream& write, int eX, int eY, int oX, int oY);
	int randomGeneratorPathfinding();
	int existConvinientCellPathfinding(int corX, int corY);
	void whenNoneConvinientCellPathfinding();
	void PrintFunctionPathfinding(ofstream& Write);
	bool DetailedPathfinding(int coordX, int coordY);
	void fillingOriginalPathfinding();
	bool oneCellConvinientPathfinding(Cell& cell_checking, const string& direc);

private:
	int M , N, entX, entY, outX, outY;
	
	int currentX , currentY  , BrokenWalls;

	vector<vector<Cell>> VecCell; 
	Stack<Cell> OurMAINStack, OurOtherStack, OurMAINPathStack, OurOtherPathStack;
	Stack<string> stringStack, stringStackPath;

};