#include "header.h"

/*

给定一个包含非负整数的 m x n 网格，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
说明：每次只能向下或者向右移动一步。

示例:

输入:
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
输出: 7
解释: 因为路径 1→3→1→1→1 的总和最小。

*/

class Solution {
public:
	int minPathSum(vector<vector<int> > &grid)
	{
		if (grid.empty()) return 0;
		int rows = grid.size();
		int cols = grid[0].size();
		vector<int> dp(rows, grid[0][0]);
		for (int i = 1; i<rows; ++i)
		{
			dp[i] = dp[i - 1] + grid[i][0];
		}
		for (int i = 1; i<cols; ++i)
		{
			dp[0] += grid[0][i];
			for (int j = 1; j<rows; ++j)
				dp[j] = min(dp[j], dp[j - 1]) + grid[j][i];
		}
		return dp[rows - 1];
	}
};
