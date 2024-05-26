#include "header.h"

/*

413. 等差数列划分

如果一个数列至少有三个元素，并且任意两个相邻元素之差相同，则称该数列为等差数列
例如，[1,3,5,7,9]、[7,7,7,7] 和 [3,-1,-5,-9] 都是等差数列
给你一个整数数组nums，返回数组nums中所有为等差数组的子数组个数

子数组 是数组中的一个连续序列

示例 1：
输入：nums = [1,2,3,4]
输出：3
解释：nums 中有三个子等差数组：[1, 2, 3]、[2, 3, 4] 和 [1,2,3,4] 自身

示例 2：
输入：nums = [1]
输出：0

提示：
1 <= nums.length <= 5000
-1000 <= nums[i] <= 1000

*/

class Solution {
private:
	vector<int> memo;

public:
	int numberOfArithmeticSlices(vector<int> &nums) {
		int len = nums.size();
		memo.resize(len, -1);
		int ans = 0;
		for (int i = 0; i < len; ++i) {
			ans += helper(nums, i);
		}
		return ans;
	}

private:
	int helper(vector<int> &nums, int idx) {
		if (idx < 2) return 0;
		if (memo[idx] != -1) return memo[idx];
		int ans = 0;
		if (nums[idx] - nums[idx - 1] == nums[idx - 1] - nums[idx - 2]) {
			ans = 1 + helper(nums, idx - 1);
		}
		return memo[idx] = ans;
	}
};
