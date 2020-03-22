#include "header.h"

/*

给定一个二维的矩阵，包含 'X' 和 'O'（字母 O）。
找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。

示例:

X X X X
X O O X
X X O X
X O X X

运行你的函数后，矩阵变为：

X X X X
X X X X
X X X X
X O X X
解释:

被围绕的区间不会存在于边界上，换句话说，任何边界上的 'O' 都不会被填充为 'X'。 
任何不在边界上，或不与边界上的 'O' 相连的 'O' 最终都会被填充为 'X'。
如果两个元素在水平或垂直方向相邻，则称它们是“相连”的。

*/

//DFS
class Solution1 {
public:
	void solve(vector<vector<char>> &board)
	{
		if (board.empty() || board[0].empty()) return;
		int rows = board.size(), cols = board[0].size();
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if ((i == 0 || i == rows - 1 || j == 0 || j == cols - 1) && board[i][j] == 'O')
					helper(board, i, j, rows, cols);
			}
		}
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if (board[i][j] == 'O') board[i][j] = 'X';
				if (board[i][j] == '#') board[i][j] = 'O';
			}
		}
	}
	void helper(vector<vector<char>> &board, int i, int j, int rows, int cols)
	{
		if (i < 0 || j < 0 || i >= rows || j >= cols || board[i][j] == 'X' || board[i][j] == '#') return;
		board[i][j] = '#';
		helper(board, i - 1, j, rows, cols);
		helper(board, i + 1, j, rows, cols);
		helper(board, i, j - 1, rows, cols);
		helper(board, i, j + 1, rows, cols);
	}
};

//并查集
class UF {
private:
	vector<int> id;
public:
	UF(int total)
	{
		for (int i = 0; i < total; ++i) id.push_back(i);
	}
	int find(int x)
	{
		if (id[x] != x) id[x] = find(id[x]);
		return id[x];
	}
	void unionpq(int p, int q)
	{
		int pRoot = find(p);
		int qRoot = find(q);
		if (pRoot == qRoot) return;
		id[pRoot] = qRoot;
	}
	bool isConnected(int p, int q)
	{
		return find(p) == find(q);
	}
};

class Solution2 {
public:
	void solve(vector<vector<char>> &board)
	{
		if (board.empty() || board[0].empty()) return;
		int rows = board.size(), cols = board[0].size();
		UF uf(rows*cols + 1);
		int dummyNode = rows*cols;
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if (board[i][j] == 'O')
				{
					if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1)
					{
						uf.unionpq(i*cols + j, dummyNode);
					}
					else
					{
						if (board[i - 1][j] == 'O')
							uf.unionpq(i*cols + j, (i - 1)*cols + j);
						if (board[i + 1][j] == 'O')
							uf.unionpq(i*cols + j, (i + 1)*cols + j);
						if (board[i][j - 1] == 'O')
							uf.unionpq(i*cols + j, i*cols + j - 1);
						if (board[i][j + 1] == 'O')
							uf.unionpq(i*cols + j, i*cols + j + 1);
					}
				}
			}
		}
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if (!uf.isConnected(i*cols + j, dummyNode)) board[i][j] = 'X';
			}
		}
	}
};

//https://leetcode-cn.com/problems/surrounded-regions/solution/bfsdi-gui-dfsfei-di-gui-dfsbing-cha-ji-by-ac_pipe/