#include "header.h"

/*

给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。

示例 1:
输入: coins = [1, 2, 5], amount = 11
输出: 3
解释: 11 = 5 + 5 + 1

示例 2:
输入: coins = [2], amount = 3
输出: -1

说明:
你可以认为每种硬币的数量是无限的。

*/

//备忘录方法
class Solution1 {
public:
	int coinChange(vector<int> &coins, int amount)
	{
		vector<int> memo(amount + 1, -2);
		return helper(coins, amount, memo);
	}
	int helper(vector<int> &coins, int amount, vector<int> &memo)
	{
		if (amount == 0) return 0;
		if (memo[amount] != -2) return memo[amount];
		int res = INT_MAX;
		for (int coin : coins)
		{
			if (amount - coin < 0) continue;
			int sub = helper(coins, amount - coin, memo);
			if (sub == -1) continue;
			res = min(res, sub + 1);
		}
		memo[amount] = (res == INT_MAX ? -1 : res);
		return memo[amount];
	}
};
//https://leetcode-cn.com/problems/coin-change/solution/dong-tai-gui-hua-tao-lu-xiang-jie-by-wei-lai-bu-ke/

//自底而上动态规划方法
class Solution2 {
public:
	int coinChange(vector<int> &coins, int amount)
	{
		vector<int> dp(amount + 1, amount + 1);
		dp[0] = 0;
		for (int i = 1; i <= amount; ++i)
		{
			for (int coin : coins)
			{
				if (coin <= i)
					dp[i] = min(dp[i], dp[i - coin] + 1);
			}
		}
		return dp[amount] == amount + 1 ? -1 : dp[amount];
	}
};
//https://leetcode-cn.com/problems/coin-change/solution/dong-tai-gui-hua-tao-lu-xiang-jie-by-wei-lai-bu-ke/