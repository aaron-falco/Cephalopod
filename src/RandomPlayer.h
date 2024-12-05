#ifndef RANDOMPLAYER_H_
#define RANDOMPLAYER_H_

class RandomPlayer : public Player {
public:
	RandomPlayer(int t) : Player("Rand", t) {}
	void getMove(Board board, int& x, int& y);
};


void RandomPlayer::getMove(Board board, int& x, int& y)
{
	if (board.isBoardFull())
		return;

	vector<Cell> emptyCells = board.returnEmptyCells();
	int counter = 0;

	do {
		if (counter > 1) {
			std::cout << endl << counter << endl;
		}
		int emptyCellsIndex = rand() % emptyCells.size();

		Cell choice = emptyCells[emptyCellsIndex];
		x = choice.x - 1;
		y = choice.y - 1;
		counter++;

	} while (!board.validMove(x, y));
}

#endif