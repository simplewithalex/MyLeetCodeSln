#include "header.h"

/*

n皇后问题研究的是如何将n个皇后放置在n×n的棋盘上，并且使皇后彼此之间不能相互攻击。
给你一个整数 n ，返回 n 皇后问题不同的解决方案的数量。

示例 1：
输入：n = 4
输出：2
解释：如上图所示，4 皇后问题存在两个不同的解法。

示例 2：
输入：n = 1
输出：1

提示：
1 <= n <= 9
皇后彼此不能相互攻击，也就是说：任何两个皇后都不能处于同一条横行、纵行或斜线上。

*/

// 参考 0051.N皇后1
class Solution1 {
public:
	int totalNQueens(int n) {
		int res = 0;
		std::vector<char> flag(5 * n - 2, 0);
		solveNQueens(res, flag, 0, n);
		return res;
	}
private:
	void solveNQueens(int &res, std::vector<char> &flag, int row, int n) {
		if (row == n) {
			++res;
			return;
		}
		for (int col = 0; col < n; ++col) {
			if (flag[col] || flag[row + col + n] || flag[4 * n - 2 + col - row]) continue;
			flag[col] = flag[n + row + col] = flag[4 * n - 2 + col - row] = 1;
			solveNQueens(res, flag, row + 1, n);
			flag[col] = flag[n + row + col] = flag[4 * n - 2 + col - row] = 0;
		}
	}
};

// 优化为位运算方法
class Solution2 {
public:
	int totalNQueens(int n) {
		int res = 0;
		solveNQueens(res, 0, 0, 0, 0, n);
		return res;
	}
private:
	// 棋盘每一行从左到右对应二进位的从右到左，方便运算
	void solveNQueens(int &res, int columns, int diagonals1, int diagonals2, int row, int n) {
		if (row == n) {
			++res;
			return;
		}
		int availablePosition = ((1 << n) - 1) & (~(columns | diagonals1 | diagonals2));
		while (availablePosition) {
			int position = availablePosition&(-availablePosition);
			availablePosition = availablePosition&(availablePosition - 1);
			solveNQueens(res, columns | position, (diagonals1 | position) << 1, (diagonals2 | position) >> 1, row + 1, n);
		}
	}
};
// https://leetcode-cn.com/problems/n-queens-ii/solution/nhuang-hou-ii-by-leetcode-solution/
// 同样可以运用在 0051.N皇后1
