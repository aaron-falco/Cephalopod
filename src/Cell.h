#ifndef CELL_H_
#define CELL_H_

struct Cell {
	int x;
	int y;
	int heuristic;
	int value;

	Cell(int xx, int yy, int hh, int vv) :x(xx), y(yy), heuristic(hh), value(vv) {}

	bool operator<(const Cell& c) const {
		return heuristic < c.heuristic;
	}

};



#endif