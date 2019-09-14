#include "header.h"

/*

给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
说明：解集不能包含重复的子集。

示例:
输入: nums = [1,2,3]
输出:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]

*/

class Solution {
public:
	vector<vector<int>> subsets(vector<int> &S)
	{
		vector<vector<int>> res;
		vector<int> vec;
		backTrack(res, vec, S, 0);
		return res;
	}
	void backTrack(vector<vector<int>> &res, vector<int> &vec, vector<int> &nums, int start)
	{
		res.push_back(vec);
		int len = nums.size();
		for (int i = start; i < len; ++i)
		{
			vec.push_back(nums[i]);
			backTrack(res, vec, nums, i + 1);
			vec.pop_back();
		}
	}
};
//参考这个回答，总结了一套回溯的使用方法。
//https://leetcode.com/problems/subsets/discuss/27281/A-general-approach-to-backtracking-questions-in-Java-(Subsets-Permutations-Combination-Sum-Palindrome-Partitioning)
