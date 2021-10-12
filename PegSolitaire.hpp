#pragma once

#include "Direction.hpp"

#include <vector>

using namespace std;

typedef vector<vector<char>> board;

class ps
{
private:
	const static int board_size = 7;
	const static int middle_index = 3;
	
	static vector<Direction> directions;

	static size_t count_pegs(board english_board);

public:
	static board get_english_board();
	static vector<board> solve(board english_board);
	static void print(board english_board);
	static void print_moves(vector<board> results);
};