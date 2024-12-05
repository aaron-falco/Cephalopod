#ifndef MINMAXPLAYER_H_
#define MINMAXPLAYER_H_

class MinMaxPlayer : public Player {
public:
	MinMaxPlayer(int t) : Player("MinMax", t) {}
	void getMove(Board board, int& x, int& y);
	int steps;

	double maxMove(Board);
	double minMove(Board);
};


void MinMaxPlayer::getMove(Board board, int& x, int& y) {

	priority_queue<Cell> moves;

	int row = board.getRow();
	int col = board.getCol();

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			steps = 1000;
			Board tempBoard(board);
			if (!tempBoard.validMove(i, j)) {
				continue;
			}

			tempBoard.addMove(i, j);
			if (tempBoard.isBoardFull()) {
				if (tempBoard.checkWinningStatus() == type) {
					x = i;
					y = j;
					return;
				}
				else {
					continue;
				}
			}

			double mini = minMove(tempBoard);
			Cell cell(i, j, mini, 0);
			moves.push(cell);
		}

	}
	if (moves.size() > 0) {
		x = moves.top().x;
		y = moves.top().y;
		std::cout << moves.size() << " MiniMax Utility = " << moves.top().heuristic
			<< " at (" << (x + 1) << "," << (y + 1) << ")" << endl;
	}

	return;
}

double MinMaxPlayer::maxMove(Board board) {

	int row = board.getRow();
	int col = board.getCol();

	if (board.isBoardFull() || steps <= 0) {
		return 0.01;
	}

	double maxi = -10;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			Board tempBoard(board);
			if (!tempBoard.validMove(i, j)) {
				continue;
			}
			tempBoard.addMove(i, j);
			if (tempBoard.isBoardFull()) {
				int winner = tempBoard.checkWinningStatus();
				if (winner == type) {
					return 1;
				}
				else if (winner == 0) {
					return 0;
				}
				else {
					return -1;
				}
			}

			double value = minMove(tempBoard);

			if (value > maxi) {
				maxi = value;
			}
		}

	}

	steps--;
	return maxi;
}

double MinMaxPlayer::minMove(Board board) {

	int row = board.getRow();
	int col = board.getCol();

	if (board.isBoardFull() || steps <= 0) {
		return 0.01;
	}

	double mini = 10;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			Board tempBoard(board);
			if (!tempBoard.validMove(i, j)) {
				continue;
			}
			tempBoard.addMove(i, j);
			if (tempBoard.isBoardFull()) {
				int winner = tempBoard.checkWinningStatus();
				if (winner == type) {
					return 1;
				}
				else if (winner == 0) {
					return 0;
				}
				else {
					return -1;
				}
			}

			double value = maxMove(tempBoard);

			if (value < mini) {
				mini = value;
			}
		}

	}

	steps--;
	return mini;
}
#endif