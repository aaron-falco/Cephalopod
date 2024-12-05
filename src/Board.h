#ifndef BOARD_H_
#define BOARD_H_

class Board {
private:
	int row, col;
	int player;
	int** grid;

	vector<Cell> emptyCells;

public:
	Board(int r, int c) :
		row(r), col(c) {
		grid = new int* [row];
		for (int i = 0; i < row; i++)
			grid[i] = new int[col];

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				grid[i][j] = 0;
				Cell temp(i + 1, j + 1, 0, 0);
				emptyCells.push_back(temp);
			}
		}

		player = 1;
	}

	~Board() {
		for (int i = 0; i < row; i++)
			delete[] grid[i];

		delete[] grid;
	}

	Board(const Board& cboard) {
		row = cboard.row;
		col = cboard.col;

		grid = new int* [row];
		for (int i = 0; i < row; i++)
			grid[i] = new int[col];

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++) {
				grid[i][j] = cboard.grid[i][j];
			}

		emptyCells = cboard.emptyCells;

		player = cboard.getTurn();
	}

	bool isBoardFull() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (grid[i][j] == 0)
					return false;
			}
		}
		return true;
	}

	int getTurn() const {
		return player;
	}

	int getRow() {
		return row;
	}

	int getCol() {
		return col;
	}

	vector<Cell> returnEmptyCells() {

		return emptyCells;
	}

	bool validMove(int x, int y);

	bool addMove(int x, int y);

	int checkWinningStatus();

	void printBoard();

	int capturingPlacement(int, int);

	int heuristics(int, int);

};


int Board::heuristics(int x, int y) {

	if (!validMove(x - 1, y - 1))
		return 0;

	return capturingPlacement(x - 1, y - 1);
}

int Board::capturingPlacement(int x, int y) {

	vector<Cell> cells;

	if (x > 0) {

		if (grid[x - 1][y] != 0 && abs(grid[x - 1][y]) != 6) {

			Cell temp = Cell(x - 1, y, 0, grid[x - 1][y]);
			cells.push_back(temp);
		}
	}

	if (x + 1 < row) {

		if (grid[x + 1][y] != 0 && abs(grid[x + 1][y]) != 6) {

			Cell temp = Cell(x + 1, y, 0, grid[x + 1][y]);
			cells.push_back(temp);
		}
	}


	if (y > 0) {

		if (grid[x][y - 1] != 0 && abs(grid[x][y - 1]) != 6) {

			Cell temp = Cell(x, y - 1, 0, grid[x][y - 1]);
			cells.push_back(temp);
		}
	}


	if (y + 1 < col) {

		if (grid[x][y + 1] != 0 && abs(grid[x][y + 1]) != 6) {

			Cell temp = Cell(x, y + 1, 0, grid[x][y + 1]);
			cells.push_back(temp);
		}
	}


	int len = cells.size();

	if (len < 2) {

		return 1;
	}

	else if (len == 2) {

		int sum = abs(cells[0].value) +
			abs(cells[1].value);


		if (sum > 6) {

			return 1;
		}


		grid[cells[0].x][cells[0].y] = 0;
		grid[cells[1].x][cells[1].y] = 0;


		cells[0].x += 1;
		cells[0].y += 1;

		cells[1].x += 1;
		cells[1].y += 1;

		emptyCells.push_back(cells[0]);
		emptyCells.push_back(cells[1]);

		return sum;
	}
	else if (len > 2) {


		bool altered;

		for (int i = 0; i < len - 1; i++) {
			altered = false;

			for (int j = i; j < len - 1; j++) {

				if (abs(cells[j].value) < abs(cells[j + 1].value)) {

					int temp = cells[j].value;
					cells[j].value = cells[j + 1].value;
					cells[j + 1].value = temp;
					altered = true;
				}
			}
			if (altered) {
				i--;
			}
		}


		int sum = 0;
		vector<Cell> captured;

		for (int i = 0; i < len; i++)
		{
			int tempSum = abs(cells[i].value);
			vector<Cell> tempCaptured;
			tempCaptured.push_back(cells[i]);
			for (int j = i + 1; j < len; j++)
			{
				if (tempSum + abs(cells[j].value) > 6) {

					continue;
				}
				else {

					tempSum += abs(cells[j].value);

					tempCaptured.push_back(cells[j]);
				}
			}

			if (tempSum > sum && tempSum <= 6) {
				sum = tempSum;

				captured = tempCaptured;
			}
		}


		for (int i = 0; i < captured.size(); i++) {
			int tempX = captured[i].x;
			int tempY = captured[i].y;


			grid[tempX][tempY] = 0;


			captured[i].x += 1;
			captured[i].y += 1;
			emptyCells.push_back(captured[i]);
		}

		return sum;
	}

	return 0;
}

int Board::checkWinningStatus() {
	if (!isBoardFull())
		return -2;

	int counter = 0;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (grid[i][j] > 0)
				counter++;
		}
	}

	if (counter * 2 > row * col)
		return 1;
	else if (counter * 2 < row * col)
		return -1;
	else
		return 0;
}

bool Board::validMove(int x, int y) {

	if (x < 0 || y < 0 || x > row - 1 || y > col - 1) {
		return false;
	}

	if (grid[x][y] != 0) {
		return false;
	}

	return true;
}

bool Board::addMove(int x, int y) {

	if (!validMove(x, y))
		return false;

	grid[x][y] = player * capturingPlacement(x, y);

	player = -1 * player;




	for (int i = 0; i < emptyCells.size(); i++)
	{
		if (emptyCells[i].x == x + 1 && emptyCells[i].y == y + 1) {

			emptyCells.erase(emptyCells.begin() + i);
			break;
		}
	}

	return true;
}

void Board::printBoard() {
	cout << "    ";
	for (int j = 0; j < col; j++) {
		cout << j + 1 << "   ";
	}
	cout << endl;

	for (int i = 0; i < row; i++) {
		cout << "  ";
		for (int j = 0; j < col; j++) {
			cout << " ---";
		}
		cout << endl;

		cout << (i + 1) << " |";

		for (int j = 0; j < col; j++) {
			if (grid[i][j] == 0) {
				cout << "   |";
			}
			else if (grid[i][j] > 0) {
				cout << " " << grid[i][j] << " |";
			}
			else if (grid[i][j] < 0) {
				cout << "" << grid[i][j] << " |";
			}
		}
		cout << endl;
	}
	cout << "  ";

	for (int j = 0; j < col; j++) {
		cout << " ---";
	}
	cout << endl << endl;
}

#endif