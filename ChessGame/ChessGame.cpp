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

void printMenu()
{
	std::cout << "Start new game - Press 1" << std::endl;
	std::cout << "Change board size - Press 2" << std::endl;
	std::cout << "Exit - Press 3" << std::endl;
	std::cout << "Enter command: ";
}

void generatePositions(int* positions, unsigned size)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(0, size - 1);
	positions[0] = distr(gen);
	positions[1] = distr(gen);
}

void createEmptyBoard(char** board, unsigned size)
{
	for (unsigned row = 0; row < size; row++)
	{
		board[row] = new char[size];
		for (unsigned column = 0; column < size; column++)
		{
			board[row][column] = '-';
		}
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

bool kingTrap(char** board, unsigned row, unsigned column, unsigned size, char kingSymbol)
{
	if (row == 0)
	{
		if (column == 0)
		{
			if (board[row][column + 1] == kingSymbol || board[row + 1][column + 1] == kingSymbol || board[row + 1][column] == kingSymbol)
			{
				return true;
			}
		}
		if (column == (size - 1))
		{
			if (board[row][column - 1] == kingSymbol || board[row + 1][column - 1] == kingSymbol || board[row + 1][column] == kingSymbol)
			{
				return true;
			}
		}
		if (board[row][column - 1] == kingSymbol || board[row + 1][column - 1] == kingSymbol || board[row + 1][column] == kingSymbol
			|| board[row][column + 1] == kingSymbol || board[row + 1][column + 1] == kingSymbol)
		{
			return true;
		}
	}
	if (row == (size - 1))
	{
		if (column == 0)
		{
			if (board[row][column + 1] == kingSymbol || board[row - 1][column + 1] == kingSymbol || board[row - 1][column] == kingSymbol)
			{
				return true;
			}
		}
		if (column == (size - 1))
		{
			if (board[row][column - 1] == kingSymbol || board[row - 1][column - 1] == kingSymbol || board[row - 1][column] == kingSymbol)
			{
				return true;
			}
		}
		if (board[row][column - 1] == kingSymbol || board[row - 1][column - 1] == kingSymbol || board[row - 1][column] == kingSymbol
			|| board[row - 1][column + 1] == kingSymbol || board[row][column + 1] == kingSymbol)
		{
			return true;
		}
	}
	else if (row != 0 && row != (size - 1))
	{
		if (column == 0)
		{
			if (board[row][column + 1] == kingSymbol || board[row - 1][column + 1] == kingSymbol || board[row - 1][column] == kingSymbol
				|| board[row + 1][column + 1] == kingSymbol || board[row + 1][column] == kingSymbol)
			{
				return true;
			}
		}
		else if (column == (size - 1))
		{
			if (board[row][column - 1] == kingSymbol || board[row - 1][column - 1] == kingSymbol || board[row - 1][column] == kingSymbol
				|| board[row + 1][column - 1] == kingSymbol || board[row + 1][column] == kingSymbol)
			{
				return true;
			}
		}
		else
		{
			if (board[row][column - 1] == kingSymbol || board[row - 1][column - 1] == kingSymbol || board[row - 1][column] == kingSymbol
				|| board[row + 1][column - 1] == kingSymbol || board[row + 1][column] == kingSymbol || board[row - 1][column + 1] == kingSymbol
				|| board[row][column + 1] == kingSymbol || board[row + 1][column + 1] == kingSymbol)
			{
				return true;
			}
		}
	}
	return false;
}

bool topRowTrap(char** board, unsigned row, unsigned column, unsigned size)
{
	for (unsigned currentColumn = 0; currentColumn < size; currentColumn++)
	{
		if (currentColumn != column && (board[row][currentColumn] == '1' || board[row][currentColumn] == '2'))
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
		if (currentRow != row && (board[currentRow][column] == '1' || board[currentRow][column] == '2'))
		{
			return true;
		}
	}
	return false;
}

bool trapped(char** board, unsigned row, unsigned column, unsigned size)
{
	if (kingTrap(board, row, column, size, 'P') || topColumnTrap(board, row, column, size) || topRowTrap(board, row, column, size))
	{
		return true;
	}
	return false;
}

bool possibleComputerKingMoves(char** board, unsigned row, unsigned column, unsigned size)
{
	//Move Right
	if (column != (size - 1))
	{
		if (!trapped(board, row, column + 1, size))
		{
			return true;
		}
	}
	//Move Left
	if (column != 0)
	{
		if (!trapped(board, row, column - 1, size))
		{
			return true;
		}
	}
	//Move Up
	if (row != 0)
	{
		if (!trapped(board, row - 1, column, size))
		{
			return true;
		}
	}
	//Move Down
	if (row != (size - 1))
	{
		if (!trapped(board, row + 1, column, size))
		{
			return true;
		}
	}
	//Move Up Right
	if (row != 0 && column != (size - 1))
	{
		if (!trapped(board, row - 1, column + 1, size))
		{
			return true;
		}
	}
	//Move Up Left
	if (row != 0 && column != 0)
	{
		if (!trapped(board, row - 1, column - 1, size))
		{
			return true;
		}
	}
	//Move Down Right
	if (row != (size - 1) && column != (size - 1))
	{
		if (!trapped(board, row + 1, column + 1, size))
		{
			return true;
		}
	}
	//Move Down Left
	if (row != (size - 1) && column != 0)
	{
		if (!trapped(board, row + 1, column - 1, size))
		{
			return true;
		}
	}
	return false;
}

bool isCheckMate(char** board, unsigned size)
{
	const char computerKing = 'K';
	const unsigned arraySize = 2;
	int kingPosition[arraySize];
	findSymbolPosition(board, computerKing, size, kingPosition);
	int kingRow = kingPosition[0];
	int kingColumn = kingPosition[1];
	if (!possibleComputerKingMoves(board, kingRow, kingColumn, size))
	{
		return true;
	}

	return false;
}

void placeFigures(char** board, unsigned size, const char* symbols)
{
	createEmptyBoard(board, size); 
	const unsigned arraySize = 2;
	int positions[arraySize];
	const unsigned symbolsCount = 4;
	for (unsigned symbolIndex = 0; symbolIndex < symbolsCount; symbolIndex++)
	{
		generatePositions(positions, size);
		while (board[positions[0]][positions[1]] != '-' || (symbolIndex == 1 && kingTrap(board, positions[0], positions[1], size, 'P')))
		{
			generatePositions(positions, size);
		}
		board[positions[0]][positions[1]] = symbols[symbolIndex];
	}
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
				board[row][column] = '-';
				return;
			}
		}
	}
}

bool canEliminate(char** board, unsigned size, unsigned row, unsigned column)
{
	//Move Right
	if (column != (size - 1))
	{
		if ((board[row][column + 1] == '1' || board[row][column + 1] == '2') && !trapped(board, row, column + 1, size))
		{
			board[row][column + 1] = 'K';
			return true;
		}
	}
	//Move Left
	if (column != 0)
	{
		if ((board[row][column - 1] == '1' || board[row][column - 1] == '2') && !trapped(board, row, column - 1, size))
		{
			board[row][column - 1] = 'K';
			return true;
		}
	}
	//Move Up
	if (row != 0)
	{
		if ((board[row - 1][column] == '1' || board[row - 1][column] == '2') && !trapped(board, row - 1, column, size))
		{
			board[row - 1][column] = 'K';
			return true;
		}
	}
	//Move Down
	if (row != (size - 1))
	{
		if ((board[row + 1][column] == '1' || board[row + 1][column] == '2') && !trapped(board, row + 1, column, size))
		{
			board[row + 1][column] = 'K';
			return true;
		}
	}
	//Move Up Right
	if (row != 0 && column != (size - 1))
	{
		if ((board[row - 1][column + 1] == '1' || board[row - 1][column + 1] == '2') && !trapped(board, row - 1, column + 1, size))
		{
			board[row - 1][column + 1] = 'K';
			return true;
		}
	}
	//Move Up Left
	if (row != 0 && column != 0)
	{
		if ((board[row - 1][column - 1] == '1' || board[row - 1][column - 1] == '2') && !trapped(board, row - 1, column - 1, size))
		{
			board[row - 1][column - 1] = 'K';
			return true;
		}
	}
	//Move Down Right
	if (row != (size - 1) && column != (size - 1))
	{
		if ((board[row + 1][column + 1] == '1' || board[row + 1][column + 1] == '2') && !trapped(board, row + 1, column + 1, size))
		{
			board[row + 1][column + 1] = 'K';
			return true;
		}
	}
	//Move Down Left
	if (row != (size - 1) && column != 0)
	{
		if ((board[row + 1][column - 1] == '1' || board[row + 1][column - 1] == '2') && !trapped(board, row + 1, column - 1, size))
		{
			board[row + 1][column - 1] = 'K';
			return true;
		}
	}
	return false;
}

bool randomMove(char** board, unsigned size, unsigned row, unsigned column)
{
	//Move Right
	if (column != (size - 1) && board[row][column + 1] == '-' && !trapped(board, row, column + 1, size))
	{
		board[row][column + 1] = 'K';
		return true;
	}
	//Move Left
	else if (column != 0 && board[row][column - 1] == '-' && !trapped(board, row, column - 1, size))
	{
		board[row][column - 1] = 'K';
		return true;
	}
	//Move Up
	else if (row != 0 && board[row - 1][column] == '-' && !trapped(board, row - 1, column, size))
	{
		board[row - 1][column] = 'K';
		return true;
	}
	//Move Down
	else if (row != (size - 1) && board[row + 1][column] == '-' && !trapped(board, row + 1, column, size))
	{
		board[row + 1][column] = 'K';
		return true;
	}
	//Move Up Right
	else if (row != 0 && column != (size - 1) && board[row - 1][column + 1] == '-' && !trapped(board, row - 1, column + 1, size))
	{
		board[row - 1][column + 1] = 'K';
		return true;
	}
	//Move Up Left
	else if (row != 0 && column != 0 && board[row - 1][column - 1] == '-' && !trapped(board, row - 1, column - 1, size))
	{
		board[row - 1][column - 1] = 'K';
		return true;
	}
	//Move Down Right
	else if (row != (size - 1) && column != (size - 1) && board[row + 1][column + 1] == '-' && !trapped(board, row + 1, column + 1, size))
	{
		board[row + 1][column + 1] = 'K';
		return true;
	}
	//Move Down Left
	else if (row != (size - 1) && column != 0 && board[row + 1][column - 1] == '-' && !trapped(board, row + 1, column - 1, size))
	{
		board[row + 1][column - 1] = 'K';
		return true;
	}
	return false;
}

void computerMove(char** board, unsigned size, unsigned& eliminated)
{
	const char computerKing = 'K';
	const unsigned arraySize = 2;
	int kingPosition[arraySize];
	findSymbolPosition(board, computerKing, size, kingPosition);
	unsigned kingRow = kingPosition[0];
	unsigned kingColumn = kingPosition[1];
	if (canEliminate(board, size, kingRow, kingColumn))
	{
		eliminated++;
		board[kingRow][kingColumn] = '-';
	}
	else if (randomMove(board, size, kingRow, kingColumn))
	{
		board[kingRow][kingColumn] = '-';
	}
}

bool isValidKingMove(char** board, unsigned size, char symbolToMove, unsigned currentRow,
	unsigned currentColumn, unsigned newRow, unsigned newColumn)
{
	int rowMoves = currentRow - newRow;
	int columnMoves = currentColumn - newColumn;

	if (abs(rowMoves) <= 1 && abs(columnMoves) <= 1 && !kingTrap(board, newRow, newColumn, size, 'K'))
	{
		return true;
	}

	return false;
}

bool isValidMove(char** board, unsigned size, char symbolToMove, unsigned row, unsigned column)
{
	if ((row < 0 || row >= size || column < 0 || column >= size) || board[row][column] != '-')
	{
		return false;
	}

	const unsigned arraySize = 2;
	int symbolPosition[arraySize];
	findSymbolPosition(board, symbolToMove, size, symbolPosition);
	unsigned symbolRow = symbolPosition[0];
	unsigned symbolColumn = symbolPosition[1];
	if (symbolToMove == 'P')
	{
		return isValidKingMove(board, size, 'P', symbolRow, symbolColumn, row, column);
	}
	else
	{
		return row == symbolRow || column == symbolColumn;
	}
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
			return;
		}
		char symbolToMove;
		unsigned row, column;
		std::cout << "Your turn:" << std::endl;
		std::cout << "Enter symbol to move: ";
		std::cin >> symbolToMove;
		while (symbolToMove != 'P' && symbolToMove != '1' && symbolToMove != '2')
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
	moves++;
	std::cout << "CheckMate" << std::endl;
	std::cout << "Congratulations, you won!" << std::endl; sleep_for(nanoseconds(10));
	sleep_until(system_clock::now() + seconds(1));
	std::cout << "Moves: " << moves << std::endl;
	printMenu();
}

int main()
{
	int command;
	unsigned size = 8;
	printMenu();
	std::cin >> command;
	const char symbols[] = { 'P', 'K', '1', '2' };
	char** board = new char* [size];
	while (!(command >= 1 && command <= 3))
	{
		std::cout << "Invalid command!" << std::endl;
		std::cout << "Enter new command: ";
		std::cin >> command;
	}

	while (command != 3)
	{
		switch (command)
		{
		case 1:
			startGame(board, size, symbols, 0);
			break;
		case 2:
			std::cout << "New size should be nxn!" << std::endl;
			std::cout << "Enter new size: n = ";
			std::cin >> size;
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