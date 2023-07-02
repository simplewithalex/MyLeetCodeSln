#include "header.h"

/*

给定一个 m x n 整数矩阵 matrix，找出其中最长递增路径的长度
对于每个单元格，你可以往上，下，左，右四个方向移动。你不能在对角线方向上移动或移动到边界外（即不允许环绕）

示例 1：
输入：matrix = [[9,9,4],[6,6,8],[2,1,1]]
输出：4
解释：最长递增路径为 [1, 2, 6, 9]

示例 2：
输入：matrix = [[3,4,5],[3,2,6],[2,2,1]]
输出：4
解释：最长递增路径是 [3, 4, 5, 6]。注意不允许在对角线方向上移动

示例 3：
输入：matrix = [[1]]
输出：1

提示：
m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
0 <= matrix[i][j] <= 2^31 - 1

*/

// DFS
class Solution1 {
private:
	static constexpr int dirs[4][2] = { { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } };
	int rows;
	int cols;

public:
	int longestIncreasingPath(vector<vector<int>> &matrix) {
		if (matrix.empty() || matrix[0].empty()) return 0;
		rows = matrix.size(), cols = matrix[0].size();
		vector<vector<int>> memo(rows, vector<int>(cols, 0));
		int ans = 0;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (!memo[i][j]) ans = max(ans, dfs(matrix, i, j, memo));
			}
		}
		return ans;
	}

private:
	int dfs(vector<vector<int>> &matrix, int row, int col,
		vector<vector<int>> &memo) {
		if (memo[row][col]) return memo[row][col];
		int ans = 1;
		for (auto dir : dirs) {
			int newRow = row + dir[0];
			int newCol = col + dir[1];
			if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
				matrix[newRow][newCol] > matrix[row][col]) {
				ans = max(ans, dfs(matrix, newRow, newCol, memo) + 1);
			}
		}
		return memo[row][col] = ans;
	}
};

// 将DFS改为动态规划
class Solution2 {
private:
	static constexpr int dirs[4][2] = { { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } };
	int rows;
	int cols;

public:
	int longestIncreasingPath(vector<vector<int>> &matrix) {
		if (matrix.empty() || matrix[0].empty()) return 0;
		int rows = matrix.size(), cols = matrix[0].size();
		// 保存节点值和坐标
		vector<vector<int>> points;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				points.push_back({ matrix[i][j], i, j });
			}
		}
		sort(points.begin(), points.end(),
			[](const vector<int> &a, const vector<int> &b) {
			return a[0] > b[0];
		});

		int ans = 0;
		vector<vector<int>> dp(rows, vector<int>(cols, 1));
		for (auto p : points) {
			int val = p[0];
			int row = p[1], col = p[2];
			for (auto dir : dirs) {
				int newRow = row + dir[0], newCol = col + dir[1];
				if (newRow >= 0 && newRow < rows && newCol >= 0 &&
					newCol < cols && matrix[newRow][newCol] > matrix[row][col]) {
					dp[row][col] = max(dp[row][col], dp[newRow][newCol] + 1);
				}
			}
			ans = max(ans, dp[row][col]);
		}
		return ans;
	}
};


// BFS + 拓扑排序
class Solution3 {
private:
	static constexpr int dirs[4][2] = { { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } };
	int rows;
	int cols;

public:
	int longestIncreasingPath(vector<vector<int>> &matrix) {
		if (matrix.empty() || matrix[0].empty()) return 0;
		int rows = matrix.size(), cols = matrix[0].size();
		vector<vector<int>> outDegree(rows, vector<int>(cols, 0));
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				for (auto dir : dirs) {
					int newRow = i + dir[0], newCol = j + dir[1];
					if (newRow >= 0 && newRow < rows && newCol >= 0 &&
						newCol < cols &&
						matrix[newRow][newCol] > matrix[i][j]) {
						++outDegree[i][j];
					}
				}
			}
		}

		queue<vector<int>> q;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (outDegree[i][j] == 0)
					q.push({ i, j });
			}
		}

		int ans = 0;
		while (!q.empty()) {
			++ans;
			int len = q.size();
			for (int i = 0; i < len; ++i) {
				vector<int> pos = q.front();
				q.pop();
				int row = pos[0], col = pos[1];
				for (auto dir : dirs) {
					int newRow = row + dir[0], newCol = col + dir[1];
					if (newRow >= 0 && newRow < rows && newCol >= 0 &&
						newCol < cols &&
						matrix[newRow][newCol] < matrix[row][col]) {
						if (--outDegree[newRow][newCol] == 0)
							q.push({ newRow, newCol });
					}
				}
			}
		}
		return ans;
	}
};

