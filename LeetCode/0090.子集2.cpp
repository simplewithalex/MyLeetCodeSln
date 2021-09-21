#include "header.h"

/*

给你一个整数数组 nums，其中可能包含重复元素，请你返回该数组所有可能的子集（幂集）。
解集不能包含重复的子集。返回的解集中，子集可以按任意顺序排列。

示例 1：
输入：nums = [1,2,2]
输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]

示例 2：
输入：nums = [0]
输出：[[],[0]]

提示：
1 <= nums.length <= 10
-10 <= nums[i] <= 10

*/

class Solution {
public:
	vector<vector<int>> subsetsWithDup(vector<int> &nums) {
		vector<vector<int>> res;
		vector<int> vec;
		sort(nums.begin(), nums.end());
		backTrack(res, vec, nums, 0);
		return res;
	}
private:
	void backTrack(vector<vector<int>> &res, vector<int> &vec, vector<int> &nums, int start)
	{
		res.push_back(vec);
		int len = nums.size();
		for (int i = start; i < len; ++i)
		{
			if (i > start&&nums[i] == nums[i - 1]) continue;
			vec.push_back(nums[i]);
			backTrack(res, vec, nums, i + 1);
			vec.pop_back();
		}
	}
};