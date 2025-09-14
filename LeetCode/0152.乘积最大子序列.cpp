#include "header.h"

/*

给定一个整数数组 nums ，找出一个序列中乘积最大的连续子序列（该序列至少包含一个数）

示例 1:
输入: [2,3,-2,4]
输出: 6
解释: 子数组 [2,3] 有最大乘积 6。

示例 2:
输入: [-2,0,-1]
输出: 0
解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。

*/

class Solution1 {
public:
	int maxProduct(vector<int> &nums)
	{
		int maxRes = INT_MIN, maxNum = 1, minNum = 1;
		int len = nums.size();
		for (int i = 0; i < len; ++i)
		{
			if (nums[i] < 0) swap(maxNum, minNum);
			maxNum = max(maxNum*nums[i], nums[i]);
			minNum = min(minNum*nums[i], nums[i]);
			maxRes = max(maxRes, maxNum);
		}
		return maxRes;
	}
};

// 记忆化
class Solution2 {
public:
	int ans;
	vector<pair<int, int>> memo;

	int maxProduct(vector<int> &nums) {
		int len = nums.size();
		memo.resize(len, { INT_MIN, INT_MIN });
		ans = nums[0];
		for (int i = 0; i < len; ++i) helper(nums, i);
		return ans;
	}
	pair<int, int> helper(const vector<int> &nums, int idx) {
		if (memo[idx].first != INT_MIN) return memo[idx];
		if (idx == 0) {
			memo[idx] = { nums[0], nums[0] };
			ans = max(ans, nums[0]);
			return memo[idx];
		}
		pair<int, int> prev = helper(nums, idx - 1);
		int current_max =
			max({ nums[idx], nums[idx] * prev.first, nums[idx] * prev.second });
		int current_min =
			min({ nums[idx], nums[idx] * prev.first, nums[idx] * prev.second });
		memo[idx] = { current_max, current_min };
		ans = max(ans, current_max);
		return memo[idx];
	}
};

