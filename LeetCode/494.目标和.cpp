#include "header.h"

/*

给定一个非负整数数组，a1, a2, ..., an, 和一个目标数 S。
现在你有两个符号 + 和 -。对于数组中的任意一个整数，你都可以从 + 或 -中选择一个符号添加在前面。
返回可以使最终数组和为目标数 S 的所有添加符号的方法数。

示例 1:
输入: nums: [1, 1, 1, 1, 1], S: 3
输出: 5

解释:
-1+1+1+1+1 = 3
+1-1+1+1+1 = 3
+1+1-1+1+1 = 3
+1+1+1-1+1 = 3
+1+1+1+1-1 = 3

一共有5种方法让最终目标和为3。

注意:
数组非空，且长度不会超过20。
初始的数组的和不会超过1000。
保证返回的最终结果能被32位整数存下。

*/

//记忆化搜索
//重复情况不多，比较勉强。
class Solution1 {
public:
	int findTargetSumWays(vector<int> &nums, int S)
	{
		if (nums.empty()) return 0;
		int len = nums.size();
		vector<unordered_map<long long, int>> memo(len);
		return helper(nums, S, 0, memo);
	}
	int helper(vector<int> &nums, long long sum, int index, vector<unordered_map<long long, int>> &memo)
	{
		int len = nums.size();
		if (index == len) return sum == 0 ? 1 : 0;
		if (memo[index].count(sum)) return memo[index][sum];
		memo[index][sum] = helper(nums, sum - nums[index], index + 1, memo) + helper(nums, sum + nums[index], index + 1, memo);
		return memo[index][sum];
	}
};

//自底而上动态规划
//dp[i][j] 表示用数组中的前 i 个元素，组成和为 j 的方案数
//状态转移方程：dp[i][j] = dp[i - 1][j - nums[i]] + dp[i - 1][j + nums[i]]
class Solution2 {
public:
	int findTargetSumWays(vector<int> &nums, int S)
	{
		int sum = 0;
		for (int n : nums) sum += n;
		if (S < -sum || S > sum)  return 0;
		int len = nums.size();
		vector<vector<int>> dp(len + 1, vector<int>(sum * 2 + 1, 0));
		dp[0][0 + sum] = 1; // 0 + sum means 0, 0 means -sum
		for (int i = 1; i <= len; ++i)
		{
			for (int j = 0; j < 2 * sum + 1; ++j)
			{
				if (j + nums[i - 1] < 2 * sum + 1) dp[i][j] = dp[i - 1][j + nums[i - 1]];
				if (j - nums[i - 1] >= 0) dp[i][j] += dp[i - 1][j - nums[i - 1]];
			}
		}
		return dp[len][sum + S];
	}
};

//优化为两个一维数组
class Solution3 {
public:
	int findTargetSumWays(vector<int> &nums, int S)
	{
		int sum = 0;
		for (int n : nums) sum += n;
		if (S < -sum || S > sum)  return 0;
		int len = nums.size();
		vector<int> dp(sum * 2 + 1, 0);
		dp[sum] = 1;
		for (int i = 1; i <= len; ++i)
		{
			vector<int> next(sum * 2 + 1, 0);
			for (int j = 0; j < 2 * sum + 1; ++j)
			{
				if (j + nums[i - 1] < 2 * sum + 1) next[j] = dp[j + nums[i - 1]];
				if (j - nums[i - 1] >= 0) next[j] += dp[j - nums[i - 1]];
			}
			dp = next;
		}
		return dp[S + sum];
	}
};

//转换为0-1背包问题
class Solution4 {
public:
	int findTargetSumWays(vector<int> &nums, int S) {
		int sum = accumulate(nums.begin(), nums.end(), 0);
		if (S < -sum || S > sum) return 0;
		if ((sum + S) & 1) return 0;
		int len = nums.size();
		sum = (sum + S) >> 1;
		vector<vector<int>> dp(len + 1, vector<int>(sum + 1, 0));
		dp[0][0] = 1;
		for (int i = 1; i <= len; i++)
		{
			for (int j = 0; j <= sum; ++j)
			{
				if (j >= nums[i - 1])
				{
					dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i - 1]];
				}
				else
				{
					dp[i][j] = dp[i - 1][j];
				}
			}
		}
		return dp[len][sum];
	}
};
//背包问题可以进一步优化成一维数组
//https://leetcode-cn.com/problems/target-sum/solution/python-dfs-xiang-jie-by-jimmy00745/
