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
		sort(nums.begin(), nums.end(), greater<int>());
		return !(sum & 1) && helper(nums, 0, sum >> 1);
	}
	bool helper(vector<int> &nums, int index, int target)
	{
		int len = nums.size();
		if (target <= 0) return target == 0;
		//递归的含义为是否选取当前数参与到对目标数的运算中
		for (int i = index; i < len; ++i)
		{
			if (target - nums[i] < 0) break;
			if (helper(nums, i + 1, target - nums[i])) return true;
		}
		return false;
	}
};

//二维动态规划
class Solution2 {
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
				if (nums[i - 1] <= j) dp[i][j] = dp[i][j] || dp[i - 1][j - nums[i - 1]];
			}
		}
		return dp[len][target];
	}
};

//优化为一维动态规划
class Solution3 {
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