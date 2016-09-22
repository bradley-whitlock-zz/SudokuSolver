#include <iostream>
#include <string>

#include "sudoku_solver.hpp"

using namespace std;

int main()
{
	SudokuSolver game;
	
	// The file "sudokuIn.txt" must be in the same directory as the CPP and HPP files
	ifstream fineasy ("sudokuIn.txt");
	
	// Reads in the Soduku from a text file
	game.inSudoku(fineasy);
	
	// Displays the starting grid to the user
	game.outGrid(cout, true);
	
	// Solves the Soduku
	game.solveSudoku();
	
	// Outputs the solved grid to the user
	game.outGrid(cout, false);	
}

