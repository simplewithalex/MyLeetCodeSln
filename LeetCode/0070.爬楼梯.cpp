#include "header.h"

/*

假设你正在爬楼梯。需要 n 阶你才能到达楼顶。每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

注意：给定 n 是一个正整数。

示例 1：
输入： 2
输出： 2
解释： 有两种方法可以爬到楼顶。
1.  1 阶 + 1 阶
2.  2 阶

示例 2：
输入： 3
输出： 3
解释： 有三种方法可以爬到楼顶。
1.  1 阶 + 1 阶 + 1 阶
2.  1 阶 + 2 阶
3.  2 阶 + 1 阶

*/

// 备忘录
class Solution1 {
public:
	int climbStairs(int n) {
		vector<int> memo(n + 1, 0);
		return helper(n, memo);
	}
	int helper(int n, vector<int> &memo) {
		if (n == 0 || n == 1) return 1;
		if (memo[n] != 0) return memo[n];
		return memo[n] = helper(n - 1, memo) + helper(n - 2, memo);
	}
};

// 自底而上动态规划
class Solution2 {
public:
	int climbStairs(int n) {
		if (n == 0 || n == 1) return 1;
		vector<int> dp(n + 1, 0);
		dp[0] = 1, dp[1] = 1;
		for (int i = 2; i <= n; ++i) {
			dp[i] = dp[i - 1] + dp[i - 2];
		}
		return dp[n];
	}
};

// 空间复杂度优化
class Solution3 {
public:
	int climbStairs(int n) {
		if (n == 0 || n == 1) return 1;
		int pre = 1, cur = 1;
		for (int i = 2; i <= n; ++i) {
			int tmp = pre + cur;
			pre = cur;
			cur = tmp;
		}
		return cur;
	}
};