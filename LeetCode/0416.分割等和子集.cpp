#include "header.h"

/*

给定一个只包含正整数的非空数组。是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

注意:
每个数组中的元素不会超过 100
数组的大小不会超过 200

示例 1:
输入: [1, 5, 11, 5]
输出: true
解释: 数组可以分割成 [1, 5, 5] 和 [11].

示例 2:
输入: [1, 2, 3, 5]
输出: false
解释: 数组不能分割成两个元素和相等的子集.

*/

//DFS
class Solution1 {
public:
	bool canPartition(vector<int> &nums)
	{
		int sum = accumulate(nums.begin(), nums.end(), 0);
		//记录失败路径
		unordered_set<string> memo;
		return !(sum & 1) && helper(nums, 0, sum >> 1, memo);
	}
	bool helper(vector<int> &nums, int index, int target, unordered_set<string> &memo)
	{
		int len = nums.size();
		if (target <= 0) return target == 0;
		string temp = to_string(index) + "#" + to_string(target);
		if (memo.count(temp)) return false;
		//递归的含义为是否选取当前数参与到对目标数的运算中
		for (int i = index; i < len; ++i)
		{
			if (helper(nums, i + 1, target - nums[i], memo)) return true;
		}
		memo.insert(temp);
		return false;
	}
};

//转化为 0 — 1 背包问题

//记忆化搜索
class Solution2 {
public:
	bool canPartition(vector<int>& nums) 
	{
		int len = nums.size();
		int sum = accumulate(nums.begin(), nums.end(), 0);
		if (sum & 1) return false;
		vector<vector<char>> memo(len, vector<char>((sum >> 1) + 1, 0));
		//从大到小排序降低搜索树
		sort(nums.begin(), nums.end(), greater<int>());
		return helper(nums, 0, sum >> 1, memo);
	}
	bool helper(vector<int> &nums, int index, int target, vector<vector<char>> &memo)
	{
		int len = nums.size();
		if (target == 0) return true;
		if (target < 0 || index == len) return false;
		if (memo[index][target] != 0) return memo[index][target] == 1;
		memo[index][target] = (helper(nums, index + 1, target - nums[index], memo) || helper(nums, index + 1, target, memo)) ? 1 : -1;
		return memo[index][target] == 1;
	}
};

//二维动态规划
class Solution3 {
public:
	bool canPartition(vector<int> &nums)
	{
		if (nums.empty()) return false;
		int len = nums.size();
		int sum = accumulate(nums.begin(), nums.end(), 0);
		if (sum & 1) return false;
		int target = sum >> 1;
		vector<vector<char>> dp(len + 1, vector<char>(target + 1, false));
		for (int i = 0; i < len + 1; ++i) dp[i][0] = true;
		for (int i = 1; i < target + 1; ++i) dp[0][i] = false;
		for (int i = 1; i < len + 1; ++i)
		{
			for (int j = 1; j < target + 1; ++j)
			{
				dp[i][j] = dp[i - 1][j];
				//选择当前数为dp[i - 1][j - nums[i - 1]]，不选择当前数为dp[i][j]
				if (nums[i - 1] <= j) dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i - 1]];
			}
		}
		return dp[len][target];
	}
};

//优化为一维动态规划
class Solution4 {
public:
	bool canPartition(vector<int> &nums)
	{
		if (nums.empty()) return false;
		int len = nums.size();
		int sum = accumulate(nums.begin(), nums.end(), 0);
		if (sum & 1) return false;
		int target = sum >> 1;
		vector<char> dp(target + 1, false);
		dp[0] = true;
		for (int n : nums)
		{
			for (int i = target; i > 0; --i)
			{
				if (n <= i) dp[i] = dp[i] || dp[i - n];
			}
		}
		return dp[target];
	}
};

//https://leetcode.com/problems/partition-equal-subset-sum/discuss/90592/01-knapsack-detailed-explanation