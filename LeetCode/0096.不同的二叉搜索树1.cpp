#include "header.h"

/*

给定一个整数 n，求以 1 ... n 为节点组成的二叉搜索树有多少种？

示例:

输入: 3
输出: 5
解释:
给定 n = 3, 一共有 5 种不同结构的二叉搜索树:

	1         3     3      2      1
	 \       /     /      / \      \
	  3     2     1      1   3      2
	 /     /       \                 \
	2     1         2                 3

*/

//备忘录
class Solution1 {
public:
	int numTrees(int n)
	{
		if (n == 0) return 0;
		vector<int> memo(n + 1, 0);
		return helper(n, memo);
	}
	int helper(int n, vector<int> &memo)
	{
		if (memo[n] > 0) return memo[n];
		if (n <= 1) return 1;
		int res = 0;
		for (int i = 1; i <= n; ++i)
		{
			int left = helper(i - 1, memo);
			int right = helper(n - i, memo);
			res += left*right;
		}
		return memo[n] = res;
	}
};

//动态规划
//假设当n为5时，我们需要考虑1-5分别为根节点的情况，左子树和右子树分别能容纳的个数，
//然后运用动态规划求出。
class Solution2 {
public:
	int numTrees(int n)
	{
		if (n == 0) return 0;
		vector<int> dp(n + 1);
		dp[0] = 1;
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j <= i; ++j)
			{
				dp[i] += dp[j - 1] * dp[i - j];
			}
		}
		return dp[n];
	}
};