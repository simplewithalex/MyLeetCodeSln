#include "header.h"

/*

1463. 摘樱桃 II

给你一个 rows x cols 的矩阵 grid 来表示一块樱桃地，grid 中每个格子的数字表示你能获得的樱桃数目

你有两个机器人帮你收集樱桃，机器人 1 从左上角格子 (0,0) 出发，机器人 2 从右上角格子 (0, cols-1) 出发

请你按照如下规则，返回两个机器人能收集的最多樱桃数目：
从格子 (i,j) 出发，机器人可以移动到格子 (i+1, j-1)，(i+1, j) 或者 (i+1, j+1)
当一个机器人经过某个格子时，它会把该格子内所有的樱桃都摘走，然后这个位置会变成空格子，即没有樱桃的格子
当两个机器人同时到达同一个格子时，它们中只有一个可以摘到樱桃
两个机器人在任意时刻都不能移动到 grid 外面
两个机器人最后都要到达 grid 最底下一行

示例 1：
输入：grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
输出：24
解释：机器人 1 和机器人 2 的路径在上图中分别用绿色和蓝色表示
机器人 1 摘的樱桃数目为 (3 + 2 + 5 + 2) = 12
机器人 2 摘的樱桃数目为 (1 + 5 + 5 + 1) = 12
樱桃总数为： 12 + 12 = 24

示例 2：
输入：grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]
输出：28
解释：机器人 1 和机器人 2 的路径在上图中分别用绿色和蓝色表示
机器人 1 摘的樱桃数目为 (1 + 9 + 5 + 2) = 17
机器人 2 摘的樱桃数目为 (1 + 3 + 4 + 3) = 11
樱桃总数为： 17 + 11 = 28

示例 3：
输入：grid = [[1,0,0,3],[0,0,0,3],[0,0,3,3],[9,0,3,3]]
输出：22

示例 4：
输入：grid = [[1,1],[1,1]]
输出：4

提示：
rows == grid.length
cols == grid[i].length
2 <= rows, cols <= 70
0 <= grid[i][j] <= 100

*/

// 记忆化回溯，j 和 k 区分左右轮廓
class Solution1 {
public:
	vector<vector<vector<int>>> memo;
	int cherryPickup(vector<vector<int>> &grid) {
		int rows = grid.size(), cols = grid[0].size();
		memo.resize(rows, vector<vector<int>>(cols, vector<int>(cols, -1)));
		return helper(grid, 0, 0, cols - 1);
	}
	int helper(vector<vector<int>> &grid, int i, int j, int k) {
		int rows = grid.size(), cols = grid[0].size();
		if (i == rows) return 0;
		if (j < 0 || j >= cols || k < 0 || k >= cols || k <= j) return INT_MIN;
		if (memo[i][j][k] != -1) return memo[i][j][k];
		int res = INT_MIN;
		for (int j2 = j - 1; j2 <= j + 1; ++j2) {
			for (int k2 = k - 1; k2 <= k + 1; ++k2) {
				res = max(res, helper(grid, i + 1, j2, k2));
			}
		}
		return memo[i][j][k] = res + grid[i][j] + grid[i][k];
	}
};

// 自底而上的动态规划
class Solution2 {
public:
	int cherryPickup(vector<vector<int>> &grid) {
		int rows = grid.size(), cols = grid[0].size();
		vector<vector<vector<int>>> dp(rows + 1,
			vector<vector<int>>(cols + 2, vector<int>(cols + 2)));
		for (int i = rows - 1; i >= 0; --i) {
			for (int j = 0; j <= min(cols - 1, i); ++j) {
				for (int k = max(j + 1, cols - 1 - i); k <= cols - 1; ++k) {
					dp[i][j + 1][k + 1] =
						max({ dp[i + 1][j][k], dp[i + 1][j][k + 1],
							dp[i + 1][j][k + 2], dp[i + 1][j + 1][k],
							dp[i + 1][j + 1][k + 1], dp[i + 1][j + 1][k + 2],
							dp[i + 1][j + 2][k], dp[i + 1][j + 2][k + 1],
							dp[i + 1][j + 2][k + 2] }) +
						grid[i][j] + grid[i][k];
				}
			}
		}
		return dp[0][1][cols];
	}
};


// 空间复杂度优化
class Solution3 {
public:
	int cherryPickup(vector<vector<int>> &grid) {
		int rows = grid.size(), cols = grid[0].size();
		vector<vector<int>> dp1(cols + 2, vector<int>(cols + 2));
		vector<vector<int>> dp2(cols + 2, vector<int>(cols + 2));
		for (int i = rows - 1; i >= 0; --i) {
			for (int j = 0; j <= min(cols - 1, i); ++j) {
				for (int k = max(j + 1, cols - 1 - i); k <= cols - 1; ++k) {
					dp1[j + 1][k + 1] =
						max({ dp2[j][k], dp2[j][k + 1], dp2[j][k + 2],
							dp2[j + 1][k], dp2[j + 1][k + 1],
							dp2[j + 1][k + 2], dp2[j + 2][k],
							dp2[j + 2][k + 1], dp2[j + 2][k + 2] }) +
						grid[i][j] + grid[i][k];
				}
			}
			swap(dp1, dp2);
		}
		return dp2[1][cols];
	}
};


