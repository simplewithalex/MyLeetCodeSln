#include "header.h"

/*

给定一个二维网格和一个单词，找出该单词是否存在于网格中。
单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
同一个单元格内的字母不允许被重复使用。

示例:
board =
[
 ['A','B','C','E'],
 ['S','F','C','S'],
 ['A','D','E','E']
]

给定 word = "ABCCED", 返回 true.
给定 word = "SEE", 返回 true.
给定 word = "ABCB", 返回 false.

*/

class Solution {
public:
	bool exist(vector<vector<char>> &board, string word)
	{
		for (int i = 0; i < board.size(); ++i)
		{
			for (int j = 0; j < board[0].size(); ++j)
			{
				if (backTrack(board, i, j, word, 0))
					return true;
			}
		}
		return false;
	}
	bool backTrack(vector<vector<char>> &board, int i, int j, string &word, int index)
	{
		if (index == word.size()) return true;
		if (i>board.size() - 1 || i < 0 || j<0 || j>board[0].size() - 1 || board[i][j] != word[index])
			return false;
		board[i][j] = '*';
		bool result = backTrack(board, i - 1, j, word, index + 1) ||
			backTrack(board, i + 1, j, word, index + 1) ||
			backTrack(board, i, j - 1, word, index + 1) ||
			backTrack(board, i, j + 1, word, index + 1);
		board[i][j] = word[index];
		return result;
	}
};