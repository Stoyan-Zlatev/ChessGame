/**
*
* Solution to course project # 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2021/2022
*
* @author Stoyan Zlatev
* @idnumber 4MI0600043
* @compiler VC
*
* <file with simple chess game>
*
*/

#include <iostream>
#include <random>
#include <cmath>
#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono;

const unsigned CoordinatesArraySize = 2;
const int CombinationsCount = 8;
const int RowDimensions[] = { 0, 0,-1, 1,-1,-1, 1, 1 };
const int ColumnDimensions[] = { 1,-1, 0, 0, 1,-1, 1, -1 };
const char EmptyCell = '-';
const char ComputerKingSymbol = 'K';
const char MyKingSymbol = 'P';
const char FirstTop = '1';
const char SecondTop = '2';

void printMenu()
{
	std::cout << "Start new game - Press 1" << std::endl;
	std::cout << "Change board size - Press 2" << std::endl;
	std::cout << "Exit - Press 3" << std::endl;
	std::cout << "Enter command: ";
}

void createEmptyBoard(char** board, unsigned size)
{
	for (unsigned row = 0; row < size; row++)
	{
		board[row] = new char[size];
		for (unsigned column = 0; column < size; column++)
		{
			board[row][column] = EmptyCell;
		}
	}
}

void generatePositions(int* positions, unsigned size)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(0, size - 1);
	positions[0] = distr(gen);
	positions[1] = distr(gen);
}

bool kingTrap(char** board, unsigned row, unsigned column, unsigned size, char kingSymbol)
{
	for (unsigned i = 0; i < CombinationsCount; i++)
	{
		int newRow = row + RowDimensions[i];
		int newColumn = column + ColumnDimensions[i];
		if (newRow >= 0 && newRow < size && newColumn >= 0 && newColumn < size)
		{
			if (board[newRow][newColumn] == kingSymbol)
			{
				return true;
			}
		}
	}

	return false;
}

void placeFigures(char** board, unsigned size, const char* symbols)
{
	createEmptyBoard(board, size);
	int positions[CoordinatesArraySize];
	const unsigned symbolsCount = 4;

	for (unsigned symbolIndex = 0; symbolIndex < symbolsCount; symbolIndex++)
	{
		generatePositions(positions, size);
		while (board[positions[0]][positions[1]] != EmptyCell || (symbolIndex == 1 && kingTrap(board, positions[0], positions[1], size, MyKingSymbol)))
		{
			generatePositions(positions, size);
		}
		board[positions[0]][positions[1]] = symbols[symbolIndex];
	}
}

void findSymbolPosition(char** board, char symbol, unsigned size, int* position)
{
	bool found = false;
	for (unsigned row = 0; row < size; row++)
	{
		for (unsigned column = 0; column < size; column++)
		{
			if (board[row][column] == symbol)
			{
				position[0] = row;
				position[1] = column;
				return;
			}
		}
	}
}

bool topRowTrap(char** board, unsigned row, unsigned column, unsigned size)
{
	for (unsigned currentColumn = 0; currentColumn < size; currentColumn++)
	{
		if (currentColumn != column && (board[row][currentColumn] == FirstTop || board[row][currentColumn] == SecondTop))
		{
			return true;
		}
	}
	return false;
}

bool topColumnTrap(char** board, unsigned row, unsigned column, unsigned size)
{
	for (unsigned currentRow = 0; currentRow < size; currentRow++)
	{
		if (currentRow != row && (board[currentRow][column] == FirstTop || board[currentRow][column] == SecondTop))
		{
			return true;
		}
	}
	return false;
}

bool trapped(char** board, unsigned row, unsigned column, unsigned size)
{
	if (kingTrap(board, row, column, size, MyKingSymbol) || topColumnTrap(board, row, column, size) || topRowTrap(board, row, column, size))
	{
		return true;
	}
	return false;
}

bool possibleComputerKingMoves(char** board, unsigned row, unsigned column, unsigned size)
{
	for (unsigned i = 0; i < CombinationsCount; i++)
	{
		int newRow = row + RowDimensions[i];
		int newColumn = column + ColumnDimensions[i];
		if (newRow >= 0 && newRow < size && newColumn >= 0 && newColumn < size)
		{
			if (!trapped(board, newRow, newColumn, size))
			{
				return true;
			}
		}
	}

	return false;
}

bool isCheckMate(char** board, unsigned size)
{
	int kingPosition[CoordinatesArraySize];
	findSymbolPosition(board, ComputerKingSymbol, size, kingPosition);
	int kingRow = kingPosition[0];
	int kingColumn = kingPosition[1];
	if (!possibleComputerKingMoves(board, kingRow, kingColumn, size))
	{
		return true;
	}

	return false;
}

void printBoard(char** board, unsigned size)
{
	std::cout << std::endl;
	std::cout << "  ";

	for (unsigned column = 0; column < size; column++)
	{
		std::cout << column << " ";
	}

	std::cout << std::endl;

	for (unsigned row = 0; row < size; row++)
	{
		std::cout << row << " ";
		for (unsigned column = 0; column < size; column++)
		{
			std::cout << board[row][column] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
}

void clearCell(char** board, char symbol, unsigned size)
{
	for (unsigned row = 0; row < size; row++)
	{
		for (unsigned column = 0; column < size; column++)
		{
			if (board[row][column] == symbol)
			{
				board[row][column] = EmptyCell;
				return;
			}
		}
	}
}

bool canEliminate(char** board, unsigned size, unsigned row, unsigned column)
{
	for (unsigned i = 0; i < CombinationsCount; i++)
	{
		int newRow = row + RowDimensions[i];
		int newColumn = column + ColumnDimensions[i];
		if (newRow >= 0 && newRow < size && newColumn >= 0 && newColumn < size)
		{
			if ((board[newRow][newColumn] == FirstTop || board[newRow][newColumn] == SecondTop) && !trapped(board, newRow, newColumn, size))
			{
				board[newRow][newColumn] = ComputerKingSymbol;
				return true;
			}
		}
	}

	return false;
}

bool randomMove(char** board, unsigned size, unsigned row, unsigned column)
{
	for (unsigned i = 0; i < CombinationsCount; i++)
	{
		int newRow = row + RowDimensions[i];
		int newColumn = column + ColumnDimensions[i];
		if (newRow >= 0 && newRow < size && newColumn >= 0 && newColumn < size)
		{
			if (board[newRow][newColumn] == EmptyCell && !trapped(board, newRow, newColumn, size))
			{
				board[newRow][newColumn] = ComputerKingSymbol;
				return true;
			}
		}
	}

	return false;
}

void computerMove(char** board, unsigned size, unsigned& eliminated)
{
	int kingPosition[CoordinatesArraySize];
	findSymbolPosition(board, ComputerKingSymbol, size, kingPosition);
	unsigned kingRow = kingPosition[0];
	unsigned kingColumn = kingPosition[1];
	if (canEliminate(board, size, kingRow, kingColumn))
	{
		eliminated++;
		board[kingRow][kingColumn] = EmptyCell;
	}
	else if (randomMove(board, size, kingRow, kingColumn))
	{
		board[kingRow][kingColumn] = EmptyCell;
	}
}

bool isValidKingMove(char** board, unsigned size, unsigned currentRow,
	unsigned currentColumn, unsigned newRow, unsigned newColumn)
{
	int rowMoves = currentRow - newRow;
	int columnMoves = currentColumn - newColumn;

	if (abs(rowMoves) <= 1 && abs(columnMoves) <= 1 && !kingTrap(board, newRow, newColumn, size, ComputerKingSymbol))
	{
		return true;
	}

	return false;
}

bool isFreeColumn(char** board, unsigned symbolRow, unsigned symbolColumn, unsigned row, unsigned column)
{
	if (symbolColumn < column)
	{
		for (unsigned tempColumn = symbolColumn + 1; tempColumn <= column; tempColumn++)
		{
			if (board[symbolRow][tempColumn] != EmptyCell)
			{
				return false;
			}
		}
	}
	else
	{
		for (int tempColumn = symbolColumn - 1; tempColumn > column; tempColumn--)
		{
			if (board[symbolRow][tempColumn] != EmptyCell)
			{
				return false;
			}
		}
	}
	return true;
}

bool isFreeRow(char** board, unsigned symbolRow, unsigned symbolColumn, unsigned row, unsigned column)
{
	if (symbolRow < row)
	{
		for (unsigned tempRow = symbolRow + 1; tempRow <= row; tempRow++)
		{
			if (board[tempRow][symbolColumn] != EmptyCell)
			{
				return false;
			}
		}
	}
	else
	{
		for (int tempRow = symbolRow - 1; tempRow > row; tempRow--)
		{
			if (board[tempRow][symbolColumn] != EmptyCell)
			{
				return false;
			}
		}
	}
	return true;
}

bool isValidMove(char** board, unsigned size, char symbolToMove, unsigned row, unsigned column)
{
	if ((row < 0 || row >= size || column < 0 || column >= size) || board[row][column] != EmptyCell)
	{
		return false;
	}

	int symbolPosition[CoordinatesArraySize];
	findSymbolPosition(board, symbolToMove, size, symbolPosition);
	unsigned symbolRow = symbolPosition[0];
	unsigned symbolColumn = symbolPosition[1];
	if (symbolToMove == MyKingSymbol)
	{
		return isValidKingMove(board, size, symbolRow, symbolColumn, row, column);
	}
	else
	{
		if (row == symbolRow)
		{
			return isFreeColumn(board, symbolRow, symbolColumn, row, column);
		}
		else if (column == symbolColumn)
		{
			return isFreeRow(board, symbolRow, symbolColumn, row, column);
		}
	}
	return false;
}

void startGame(char** board, unsigned size, const char* symbols, unsigned moves)
{
	std::cout << "K - Computer King" << std::endl;
	std::cout << "P - Your King" << std::endl;
	std::cout << "1 - Your First Top" << std::endl;
	std::cout << "2 - Your Second Top" << std::endl;
	placeFigures(board, size, symbols);
	while (isCheckMate(board, size))
	{
		placeFigures(board, size, symbols);
	}
	printBoard(board, size);
	unsigned eliminated = 0;
	do
	{
		std::cout << "Computer's turn:";
		computerMove(board, size, eliminated);
		sleep_for(nanoseconds(10));
		sleep_until(system_clock::now() + seconds(2));
		printBoard(board, size);
		if (eliminated == 2)
		{
			std::cout << "Draw" << std::endl;
			printMenu();
			return;
		}
		char symbolToMove;
		unsigned row, column;
		std::cout << "Your turn:" << std::endl;
		std::cout << "Enter symbol to move: ";
		std::cin >> symbolToMove;
		while (symbolToMove != MyKingSymbol && symbolToMove != FirstTop && symbolToMove != SecondTop)
		{
			std::cout << "Invalid symbol to move!" << std::endl;
			std::cout << "Enter new symbol to move: ";
			std::cin >> symbolToMove;
		}
		std::cout << "Enter row: ";
		std::cin >> row;
		std::cout << "Enter column: ";
		std::cin >> column;

		while (!isValidMove(board, size, symbolToMove, row, column))
		{
			std::cout << "Invalid coordinates!" << std::endl;
			std::cout << "Enter new row: ";
			std::cin >> row;
			std::cout << "Enter new column: ";
			std::cin >> column;
		}

		clearCell(board, symbolToMove, size);

		board[row][column] = symbolToMove;
		moves++;

		printBoard(board, size);
	} while (!isCheckMate(board, size));

	//Last move you make to finish the game
	moves++;

	std::cout << "CheckMate" << std::endl;
	std::cout << "Congratulations, you won!" << std::endl;

	sleep_for(nanoseconds(10));
	sleep_until(system_clock::now() + seconds(1));

	std::cout << "Moves: " << moves << std::endl;
	std::cout << std::endl;

	printMenu();
}

int main()
{
	int command;
	unsigned size = 8;
	printMenu();
	std::cin >> command;
	const char symbols[] = { MyKingSymbol, ComputerKingSymbol, FirstTop, SecondTop };
	char** board = new char* [size];

	const int start = 1;
	const int changeSize = 2;
	const int exit = 3;

	while (!(command >= start && command <= exit))
	{
		std::cout << "Invalid command!" << std::endl;
		std::cout << "Enter new command: ";
		std::cin >> command;
	}

	while (command != exit)
	{
		switch (command)
		{
		case start:
			startGame(board, size, symbols, 0);
			break;
		case changeSize:
			std::cout << "New size should be nxn, n>=3" << std::endl;
			std::cout << "Enter new size: n = ";
			std::cin >> size;
			while (size < 3)
			{
				std::cout << "Invalid size!" << std::endl;
				std::cout << "Enter new size: n = ";
				std::cin >> size;
			}
			startGame(board, size, symbols, 0);
			break;
		default: std::cout << "Invalid command!" << std::endl;
			std::cout << "Enter new command: "; break;
		}
		std::cin >> command;
	}

	for (unsigned row = 0; row < size; row++)
	{
		delete[] board[row];
	}

	delete[] board;
}
