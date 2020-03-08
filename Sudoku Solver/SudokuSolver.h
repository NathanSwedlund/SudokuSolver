#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Board; // Forward declaring Board class

// Tile class -----------------------------
class Tile
{
	int value;
	int index;
	Board* b;
public:
	void setValue(int _value);
	void setIndex(int _index) { index = _index; }
	int  getIndex() { return index; }
	void setBoard(Board* _b)  { b = _b; }
	int  getValue() { return value; }
};
// -----------------------------------------

class Board
{
	// Stores the options for each row, column, and box
	bool** rowsOpts;
	bool** colsOpts;
	bool** boxsOpts;

	Tile* tiles; // Stores the 81 tiles of the sudoku board
public:
	Board(string fileName)
	{
		// Allocating memory for board
		rowsOpts = new bool*[9];
		colsOpts = new bool*[9];
		boxsOpts = new bool*[9];
		for(int i = 0; i < 9; i++)
		{
			rowsOpts[i] = new bool[9];
			colsOpts[i] = new bool[9];
			boxsOpts[i] = new bool[9];
			for(int x = 0; x < 9; x++)
			{
				rowsOpts[i][x] = true;
				colsOpts[i][x] = true;
				boxsOpts[i][x] = true;
			}
		}

		// Getting Tile values from file
		ifstream fin;
		tiles = new Tile[81];
		fin.open(fileName.c_str());
		if(fin.is_open())
		{
			int num;
			for(int i = 0; i < 81 && fin>>num; i++)
			{
				tiles[i].setIndex(i);
				tiles[i].setBoard(this);
				tiles[i].setValue(num);
			}
		}
		else
			cout<<"Error opening "<<fileName<<'\n';
		fin.close();
	}

	~Board()
	{
		// Deallocating memory
		for(int i = 0; i < 9; i++)
		{
			delete rowsOpts[i];
			delete colsOpts[i];
			delete boxsOpts[i];
		}
		delete [] rowsOpts;
		delete [] colsOpts;
		delete [] boxsOpts;
		delete [] tiles;
	}

	// Eliminates an option from the row, box, and column of a given index
	void eliminateOption(int index, int opt)
	{
		int row = index/9;
		int col = index%9;
		int box = (col/3) + 3*(row/3);
		rowsOpts[row][opt-1] = false;
		colsOpts[col][opt-1] = false;
		boxsOpts[box][opt-1] = false;
	}

	// Solves a Tile if possible. If it does returns true, else false.
	bool solveTile(Tile& t)
	{
		// Stopping if Tile is already solved.
		if(t.getValue() != 0)
			return false;

		// Finding row/column/box numbers.
		int row = t.getIndex()/9;
		int col = t.getIndex()%9;
		int box = (col/3) + 3*(row/3);

		int count = 0; // Keeps track of how many possible values the tile could have.
		int possibility; // Keeps track of the most recently seen possible value.

		// Since we're only interested in Tiles with 1 possibility, loop will stop if "t"
		//  has more than 1.
		for(int i = 0; i < 9 && count < 2; i++)
		{
			// If "i" is an option for "t"s row column and box then it's a possibility.
			if (rowsOpts[row][i] && colsOpts[col][i] && boxsOpts[box][i])
			{
				count++;
				possibility = i;
			}
		}
		// If there is only possibility, set the Tile's value and return true.
		if(count == 1)
		{
			t.setValue(possibility+1);
			return true;
		}
		// else return false.
		return false;
	}
	//
	bool loop()
	{
		bool hasChanged = false;
		for(int i = 0; i < 81; i++)
			hasChanged = (solveTile(tiles[i]) || hasChanged);
		return hasChanged;
	}

	// Solves the board
	void solve(int maxLoops = 100)
	{
		for(int i = 0; i < maxLoops && loop(); i++) {}
	}

	// Prints the board to the output stream
	friend ostream& operator<<(ostream& out, Board& b)
	{
		for(int row = 0; row < 9; row++)
		{
			for(int col = 0; col < 9; col++)
				out<<b.tiles[col + (row*9)].getValue()<<' ';
			out<<'\n';
		}
		return out;
	}
};

void Tile::setValue(int _value)
{
	value = _value;
	b->eliminateOption(index, value);
}
