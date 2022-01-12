#include <iostream>
#include <random>
#include <cmath>

using namespace std;

void printMenu()
{
	cout << "Start new game - Press 1" << endl;
	cout << "Change board size - Press 2" << endl;
	cout << "Exit - Press 3" << endl;
	cout << "Enter command: ";
}

void generatePositions(int* positions, unsigned size)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(0, size - 1);
	positions[0] = distr(gen);
	positions[1] = distr(gen);
}

void createEmptyBoard(char** board, unsigned size)
{
	for (unsigned i = 0; i < size; ++i)
	{
		board[i] = new char[size];
		for (unsigned j = 0; j < size; j++)
		{
			board[i][j] = '-';
		}
	}
}

void findSymbolPosition(char** board, char symbol, unsigned size, int* position)
{
	bool found = false;
	for (unsigned i = 0; i < size; i++)
	{
		for (unsigned j = 0; j < size; j++)
		{
			if (board[i][j] == symbol)
			{
				position[0] = i;
				position[1] = j;
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
	for (unsigned i = 0; i < size; i++)
	{
		if (i != column && (board[row][i] == '1' || board[row][i] == '2'))
		{
			return true;
		}
	}
	return false;
}

bool topColumnTrap(char** board, unsigned row, unsigned column, unsigned size)
{
	for (unsigned i = 0; i < size; i++)
	{
		if (i != row && (board[i][column] == '1' || board[i][column] == '2'))
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
	int kingPosition[2];
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
	int positions[2];
	for (unsigned i = 0; i < 4; i++)
	{
		generatePositions(positions, size);
		while (board[positions[0]][positions[1]] != '-' || (i == 1 && kingTrap(board, positions[0], positions[1], size, 'P')))
		{
			generatePositions(positions, size);
		}
		board[positions[0]][positions[1]] = symbols[i];
	}
}

void printBoard(char** board, unsigned size)
{
	cout << endl;
	cout << "  ";
	for (unsigned i = 0; i < size; i++)
	{
		cout << i << " ";
	}
	cout << endl;
	for (unsigned i = 0; i < size; i++)
	{
		cout << i << " ";
		for (unsigned j = 0; j < size; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void clearCell(char** board, char symbol, unsigned size)
{
	for (unsigned i = 0; i < size; i++)
	{
		for (unsigned j = 0; j < size; j++)
		{
			if (board[i][j] == symbol)
			{
				board[i][j] = '-';
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
	int kingPosition[2];
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

	int symbolPosition[2];
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

void startGame(char** board, unsigned size, const char* symbols, unsigned& moves)
{
	cout << "K - Computer King" << endl;
	cout << "P - Your King" << endl;
	cout << "1 - Your First Top" << endl;
	cout << "2 - Your Second Top" << endl;
	placeFigures(board, size, symbols);
	while (isCheckMate(board, size))
	{
		placeFigures(board, size, symbols);
	}
	printBoard(board, size);
	unsigned eliminated = 0;
	do
	{
		cout << "Computer's turn:";
		computerMove(board, size, eliminated);
		printBoard(board, size);
		if (eliminated == 2)
		{
			cout << "Draw";
			return;
		}
		char symbolToMove;
		unsigned row, column;
		cout << "Your turn:" << endl;
		cout << "Enter symbol to move: ";
		cin >> symbolToMove;
		while (symbolToMove != 'P' && symbolToMove != '1' && symbolToMove != '2')
		{
			cout << "Invalid symbol to move!" << endl;
			cout << "Enter new symbol to move: ";
			cin >> symbolToMove;
		}
		cout << "Enter row: ";
		cin >> row;
		cout << "Enter column: ";
		cin >> column;
		while (!isValidMove(board, size, symbolToMove, row, column))
		{
			cout << "Invalid coordinates!" << endl;
			cout << "Enter new row: ";
			cin >> row;
			cout << "Enter new column: ";
		}
		clearCell(board, symbolToMove, size);
		board[row][column] = symbolToMove;
		moves++;
		printBoard(board, size);
	} while (!isCheckMate(board, size));

	cout << "CheckMate" << endl;
	cout << "Congratulations, you won!" << endl;
}

int main()
{
	int command;
	unsigned size = 8;
	printMenu();
	cin >> command;
	const char symbols[] = { 'P', 'K', '1', '2' };
	char** board = new char* [size];
	unsigned moves = 0;
	while (!(command >= 1 && command <= 3))
	{
		cout << "Invalid command!" << endl;
		cout << "Enter new command: ";
		cin >> command;
	}

	switch (command)
	{
	case 1:
		startGame(board, size, symbols, moves);
		break;
	case 2:
		cout << "New size should be nxn!" << endl;
		cout << "Enter new size: n = ";
		cin >> size;
		startGame(board, size, symbols, moves);
		break;
	case 3: return 0;
	}
	cout << "Moves: " << moves;
}