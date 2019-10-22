#include "header.h"

/*

判断一个 9x9 的数独是否有效。只需要根据以下规则，验证已经填入的数字是否有效即可。
数字 1-9 在每一行只能出现一次。
数字 1-9 在每一列只能出现一次。
数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
数独部分空格内已填入了数字，空白格用 '.' 表示。

输入:
[
  ["5","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
输出: true

*/

class Solution
{
public:
	bool isValidSudoku(vector<vector<char>> &board)
	{
		unordered_set<string> s;
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
			{
				char ch = board[i][j];
				if (ch != '.')
				{
					if (!s.insert(to_string(ch) + "in row" + to_string(i)).second ||
						!s.insert(to_string(ch) + "in col" + to_string(j)).second ||
						!s.insert(to_string(ch) + "in block" + to_string(i / 3) + '-' + to_string(j / 3)).second)
						return false;
				}
			}
		}
		return true;
	}
};
//https://leetcode.com/problems/valid-sudoku/discuss/15472/Short%2BSimple-Java-using-Strings