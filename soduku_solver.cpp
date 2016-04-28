// Bradley Whitlock
// January 2015
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <cmath>
// this is a comment anf d I am going to  commit to github

using namespace std; 

class SudokuSolver
{
	private:
		int grid[9][9];
		int startgrid[9][9];
	public:
		SudokuSolver ();
		void setSpot (int x, int y, int num);
		int getSpot (int x, int y);
		bool incSpot (int x, int y);
		bool checkincSpot (int x, int y);
		bool addValues (istream & in);
		bool checkRowCol (bool isRow, int RowCol, int num);
		bool checkSquare (int row, int col, int num); 
		void inSudoku (istream & in); // row col num
		void outGrid (ostream & out);
		void outStartGrid (ostream & out);
		bool checkDone();
		void findNextEmpty(int & row, int & col);
		void resetGrid();
		int findNumber(int & row, int & col);
		void findPrevNumber (int & rowprev, int & colprev);
		bool checkSpot (int row, int col, int num);
		void getFirstSpot (int & row, int & col);
		void solveSudoku();	
};

int main()
{
	SudokuSolver game;
	ifstream fin ("sudokutrial.txt");
	ifstream fineasy ("sudokueasy.txt");
	game.inSudoku(fineasy);
	
	game.solveSudoku();
	
	game.outStartGrid(cout);
	cout <<endl;
	game.outGrid(cout);
	cout << endl;	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void SudokuSolver::solveSudoku()
{
		int Fcounter = 1; 
	int xcurr = 0, ycurr = 0, numcurr = 0;
	int xnew = 0, ynew = 0;
	int xprev = 0, yprev = 0;
	bool addednum = false;
	
	int xfirst = 0, yfirst = 0;
	getFirstSpot(xfirst, yfirst);
	
	while (!checkDone())// && game.checkincSpot(xfirst, yfirst)) // main loop
	{
		findNextEmpty(xcurr, ycurr); // find empty box
		numcurr = findNumber(xcurr, ycurr); // tries to find number returns 0 if not found
		if (numcurr != 0) //ADD NEW NUMBER
		{ 
			setSpot(xcurr, ycurr, findNumber(xcurr, ycurr));
		}
		else //CANT ADD NUMBER
		{
			findPrevNumber(xcurr, ycurr); 
			if (incSpot(xcurr, ycurr) == true) // if we can increment then we will
			{			}
			else // cant increment the box
			{		
				while (incSpot(xcurr,ycurr) == false)
				{
					setSpot(xcurr, ycurr, 0);
					findPrevNumber(xcurr, ycurr);
				}
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
	if (checkRowCol(true, row, num) == false || checkRowCol(false, col, num) == false || checkSquare(row, col, num) == false)
	{
		return false;
	}
	return true;
}
void SudokuSolver::findPrevNumber (int & rowprev, int & colprev)
{
	int startrow = rowprev;
	int startcol = colprev;
	int temprow = 0;
	int tempcol = 0;
	for (int i = 0; i <= startrow; i++)
	{
		for (int j = 0; j <= 8; j++)
		{
			if (i < rowprev || (i == rowprev && j < colprev))
			{
				if (startgrid[i][j] == 0)
				{
					temprow = i;
					tempcol = j;
					
				}
			}
		}
	}
	rowprev = temprow;
	colprev = tempcol;
}

int SudokuSolver::findNumber(int & row, int & col)
{
	for (int i = 1; i <= 9; i++)
	{
		if (checkRowCol(true, row, i) && checkRowCol(false, col, i) && checkSquare(row, col, i))
		{
			return i;
		}
	}
	return 0;
}

void SudokuSolver::resetGrid()
{
	for (int i = 0; i <  9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			grid[i][j] = startgrid[i][j];
		}
	}
}

void SudokuSolver::findNextEmpty(int & row, int & col)
{
	for (int i = 8; i >= 0; i--)
		for (int j = 8; j >= 0; j--)
			if (grid[i][j] == 0)
			{
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
void SudokuSolver::outGrid(ostream & out)
{
	for (int i = 0; i <9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			out << grid[i][j] << " ";
		}
		out << endl;
	}
}

void SudokuSolver::outStartGrid(ostream & out)
{
	for (int i = 0; i <9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			out << startgrid[i][j] << " ";
		}
		out << endl;
	}
}

void SudokuSolver::inSudoku(istream & in)
{
	int row, col, num;
	while (in >> row >> col >> num)
	{
		grid[row][col] = num;
		startgrid[row][col] = num;
	}
}
bool SudokuSolver::checkSquare (int row, int col, int num)
{
	int box[9];
	int startx, starty;
	if (row < 3) 
		startx = 0;
	else if (row < 6)
		startx = 3;
	else
		startx = 6;
	if (col < 3)
		starty = 0;
	else if (col < 6)
		starty = 3;
	else 
		starty = 6;
	
	for (int i = startx; i < startx + 3; i++)
		for (int j = starty; j < starty + 3; j++)
		{
			if (grid[i][j] == num)
			{
				return false;
			}
		}
	return true;
			
}
bool SudokuSolver::checkRowCol (bool isRow, int RowCol, int num)
{
	if (isRow) //checking row
		for(int i = 0; i < 9; i++) 
		{
			if (grid[RowCol][i] == num)
		    	return false;	
		}
	else // checking column
		for (int i = 0; i < 9; i++)
		{
			if (grid[i][RowCol] == num)
				return false;
		}
	return true;
}
bool SudokuSolver::addValues (istream & in)
{
	bool status = false;
	int  row, col, num;
	while (status == false)
	{
		cout << "Enter row, col, number (0 to exit) ";
		in >> row >> col >> num;
		grid[row][col] = num;
		startgrid[row][col] = num;
		if (row == 0 || col == 0 || num == 0) {
			status == true;
			cout << "exit input loop";
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
	for (int i = start; i <= 9; i++)
	{
		if (checkSpot(x,y,i))
		{
			grid[x][y] = i;
			return true;
		}
	}
	return false;
}
bool SudokuSolver::checkincSpot (int x, int y)
{
	int start = grid[x][y];
	for (int i = start; i <= 9; i++)
	{
		if (checkSpot(x,y,i))
		{
			//cout << "here";
			return true;
		}
	}
	return false;
}
SudokuSolver::SudokuSolver()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			grid[i][j] = 0;
			startgrid[i][j] = 0;
		}
	}
}
