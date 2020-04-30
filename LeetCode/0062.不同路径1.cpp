#include "header.h"

/*

一个机器人位于一个 m x n 网格的左上角。
机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角。
问总共有多少条不同的路径？

示例 1:

输入: m = 2, n = 3  
输出: 3
解释:
从左上角开始，总共有 3 条路径可以到达右下角。
1. 向右 -> 向右 -> 向下
2. 向右 -> 向下 -> 向右
3. 向下 -> 向右 -> 向右

示例 2:
输入: m = 3, n = 7
输出: 28

*/

//自顶向下备忘录
class Solution1 {
public:
	int uniquePaths(int m, int n)
	{
		if (m <= 0 || n <= 0) return 0;
		vector<vector<int>> memo(n + 1, vector<int>(m + 1, 0));
		return helper(m, n, memo);
	}
	int helper(int m, int n,vector<vector<int>> &memo)
	{
		if (m == 1 || n == 1) return 1;
		if (memo[n][m] > 0) return memo[n][m];
		memo[n][m] = helper(m - 1, n, memo) + helper(m, n - 1, memo);
		return memo[n][m];
	}
};

//自底向上的动态规划
class Solution2 {
public:
	int uniquePaths(int m, int n)
	{
		if (m <= 0 || n <= 0) return 0;
		vector<vector<int>> dp(n, vector<int>(m, 0));
		for (int i = 0; i < n; ++i) dp[i][0] = 1;
		for (int i = 0; i < m; ++i) dp[0][i] = 1;
		for (int i = 1; i < n; ++i)
			for (int j = 1; j < m; ++j)
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		return dp[n - 1][m - 1];
	}
};

class Solution3 {
public:
	int uniquePaths(int m, int n)
	{
		if (m <= 0 || n <= 0) return 0;
		vector<int> dp(n, 1);
		for (int i = 1; i < m; ++i)
			for (int j = 1; j < n; ++j)
				dp[j] += dp[j - 1];
		return dp[n - 1];
	}
};