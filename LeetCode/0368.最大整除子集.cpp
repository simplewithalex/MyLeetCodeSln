#include "header.h"

/*

368. 最大整除子集

给你一个由 无重复 正整数组成的集合 nums，请你找出并返回其中最大的整除子集 answer，子集中每一元素对 (answer[i], answer[j]) 都应当满足：
answer[i] % answer[j] == 0 ，或
answer[j] % answer[i] == 0
如果存在多个有效解子集，返回其中任何一个均可

示例 1：
输入：nums = [1,2,3]
输出：[1,2]
解释：[1,3] 也会被视为正确答案

示例 2：
输入：nums = [1,2,4,8]
输出：[1,2,4,8]

提示：
1 <= nums.length <= 1000
1 <= nums[i] <= 2 * 10^9
nums 中的所有整数 互不相同

*/


class Solution {
private:
	vector<int> memo;

public:
	vector<int> largestDivisibleSubset(vector<int> &nums) {
		int len = nums.size();
		memo.resize(len + 1, -1);
		sort(nums.begin(), nums.end());
		int maxLen = 1, handle = 1;
		for (int i = 1; i <= len; ++i) {
			int tempLen = helper(nums, i);
			if (tempLen > maxLen) {
				maxLen = tempLen;
				handle = i;
			}
		}
		vector<int> ans;
		for (int i = handle, curVal = nums[i - 1]; i >= 1; --i) {
			if (memo[i] == maxLen && curVal % nums[i - 1] == 0) {
				ans.push_back(nums[i - 1]);
				curVal = nums[i - 1];
				--maxLen;
			}
		}
		return ans;
	}

private:
	int helper(vector<int> &nums, int idx) {
		if (memo[idx] != -1) return memo[idx];
		int maxLen = 1;
		for (int j = 1; j < idx; ++j) {
			if (nums[idx - 1] % nums[j - 1] == 0) {
				maxLen = max(maxLen, helper(nums, j) + 1);
			}
		}
		return memo[idx] = maxLen;
	}
};
