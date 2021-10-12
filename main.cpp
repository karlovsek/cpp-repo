#include "PegSolitaire.hpp"

#include <iostream> 
#include <chrono>
#include <algorithm>

vector<Direction> ps::directions { Direction(0, 1), Direction(0, -1), Direction(-1, 0), Direction(1, 0) };

size_t ps::count_pegs(board english_board)
{
	size_t sum = 0;
	
	for (auto& v : english_board) {
		sum += count(v.begin(), v.end(), '1');
	}
	return (sum);
}

board ps::get_english_board()
{
	auto english_board = board(board_size, vector<char>(board_size, '1'));

	english_board.at(middle_index).at(middle_index) = '0';
	for (int index = 0; index < 2; index++) {
		int reverse_index = board_size - 1 - index;

		for (int inner_index = 0; inner_index < 2; inner_index++) {
			int reverse_inner_index = board_size - 1 - inner_index;

			english_board.at(index).at(inner_index) = ' ';
			english_board.at(index).at(reverse_inner_index) = ' ';
			english_board.at(reverse_index).at(reverse_inner_index) = ' ';
			english_board.at(reverse_index).at(inner_index) = ' ';
		}

	}
	return (english_board);
}

void ps::print(board english_board)
{
	for_each(english_board.begin(), english_board.end(), [](vector<char> line) {
		for_each(line.begin(), line.end(), [](char c) {
			cout << c;
			});
		cout << "\n";
	});
}

vector<board> ps::solve(board english_board)
{
	vector<board> moves;
	bool no_solution = true;
	size_t x_size = english_board.size();

	for (int idx = 0; idx < x_size; idx++) {
		size_t y_size = english_board[idx].size();
		for (int idy = 0; idy < y_size; idy++) {
			if (english_board[idy][idx] == '1') {
				for (auto& direction : directions) {
					int posx = idx + direction.X();
					int posy = idy + direction.Y();
					int posxx = posx + direction.X();
					int posyy = posy + direction.Y();

					if ((posx >= 0) && (posy >= 0) && (posxx >= 0) && (posyy >= 0) && (posxx < x_size) && (posyy < y_size)) {
						if ((english_board[posy][posx] == '1') && (english_board[posyy][posxx] == '0')) {
							no_solution = false;
							english_board[idy][idx] = '0';
							english_board[posy][posx] = '0';
							english_board[posyy][posxx] = '1';
							/*print(english_board);
							std::cout << "---------------\n";*/
						    moves = solve(english_board);
							if (moves.size() == 0) {
								english_board[idy][idx] = '1';
								english_board[posy][posx] = '1';
								english_board[posyy][posxx] = '0';
								/*print(english_board);
								std::cout << "---------------\n";*/
							}
							else {
								if (count_pegs(english_board) > 1) {
									moves.insert(moves.begin(), english_board);
								}
								idx = x_size;
								idy = y_size;
							}
						}
					}
				}
			}
		}
	}
	if (no_solution)
	{
		if ((count_pegs(english_board) == 1) && (english_board[middle_index][middle_index] == '1')) {
			moves.push_back(english_board);
		}
	}
	return (moves);
}

void ps::print_moves(vector<board> results)
{
	for (auto& v : results) {
		print(v);
		std::cout << "---------------\n";
	}
}

int main()
{
	using namespace std::chrono;
	auto const english_board = ps::get_english_board();

	std::cout << "Start solving:\n";
	ps::print(english_board);
	std::cout << "---------------\n";

	auto const start = high_resolution_clock::now();

	// Solving board e.g.
	// 
	// Add your code
	// 
	// ps::solve(english_board, moves); or
	const auto moves = ps::solve(english_board);
	//ps::test(english_board);

	auto end = high_resolution_clock::now();
	auto duration_ms = duration_cast<duration<double, std::milli>>(end - start).count();

	// Print moves
	//
	// Add your code
	// e.g.
	ps::print_moves(moves);
	std::cout << "Solving took: " << duration_ms << " ms\n";

	/*
	Output example:
	~~~~~~~~~~~~~~~~
	Start solving:
	111
	111
  1111111
  1110111
  1111111
	111
	111
  ---------------
	111
	111
  1111111
  1110111
  1111111
	111
	111
	111
	111
  1111111
  1111001
  1111111
	111
	111
  [ ... omitted ...]
	000
	000
  0000000
  0000000
  0001000
	010
	000
	000
	000
  0000000
  0000000
  0000000
	000
	010
  Solving took: 492.057 ms
	*/

	return 0;
}