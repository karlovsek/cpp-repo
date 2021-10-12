#pragma once

class Direction
{
private:
	int _x;
	int _y;

public: 
	Direction(int x, int y)
	{
		_x = x;
		_y = y;
	}

	int X() { return(_x); }
	int Y() { return(_y); }
};
