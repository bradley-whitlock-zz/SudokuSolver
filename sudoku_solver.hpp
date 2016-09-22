// Bradley Whitlock
// Completed as a personal project

#ifndef SUDOKU_SOLVER
#define SUDOKU_SOLVER

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std; 

class SudokuSolver
{
	private:
		// The "game" in which we update with all the local functions
		int grid[9][9];
		
		// The starting grid of values we can not change
		int startgrid[9][9];
		
		// This is used to check if the soduku has been completed or not
		// Parameters:   N/A
		// Return:       Completed Soduku: TRUE
		//               Not Yet Completed: FALSE
		bool checkDone ();
		
		// Gets the next empty (0) spot on the grid
		// Parameters:   row   - The row in which we will start looking from
		//               col   - The column in which we will start looking from
		void findNextEmpty (int & row, int & col);
		
		// Resets the grid to the starting grid
		// Parameters:   N/A
		// Returns:      N/A
		void resetGrid ();
		
		// Finds the next number avaibale for a given location
		// Parameters:   row   - The row of the value we are checking
		//               col   - The col of the value we are checking
		// Returns:      Able to get higher number: Number
		//               Not able to get number: 0
		int findNumber (int & row, int & col);
		
		// Gets the number previous not apart of the starting grid
		// Parameters:   rowprev - The row we are checking at
		//               colprev - The col we are checking at
		// Returns:      N/A - Updates parameters
		void findPrevNumber (int & rowprev, int & colprev);
		
		// Checks the square, row and column all at once, for simplification
		// Parameters:   row - the row of the value we are checking
		//               col - the column of the value we are checking
		//               num - the value of the spot
		// Returns:      Number will obey rules in sudoku: TRUE
		//               Numbers doesn't obey rules in sudoku: FALSE
		bool checkSpot (int row, int col, int num);
		
		// Gets the first open spot (0) of the sudoku
		// Parameters:   row  - the row variable in which we are updating
		//               col  - the column variable in which we update
		// Returns:      N/A  - Updates parameters
		void getFirstSpot (int & row, int & col);
		
		
		// Sets a spot to a integer
		// Parameters:   x   - the row of the value we are setting
		//               y   - the column of the value we are setting
		//               num - what we are setting the value to
		// Returns:      N/A
		void setSpot (int x, int y, int num);
		
		// Gets the value of a given value of the grid
		// Parameters:   x   - the row of the value we are getting
		//               y   - the column of the value we are getting
		// Returns:      The value of the spot
		int getSpot (int x, int y);
		
		// Increments a spot to the next avaiable number
		// Parameters:   x   - the row of the value we are incrementing
		//               y   - the column of the value we are incrementing
		// Returns:      Can increment:  TRUE
		// 				 Can't increment: FALSE
		bool incSpot (int x, int y);
		
		// Checks if we can increment a given spot
		// Parameters:   x   - the row of the value we are checking
		//               y   - the column of the value we are checking
		// Returns:      Can increment: TRUE
		//               Can't increment: FALSE
		bool checkincSpot (int x, int y);
		
		// This class has the option of inputting the given values through the terminal
		// Parameters:   in  - the stream of which we inputting the numbers
		// Results:      Proper input: TRUE
		//               Invalid Input: FALSE
		bool addValues (istream & in);
		
		// Checks a given row or column for a number
		// Parameters:   isRow   - if TRUE: check row, if FALSE: check column 
		//               RowCol  - the integer value of row/column
		//               num     - the number we are checking
		// Returns:      Contains num: TRUE
		//               Doesn't Contain num: FALSE
		bool checkRowCol (bool isRow, int RowCol, int num);
		
		// Checks a given 3 by 3 grid for a number
		// Parameters:   row    - The row of the value we are checking
		//               col    - The column of the value we are checking
		//               num    - The number we are checking for
		// Returns:      Contains num: TRUE
		//               Doesn't contain num: FALSE
		bool checkSquare (int row, int col, int num); 
		
	public:
		SudokuSolver ();
		
		// Reads in the soduku from a text file, file format: row col num \n
		// Parameters:   in    - The stream in which we are reading the starting numbers 
		// Returns:      N/A
		void inSudoku (istream & in);
		
		// Outputs the soduku to a stream
		// Parameters:   out           - The stream to which we will output the solution to
		//               isStartGrid   - Bool for whether or not it is the starting grid we want to output
		// Retuns:       N/A 
		void outGrid (ostream & out, bool isStartGrid);
			
		// This is the main function which solves the soduku completely
		// Parameters:  N/A
		// Returns:     Completed Soduku
		void solveSudoku ();	
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuSolver::solveSudoku()
{
	int Fcounter = 1, xcurr = 0, ycurr = 0, numcurr = 0, xnew = 0, ynew = 0, xprev = 0, yprev = 0, xfirst = 0, yfirst = 0;
	bool addednum = false;
	
	getFirstSpot(xfirst, yfirst);
	
	while (!checkDone())
	{
		// Find the next empty box in the grid, starting at xcurr, ycurr
		findNextEmpty(xcurr, ycurr);
		
		// Gets next number, 0 if not found
		numcurr = findNumber(xcurr, ycurr);
		
		if (numcurr != 0) { 
			// Add new number
			setSpot(xcurr, ycurr, findNumber(xcurr, ycurr));
		}
		else {
			// Can't add new number
			findPrevNumber(xcurr, ycurr); 
			
			// Try and increment the current num
			if (!incSpot(xcurr, ycurr)) {
				// Couldn't increment the current spot
				do {
					// Set the value of current spot to 0
					setSpot(xcurr, ycurr, 0);
					// Update curr position to the prev number (not in original set)
					findPrevNumber(xcurr, ycurr);
				} while (!incSpot(xcurr,ycurr));
			}
		}
	}
}
void SudokuSolver::getFirstSpot(int & row, int & col)
{
	for (int i = 8; i >=0; i--)
	{
		for (int j = 8; j >= 0; j--)
		{
			if (startgrid[i][j] == 0)
			{
				//cout << "here";
				row = i;
				col = j;
			}
		}
	}
}

bool SudokuSolver::checkSpot(int row, int col, int num)
{
	if (checkRowCol(true, row, num) == false || checkRowCol(false, col, num) == false || checkSquare(row, col, num) == false) {
		return false;
	}
	return true;
}

void SudokuSolver::findPrevNumber (int & rowprev, int & colprev)
{
	int startrow = rowprev, startcol = colprev, temprow = 0, tempcol = 0;
	
	for (int i = 0; i <= startrow; i++) {
		for (int j = 0; j <= 8; j++) {
			if (i < rowprev || (i == rowprev && j < colprev) && startgrid[i][j] == 0) {
				temprow = i;
				tempcol = j;
			}
		}
	}
	rowprev = temprow;
	colprev = tempcol;
}

int SudokuSolver::findNumber(int & row, int & col)
{
	for (int i = 1; i <= 9; i++) {
		if (checkRowCol(true, row, i) && checkRowCol(false, col, i) && checkSquare(row, col, i)) {
			return i;
		}
	}
	return 0;
}

void SudokuSolver::resetGrid()
{
	for (int i = 0; i <  9; i++){
		for (int j = 0; j < 9; j++){
			grid[i][j] = startgrid[i][j];
		}
	}
}

void SudokuSolver::findNextEmpty(int & row, int & col)
{
	for (int i = 8; i >= 0; i--)
		for (int j = 8; j >= 0; j--)
			if (grid[i][j] == 0) {
				row = i;
				col = j;
			}
}
bool SudokuSolver::checkDone()
{
	for (int i = 0; i <  9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (grid[i][j] == 0)
				return false;
		}
	}
	return true;
}
void SudokuSolver::outGrid(ostream & out, bool isStartGrid)
{
	for (int i = 0; i <9; i++) {
		for (int j = 0; j < 9; j++) {
			// Outputs the grid or starting grid accordingly
			if (!isStartGrid) {
				out << grid[i][j] << " ";
			} else {
				out << startgrid[i][j] << " ";
			}
			
			if (j == 2 || j == 5) {
				out << " | ";
			}
		}
		if (i == 2 || i == 5) {
			out << endl << "-----------------------" << endl;
		} else {
			out << endl;	
		}
	}
	out << endl << endl;
}

void SudokuSolver::inSudoku(istream & in)
{
	int row, col, num;
	while (in >> row >> col >> num) {
		grid[row][col] = num;
		startgrid[row][col] = num;
	}
}
bool SudokuSolver::checkSquare (int row, int col, int num)
{
	int box[9], startx, starty;
	
	// Gets the first number in the row
	if (row < 3) 
		startx = 0;
	else if (row < 6)
		startx = 3;
	else
		startx = 6;
		
	// Gets the first number in the column
	if (col < 3)
		starty = 0;
	else if (col < 6)
		starty = 3;
	else 
		starty = 6;
	
	// Goes through all elements in the square and checks if it already has "num"
	for (int i = startx; i < startx + 3; i++)
		for (int j = starty; j < starty + 3; j++) {
			if (grid[i][j] == num) {
				return false;
			}
		}
	return true;
			
}

bool SudokuSolver::checkRowCol (bool isRow, int RowCol, int num)
{
	// If checking row, check if row already contains "num"
	if (isRow)
		for(int i = 0; i < 9; i++) {
			if (grid[RowCol][i] == num)
		    	return false;	
		}
	else 
	// If checking column, check if column already contains "num"
		for (int i = 0; i < 9; i++) {
			if (grid[i][RowCol] == num)
				return false;
		}
	return true;
}

bool SudokuSolver::addValues (istream & in)
{
	bool status = false;
	int  row, col, num;
	while (!status) {
		cout << "Enter row, col, number (0 to exit) ";
		in >> row >> col >> num;
		grid[row][col] = num;
		startgrid[row][col] = num;
		if (row == 0 || col == 0 || num == 0) {
			status == true;
			cout << "Exiting input loop";
		}
	}
}

void SudokuSolver::setSpot (int x, int y, int num)
{
	grid[x][y] = num;
}

int SudokuSolver::getSpot (int x, int y)
{
	return grid[x][y];
}

bool SudokuSolver::incSpot (int x, int y)
{
	int start = grid[x][y];
	for (int i = start; i <= 9; i++) {
		// Checks if it is possible to increment the spot, and increments accordingly
		if (checkSpot(x, y, i)) {
			grid[x][y] = i;
			return true;
		}
	}
	return false;
}

bool SudokuSolver::checkincSpot (int x, int y)
{
	int start = grid[x][y];
	for (int i = start; i <= 9; i++) {
		if (checkSpot(x,y,i)) {
			return true;
		}
	}
	return false;
}

SudokuSolver::SudokuSolver()
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			grid[i][j] = 0;
			startgrid[i][j] = 0;
		}
	}
}

#endif
