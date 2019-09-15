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


//典型的动态规划题目
//假设当n为5时，我们需要考虑1-5分别为根节点的情况，左子树和右子树分别能容纳的个数，
//然后运用动态规划求出。
class Solution {
public:
	int numTrees(int n)
	{
		if (n == 0) return 0;
		if (n == 1) return 1;
		vector<int> dp(n + 1);
		dp[0] = 1;
		dp[1] = 1;
		for (int i = 2; i <= n; ++i)
		{
			for (int j = 0; j<i; ++j)
			{
				dp[i] += dp[j] * dp[i - j - 1];
			}
		}
		return dp[n];
	}
};