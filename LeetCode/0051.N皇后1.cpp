#include "header.h"

/*

n 皇后问题研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
给定一个整数 n，返回所有不同的 n 皇后问题的解决方案。
一种解法包含一个明确的 n 皇后问题的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

示例:

输入: 4
输出: [
 [".Q..",  // 解法 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // 解法 2
  "Q...",
  "...Q",
  ".Q.."]
]
解释: 4 皇后问题存在两个不同的解法。

*/

class Solution {
public:
	std::vector<std::vector<std::string>> solveNQueens(int n)
	{
		std::vector<std::vector<std::string>> res;
		std::vector<std::string> nQueens(n, std::string(n, '.'));
		// 避免使用vector<bool>
		// 棋盘共有n列，正斜行有2n-1列，反斜行有2n-1列，共需要5n-2个标志空间
		// 不需要考虑行，因为每次选取都在不同行
		std::vector<int> flag(5 * n - 2, 0);
		solveNQueens(res, nQueens, flag, 0, n);
		return res;
	}
private:
	void solveNQueens(std::vector<std::vector<std::string>> &res, std::vector<std::string> &nQueens, std::vector<int> &flag, int row, int n)
	{
		if (row == n)
		{
			res.push_back(nQueens);
			return;
		}
		for (int col = 0; col != n; ++col)
		{
			if (flag[col] || flag[n + row + col] || flag[4 * n - 2 + col - row])
				continue;
			flag[col] = flag[n + row + col] = flag[4 * n - 2 + col - row] = 1;
			nQueens[row][col] = 'Q';
			solveNQueens(res, nQueens, flag, row + 1, n);
			nQueens[row][col] = '.';
			flag[col] = flag[n + row + col] = flag[4 * n - 2 + col - row] = 0;
		}
	}
};
// https://leetcode.com/problems/n-queens/discuss/19808/Accepted-4ms-c%2B%2B-solution-use-backtracking-and-bitmask-easy-understand