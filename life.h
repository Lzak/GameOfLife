#include <iostream>
#include <fstream>
using namespace std;

class Life {
public:
	Life(int&, int&, char&, int);
	friend ostream& operator<< (ostream&, Life&);
	void check();
	void set_pattern(int option);
private:
	int **grid, **tmpGrid;
	int max_row, max_col;
	char style;
};

Life::Life(int& width, int& height, char& pStyle, int position) {
	max_row = height;
	max_col = width;
	style = pStyle;

	//create both grids
	grid = new int * [max_row];
	tmpGrid = new int * [max_row];
	for (int j=0; j<max_row; j++) {
		grid[j] = new int[max_col];
		tmpGrid[j] = new int[max_col];
	}

	//set both grids to 0
	for (int i=0; i<max_row; i++)
		for (int j=0; j<max_col; j++) {
			grid[i][j] = 0;
			tmpGrid[i][j] = 0;
		}

	//Set pre-check position
	set_pattern(position);
}

void Life::check() {
	int neighbors;
	for (int i=0; i<max_row; i++) {
		for (int j=0; j<max_col; j++) {
			neighbors=0;

			//Count neighbors
			if (i-1 >= 0 && j-1 >= 0) //these if statements are to check out-of-bounds
				if (grid[i-1][j-1] == 1)
					neighbors++;
			if (i-1 >= 0)
				if (grid[i-1][j] == 1)
					neighbors++;
			if (i-1 >= 0 && j+1 < max_col)
				if (grid[i-1][j+1] == 1)
					neighbors++;

			if (j-1 >= 0)
				if (grid[i][j-1] == 1)
					neighbors++;
			if (j+1 < max_col)
				if (grid[i][j+1] == 1)
					neighbors++;

			if (i+1 < max_row && j-1 >= 0)
				if (grid[i+1][j-1] == 1)
					neighbors++;
			if (i+1 < max_row)
				if (grid[i+1][j] == 1)
					neighbors++;
			if (i+1 < max_row && j+1 < max_col)
				if (grid[i+1][j+1] == 1)
					neighbors++;

			//process tmpGrid for next generation
			if (grid[i][j] == 0 && neighbors == 3)
					tmpGrid[i][j] = 1;
			else if (grid[i][j] == 1) 
				tmpGrid[i][j] = (neighbors < 2 || neighbors > 3) ? 0:1;
		}
	}
	//replace grid with tmpGrid
	for (int i=0; i<max_row; i++)
		for (int j=0; j<max_col; j++)
			grid[i][j] = tmpGrid[i][j];
}

//This will first run the checker, THEN display grid
ostream& operator<< (ostream& out, Life& pLife) {
	pLife.check();
	for (int i=0; i<pLife.max_row; i++) {
		for (int j=0; j<pLife.max_col; j++) {
			if (pLife.grid[i][j] == 1) //if critter == 1, draw X
				out << pLife.style;
			else
				out << ' '; //otherwise leave blank
		}
		out << endl;
	}
	return out;
}

void Life::set_pattern(int option) {
	//ORDER: 1)gosper gun  2)glider  3)pulsar  4)tenline
	ifstream in;
	int row=0, col=0, junk=0, found = 0;
	in.open("patterns.txt");
	if(!in) cout << "Please make sure pattern.txt is in the same directory as the EXE!";
	option += 1000;
	while(!in.eof()) {
		in >> junk;
		if (option == junk) {
			while (true) {
				in >> col;
				in >> row;
				if (row > 1000 || col > 1000) break;
				grid[row][col] = 1;
			}
			found = 1;
		}
	}
	if (found == 0) {
		cout << "\nCould not find pattern (does not exist)!\n";
		system("pause");
	}
	in.close();
}