#include "header.h"

/*

417. 太平洋大西洋水流问题

有一个 m × n 的矩形岛屿，与 太平洋 和 大西洋 相邻。 “太平洋” 处于大陆的左边界和上边界，而 “大西洋” 处于大陆的右边界和下边界

这个岛被分割成一个由若干方形单元格组成的网格。给定一个 m x n 的整数矩阵 heights ， heights[r][c] 表示坐标 (r, c) 上单元格 高于海平面的高度

岛上雨水较多，如果相邻单元格的高度 小于或等于 当前单元格的高度，雨水可以直接向北、南、东、西流向相邻单元格。水可以从海洋附近的任何单元格流入海洋

返回网格坐标 result 的 2D 列表 ，其中 result[i] = [ri, ci] 表示雨水从单元格 (ri, ci) 流动 既可流向太平洋也可流向大西洋

示例 1：
输入: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
输出: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]

示例 2：
输入: heights = [[2,1],[1,2]]
输出: [[0,0],[0,1],[1,0],[1,1]]

提示：
m == heights.length
n == heights[r].length
1 <= m, n <= 200
0 <= heights[r][c] <= 10^5

*/


const int dirs[4][2] = { { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } };

// BFS
class Solution1 {
public:
	vector<vector<int>> heights;
	void bfs(int row, int col, vector<vector<char>> &visited) {
		if (visited[row][col]) return;
		int rows = heights.size(), cols = heights[0].size();
		visited[row][col] = true;
		queue<vector<int>> q;
		q.push({ row, col });
		while (!q.empty()) {
			vector<int> tmp = q.front();
			q.pop();
			int row = tmp[0], col = tmp[1];
			for (int i = 0; i < 4; ++i) {
				int newRow = row + dirs[i][0], newCol = col + dirs[i][1];
				if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
					heights[newRow][newCol] >= heights[row][col] &&
					!visited[newRow][newCol]) {
					visited[newRow][newCol] = true;
					q.push({ newRow, newCol });
				}
			}
		}
	}
	vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights) {
		this->heights = heights;
		int rows = heights.size(), cols = heights[0].size();
		vector<vector<char>> pacific(rows, vector<char>(cols, false));
		vector<vector<char>> atlantic(rows, vector<char>(cols, false));
		for (int i = 0; i < rows; ++i) {
			bfs(i, 0, pacific);
		}
		for (int j = 0; j < cols; ++j) {
			bfs(0, j, pacific);
		}
		for (int i = 0; i < rows; ++i) {
			bfs(i, cols - 1, atlantic);
		}
		for (int j = 0; j < cols; ++j) {
			bfs(rows - 1, j, atlantic);
		}
		vector<vector<int>> result;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (pacific[i][j] && atlantic[i][j]) {
					result.push_back({ i, j });
				}
			}
		}
		return result;
	}
};


// DFS
class Solution2 {
public:
	vector<vector<int>> heights;
	vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
		this->heights = heights;
		int rows = heights.size(), cols = heights[0].size();
		vector<vector<char>> pacific(rows, vector<char>(cols, false));
		vector<vector<char>> atlantic(rows, vector<char>(cols, false));
		for (int i = 0; i < rows; ++i) {
			dfs(i, 0, pacific);
		}
		for (int j = 0; j < cols; ++j) {
			dfs(0, j, pacific);
		}
		for (int i = 0; i < rows; ++i) {
			dfs(i, cols - 1, atlantic);
		}
		for (int j = 0; j < cols; ++j) {
			dfs(rows - 1, j, atlantic);
		}
		vector<vector<int>> result;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (pacific[i][j] && atlantic[i][j]) {
					result.push_back({ i, j });
				}
			}
		}
		return result;
	}
	void dfs(int row, int col, vector<vector<char>>& visted) {
		int rows = visted.size();
		int cols = visted[0].size();
		if (visted[row][col]) return;
		visted[row][col] = true;
		for (int i = 0; i < 4; ++i) {
			int newRow = row + dirs[i][0], newCol = col + dirs[i][1];
			if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
				heights[newRow][newCol] >= heights[row][col]) {
				dfs(newRow, newCol, visted);
			}
		}
	}
};

