#ifndef COMPUTERPLAYER_H_
#define COMPUTERPLAYER_H_

class ComputerPlayer : public Player {
public:
	ComputerPlayer(int t) : Player("CPU", t) {}
	void getMove(Board board, int& x, int& y);
};


void ComputerPlayer::getMove(Board board, int& x, int& y)
{
	if (board.isBoardFull())
		return;

	//Get the empty cells from the board
	vector<Cell> emptyCells = board.returnEmptyCells();

	//Get the length of emptyCells to loop through it
	int len = emptyCells.size();

	//Create a priority queue of cells
	priority_queue<Cell> moves;

	//Loop through the emptyCells, and add them to moves after calculating their heuristic
	for (int i = 0; i < len; i++)
	{
		emptyCells[i].heuristic = board.heuristics(emptyCells[i].x, emptyCells[i].y);
		moves.push(emptyCells[i]);
	}

	//Set x and y to the x and y value of the top element of the priority queue (i.e. the cell with the highest heuristic)
	x = moves.top().x - 1;
	y = moves.top().y - 1;

}

#endif