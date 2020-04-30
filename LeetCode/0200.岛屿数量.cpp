#include "header.h"

/*

给定一个由 '1'（陆地）和 '0'（水）组成的的二维网格，计算岛屿的数量。
一个岛被水包围，并且它是通过水平方向或垂直方向上相邻的陆地连接而成的。你可以假设网格的四个边均被水包围。

示例 1:

输入:
11110
11010
11000
00000
输出: 1

示例 2:

输入:
11000
11000
00100
00011
输出: 3

*/


//深度优先搜索
class Solution1 {
public:
	int numIslands(vector<vector<char>> &grid)
	{
		if (grid.empty() || grid[0].empty()) return 0;
		int rows = grid.size(), cols = grid[0].size();
		int res = 0;
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if (grid[i][j] == '1')
				{
					dfs(grid, i, j, rows, cols);
					res += 1;
				}
			}
		}
		return res;
	}
	void dfs(vector<vector<char>> &grid, int row, int col, int rows, int cols)
	{
		if (row < 0 || col < 0 || row >= rows || col >= cols || grid[row][col] != '1') return;
		grid[row][col] = '0';
		dfs(grid, row + 1, col, rows, cols);
		dfs(grid, row - 1, col, rows, cols);
		dfs(grid, row, col + 1, rows, cols);
		dfs(grid, row, col - 1, rows, cols);
	}
};

//并查集方法
class UF {
private:
	vector<int> id;
public:
	int count = 0;
	UF(vector<vector<char>> &grid, int rows, int cols)
	{
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if (grid[i][j] == '1')
				{
					id.push_back(i*cols + j);
					++count;
				}
				else
				{
					id.push_back(-1);
				}
			}
		}
	}
	int find(int x)
	{
		if (id[x] != x) id[x] = find(id[x]);
		return id[x];
	}
	void unionIslands(int p, int q)
	{
		int pRoot = find(p);
		int qRoot = find(q);
		if (pRoot == qRoot) return;
		id[pRoot] = qRoot;
		--count;
	}
};

class Solution2 {
public:
	int numIslands(vector<vector<char>> &grid)
	{
		if (grid.empty() || grid[0].empty()) return 0;
		int rows = grid.size(), cols = grid[0].size();
		UF uf(grid, rows, cols);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if (grid[i][j] == '1')
				{
					int p = i*cols + j;
					if (j < cols - 1 && grid[i][j + 1] == '1')
					{
						int q = i*cols + j + 1;
						uf.unionIslands(p, q);
					}
					if (i < rows - 1 && grid[i + 1][j] == '1')
					{
						int q = (i + 1)*cols + j;
						uf.unionIslands(p, q);
					}
				}
			}
		}
		return uf.count;
	}
};