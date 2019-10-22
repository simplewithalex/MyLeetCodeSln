#include "header.h"

/*

编写一个程序，通过已填充的空格来解决数独问题。
一个数独的解法需遵循如下规则：
数字 1-9 在每一行只能出现一次。
数字 1-9 在每一列只能出现一次。
数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
空白格用 '.' 表示。

*/

class Solution {
public:
	void solveSudoku(vector<vector<char>> &board)
	{
		if (board.empty() || board[0].empty())
			return;
		solve(board);
	}
	bool solve(vector<vector<char>> &board)
	{
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
			{
				if (board[i][j] == '.')
				{
					for (char c = '1'; c <= '9'; ++c)
					{
						if (isValid(board, i, j, c))
						{
							board[i][j] = c;
							if (solve(board))
								return true;
							else
								board[i][j] = '.';
						}
					}
					return false;
				}
			}
		}
		return true;
	}
	bool isValid(vector<vector<char>> &board, int row, int col, char c)
	{
		for (int i = 0; i < 9; ++i)
		{
			if (board[i][col] == c)
				return false;
			if (board[row][i] == c)
				return false;
			if (board[(row / 3) * 3 + i / 3][(col / 3) * 3 + i % 3] == c)
				return false;
		}
		return true;
	}
};
//https://leetcode.com/problems/sudoku-solver/discuss/15752/Straight-Forward-Java-Solution-Using-Backtracking