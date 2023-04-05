#include "Maze.h"
#include "Stack.h"
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <assert.h>

using namespace std;

Maze::Maze(int X, int Y) {  //Maze constructor and it generates a random maze
    M = X;
    N = Y;
    currentX = 0;
    currentY = 0;
    VecCell.resize(M);
    for (int i = 0; i < M; i++) {
        VecCell[i].resize(N);
        for (int j = 0; j < N; j++) {
            VecCell[i][j].coordX = i;
            VecCell[i][j].coordY = j;
        }
    }
    
    for (int i = 0; i < M; i++) {
        VecCell[i][0].left = 1;
        VecCell[i][N - 1].right = 1;
    }
    for (int j = 0; j < N; j++) {
        VecCell[0][j].up = 1;
        VecCell[M - 1][j].down = 1;
    }

    int c = rand() % 2;
    BrokenWalls = 0;
    string direc;
    OurMAINStack.push(VecCell[0][0]);

    if (M == 1 && N == 1) {
        return;
    }
    while (BrokenWalls < M * N - 1) {
        if (CountAppropriateCell(currentX, currentY)) {
            c = randomGenerator();
            switch (c) {
                case 0: isCellConvinient(VecCell[currentX][currentY], "left"); break;
                case 1: isCellConvinient(VecCell[currentX][currentY], "right"); break;
                case 2: isCellConvinient(VecCell[currentX][currentY], "up"); break;
                case 3: isCellConvinient(VecCell[currentX][currentY], "down"); break;
            }
        }
        else {
            ifNoneAppropriateCell(stringStack.top());
        }
    }
}

bool Maze::isCellConvinient(Cell& cell_checking, const string& direc)  //is the cell convinient to be included to the maze
{
    int x = cell_checking.coordX;
    int y = cell_checking.coordY;
    
    
    if (direc == "up" && y + 1 < N) {
        y++;
    }
    else if (direc == "down" && y - 1 >= 0) {
        y--;
    }
    else if (direc == "left" && x - 1 >= 0) {
        x--;
    }
    else if (direc == "right" && x + 1 < M) {
        x++;
    }
    else {
        return false;
    }
    
    
    if (DetailedStackChecker(x, y)) {
        return false;
    }
    
    
    if (direc == "up") {
        cell_checking.up = 0;
        VecCell[x][y].down = 0;
    }
    else if (direc == "down") {
        cell_checking.down = 0;
        VecCell[x][y].up = 0;
    }
    else if (direc == "left") {
        cell_checking.left = 0;
        VecCell[x][y].right = 0;
    }
    else if (direc == "right") {
        cell_checking.right = 0;
        VecCell[x][y].left = 0;
    }
    
    OurMAINStack.push(VecCell[x][y]);
    stringStack.push(direc);
    cellProcessing(cell_checking.coordX, cell_checking.coordY, direc);
    
    return true;
}


bool Maze::oneCellConvinient(Cell& cell_checking, const string& direc) { //does nothing but returns bool
    switch (direc[0]) {
        case 'u':
            return cell_checking.coordY + 1 < N && DetailedStackChecker(cell_checking.coordX, cell_checking.coordY + 1);
        case 'd':
            return cell_checking.coordY - 1 >= 0 && DetailedStackChecker(cell_checking.coordX, cell_checking.coordY - 1);
        case 'l':
            return cell_checking.coordX - 1 >= 0 && DetailedStackChecker(cell_checking.coordX - 1, cell_checking.coordY);
        case 'r':
            return cell_checking.coordX + 1 < M && DetailedStackChecker(cell_checking.coordX + 1, cell_checking.coordY);
    }
    return false;
}

bool Maze::DetailedStackChecker(int coordX, int coordY) //is given cell already in the stack?

{
	Cell popped;
	int counter = 0;
	
	while (!OurMAINStack.isEmpty()) {
		popped = OurMAINStack.topAndPop();
		OurOtherStack.push(popped);
		counter++;
		if ((coordX == popped.coordX && coordY == popped.coordY)) {
			
			while (counter > 0) {
				OurMAINStack.push(OurOtherStack.topAndPop());
				counter--;
			}
			return false;
		}
	}
	
	
	while (counter > 0) {
		OurMAINStack.push(OurOtherStack.topAndPop());
		counter--;
	}
	
	return true;
}


void Maze::fillingOriginal()  //filling the orijinal maze stack
{
    if (OurOtherStack.isEmpty()) {
        return;
    }
    
    Cell poppedCell = OurOtherStack.topAndPop();
    OurMAINStack.push(poppedCell);
    fillingOriginal();
}


void Maze::PrintMaze(ofstream& write) {  //Printing the maze stack
    write << M << " " << N << endl;
    for (auto it = VecCell.begin(); it != VecCell.end(); ++it) {
        for (auto jt = it->begin(); jt != it->end(); ++jt) {
            write << "x=" << jt->coordX << " y=" << jt->coordY << " l=" << jt->left
                    << " r=" << jt->right << " u=" << jt->up << " d=" << jt->down << endl;
        }
    }
    write.close();
}


int Maze::CountAppropriateCell(int corX, int corY)   // counts the number of neighbor cells around the given coordinates in the maze that satisfy a certain condition
{
    int count = 0;

    count += (corX + 1 < M && DetailedStackChecker(corX + 1, corY)) ? 1 : 0;
    count += (corX - 1 >= 0 && DetailedStackChecker(corX - 1, corY)) ? 1 : 0;
    count += (corY - 1 >= 0 && DetailedStackChecker(corX, corY - 1)) ? 1 : 0;
    count += (corY + 1 < N && DetailedStackChecker(corX, corY + 1)) ? 1 : 0;

    return count;
}



void Maze::ifNoneAppropriateCell(string predirec) //is called when there are no appropriate neighboring cells around the current cell
{
	stringStack.pop();
	if (predirec == "left") {
		moveCurrent(1, 0);
	}
	else if (predirec == "right") {
		moveCurrent(-1, 0);
	}
	else if (predirec == "up") {
		moveCurrent(0, -1);
	}
	else if (predirec == "down") {
		moveCurrent(0, 1);
	}
}


void Maze::moveCurrent(int dx, int dy) { //helper func of ifNoneAppropriateCell(string predirec)
	currentX += dx;
	currentY += dy;
}



void Maze::cellProcessing(int coord1, int coord2, string direc) //updating the maze by breaking walls
{
	if (direc == "up") {
		VecCell[coord1][coord2].up = 0;
		VecCell[coord1][coord2+1].down = 0;
		currentY = currentY+1;
		BrokenWalls++;
	}
	else if (direc == "down") {
		VecCell[coord1][coord2].down = 0;
		VecCell[coord1][coord2 - 1].up = 0;
		currentY = currentY-1;
		BrokenWalls++;
	}
	else if (direc == "right") {
		VecCell[coord1][coord2].right = 0;
		VecCell[coord1+1][coord2 ].left = 0;
		currentX = currentX+1;
		BrokenWalls++;
	}
	else if (direc == "left") {
		VecCell[coord1][coord2].left = 0;
		VecCell[coord1 - 1][coord2].right = 0;
		currentY = currentY-1;
		BrokenWalls++;
	}
}


int Maze::randomGenerator()  // generates a random number that represents a direction to move in the maze
{
    int t = CountAppropriateCell(currentX, currentY);
	string directions[] = {"left", "right", "up", "down"};
    vector<int> valid_directions;

    for (int i = 0; i < 4; i++) {
        if (oneCellConvinient(VecCell[currentX][currentY], directions[i])) {
            valid_directions.push_back(i);
        }
    }

    int num_valid_directions = valid_directions.size();

    if (num_valid_directions == 4) {
        return rand() % 4;
    }
    else if (num_valid_directions == 3) {
        for (int i = 0; i < 4; i++) {
            if (!oneCellConvinient(VecCell[currentX][currentY], directions[i])) {
                return i;
            }
        }
    }
    else if (num_valid_directions == 2) {
        int first_direction = valid_directions[0];
        int second_direction = valid_directions[1];

        if ((first_direction == 0 && second_direction == 1) || (first_direction == 1 && second_direction == 0)) {
            return rand() % 2 == 0 ? 0 : 1;
        }
        else if ((first_direction == 0 && second_direction == 2) || (first_direction == 2 && second_direction == 0)) {
            return rand() % 2 == 0 ? 0 : 2;
        }
        else if ((first_direction == 0 && second_direction == 3) || (first_direction == 3 && second_direction == 0)) {
            return rand() % 2 == 0 ? 0 : 3;
        }
        else if ((first_direction == 1 && second_direction == 2) || (first_direction == 2 && second_direction == 1)) {
            return rand() % 2 == 0 ? 1 : 2;
        }
        else if ((first_direction == 1 && second_direction == 3) || (first_direction == 3 && second_direction == 1)) {
            return rand() % 2 == 0 ? 1 : 3;
        }
        else {
            return rand() % 2 == 0 ? 2 : 3;
        }
    }
    else if (num_valid_directions == 1) {
        return valid_directions[0];
    }
    
    assert(false);
}



void Maze::PathFinding(ofstream& write, int pathFEntryX, int pathFEntryY, int pathFOutX, int pathFOutY)  //finding a path from the entrance to the exit of the maze.
{
    currentX = entX;
    currentY = entY;
    OurMAINPathStack.push(VecCell[currentX][currentY]);
    
    int c;
    while (currentX != outX || currentY != outY) {
        if (existConvinientCellPathfinding(currentX, currentY)) {
            c = randomGeneratorPathfinding();
			string directions[] = {"left", "right", "up", "down"};
			for (const auto& direction : directions)
			{
                if (oneCellConvinientPathfinding(VecCell[currentX][currentY], direction)) {
                    if (direction == "left") {
                        OurMAINPathStack.push(VecCell[--currentX][currentY]);
                        stringStackPath.push(direction);
                    }
                    else if (direction == "right") {
                        OurMAINPathStack.push(VecCell[++currentX][currentY]);
                        stringStackPath.push(direction);
                    }
                    else if (direction == "up") {
                        OurMAINPathStack.push(VecCell[currentX][++currentY]);
                        stringStackPath.push(direction);
                    }
                    else if (direction == "down") {
                        OurMAINPathStack.push(VecCell[currentX][--currentY]);
                        stringStackPath.push(direction);
                    }
                    break;
                }
            }
        }
        else {
            whenNoneConvinientCellPathfinding();
        }
    }
    PrintFunctionPathfinding(write);
    write.close();
}


int Maze::randomGeneratorPathfinding() {  //generates a random direction for the pathfinding algorithm to move in
    
	int t = existConvinientCellPathfinding(currentX, currentY);
    int directions[4] = {-1, -1, -1, -1}; // initialize all directions to -1
    
    // set directions array with applicable directions
    if (oneCellConvinientPathfinding(VecCell[currentX][currentY], "left")) {
        directions[0] = 0;
    }
    if (oneCellConvinientPathfinding(VecCell[currentX][currentY], "right")) {
        directions[1] = 1;
    }
    if (oneCellConvinientPathfinding(VecCell[currentX][currentY], "up")) {
        directions[2] = 2;
    }
    if (oneCellConvinientPathfinding(VecCell[currentX][currentY], "down")) {
        directions[3] = 3;
    }
    
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (directions[i] != -1) {
            count++;
        }
    }
    
    if (count == 3) {
        int index;

        do {
            index = rand() % 4;
        } while (directions[index] == -1);

        return directions[index];

    } else if (count == 2) {
        int index1, index2;
        
		do {
            index1 = rand() % 4;
        } while (directions[index1] == -1);
        
		do {
            index2 = rand() % 4;
        } while (directions[index2] == -1 || index2 == index1);
        
        if (index1 == 0 && index2 == 1 || index1 == 1 && index2 == 0) {
            return rand() % 2;

        } else if (index1 == 0 && index2 == 2 || index1 == 2 && index2 == 0) {
            int choices[2] = {0, 2};
            return choices[rand() % 2];
        } else if (index1 == 0 && index2 == 3 || index1 == 3 && index2 == 0) {
            return 1 + rand() % 2;
        } else if (index1 == 1 && index2 == 2 || index1 == 2 && index2 == 1) {
            return 2 + rand() % 2;
        } else if (index1 == 1 && index2 == 3 || index1 == 3 && index2 == 1) {
            return index1;
        } else if (index1 == 2 && index2 == 3 || index1 == 3 && index2 == 2) {
            int choices[2] = {1, 3};
            return choices[rand() % 2];
        }
    } else if (count == 1) {
        for (int i = 0; i < 4; i++) {
            if (directions[i] != -1) {
                return directions[i];
            }
        }
    }
    
    assert("Error t=100 \n\n", t != INT_MAX);
    return INT_MAX;
}



int Maze::existConvinientCellPathfinding(int coordX, int coordy) //checks whether there exists at least one cell adjacent to the current cell that can be used for pathfinding
{
	int count = 0;
	if (coordX + 1 < M && VecCell[coordX][coordy].right == 0 && DetailedPathfinding(coordX + 1, coordy))
		count++;
	if (coordX - 1 >= 0 && VecCell[coordX][coordy].left == 0 && DetailedPathfinding(coordX - 1, coordy))
		count++;
	if (coordy - 1 >= 0 && VecCell[coordX][coordy].down == 0 && DetailedPathfinding(coordX, coordy - 1))
		count++;
	if (coordy + 1 < N && VecCell[coordX][coordy].up == 0 && DetailedPathfinding(coordX, coordy + 1))
		count++;

	return count;
}

void Maze::whenNoneConvinientCellPathfinding()  // when the current cell has no convenient neighbor cells to move to
{
    string previous = stringStackPath.topAndPop();
    
    switch (previous[0])
    {
        case 'l':
            currentX++;
            break;
            
        case 'r':
            currentX--;
            break;
            
        case 'u':
            currentY--;
            break;
            
        case 'd':
            currentY++;
            break;
    }
}

//RECURSIVE
void Maze::PrintFunctionPathfinding(ofstream& Write) //prints the coordinates of the cells in the main path from the starting point to the ending point of the maze.
{
    if (OurMAINPathStack.isEmpty())
        return;
        
    while (!OurMAINPathStack.isEmpty()) {
        int x = OurMAINPathStack.topOfStack->element.coordX;
        int y = OurMAINPathStack.topOfStack->element.coordY;
        OurMAINPathStack.pop();
        Write << x << " " << y << endl;
    }
}



bool Maze::oneCellConvinientPathfinding(Cell& cell_checking, const string& direc)  //The function returns true if the resulting cell is reachable and false otherwise.
{
    int dx = 0, dy = 0;
    if (direc == "up")    dy =  1;
    if (direc == "down")  dy = -1;
    if (direc == "left")  dx = -1;
    if (direc == "right") dx =  1;

    if (cell_checking.coordX + dx < 0 || cell_checking.coordX + dx >= M ||
        cell_checking.coordY + dy < 0 || cell_checking.coordY + dy >= N)
        return false;

    if (dx != 0) {
        if (dx == -1 && VecCell[currentX][currentY].left != 0) return false;
        if (dx ==  1 && VecCell[currentX][currentY].right != 0) return false;
        return DetailedPathfinding(cell_checking.coordX + dx, cell_checking.coordY);
    }
    else {
        if (dy == -1 && VecCell[currentX][currentY].down != 0) return false;
        if (dy ==  1 && VecCell[currentX][currentY].up != 0) return false;
        return DetailedPathfinding(cell_checking.coordX, cell_checking.coordY + dy);
    }
}


bool Maze::DetailedPathfinding(int coordX, int coordY)  // find a path from the current cell to a target cell in the maze
{
    if (OurMAINPathStack.isEmpty()) {
        fillingOriginalPathfinding();
        return true;
    }
    
    Cell poppedCell = OurMAINPathStack.topAndPop();
    OurOtherPathStack.push(poppedCell);
    
    if (coordX == poppedCell.coordX && coordY == poppedCell.coordY) {
        fillingOriginalPathfinding();
        return false;
    }
    
    bool result = DetailedPathfinding(coordX, coordY);
    
    if (result) {
        OurMAINPathStack.push(OurOtherPathStack.topAndPop());
    } else {
        fillingOriginalPathfinding();
    }
    
    return result;
}


void Maze::fillingOriginalPathfinding() {  // move all the elements from the OurOtherPathStack stack to the OurMAINPathStack
    Stack<Cell> tempStack;
    while (!OurOtherPathStack.isEmpty()) {
        tempStack.push(OurOtherPathStack.topAndPop());
    }
    while (!tempStack.isEmpty()) {
        OurMAINPathStack.push(tempStack.topAndPop());
    }
}
