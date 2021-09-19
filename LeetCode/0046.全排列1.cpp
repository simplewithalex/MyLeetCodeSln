#include "header.h"

/*

给定一个不含重复数字的数组 nums ，返回其所有可能的全排列 。你可以按任意顺序返回答案。

示例 1：
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

示例 2：
输入：nums = [0,1]
输出：[[0,1],[1,0]]

示例 3：
输入：nums = [1]
输出：[[1]]
  
提示：
1 <= nums.length <= 6
-10 <= nums[i] <= 10
nums 中的所有整数 互不相同

*/

class Solution {
public:
	vector<vector<int>> permute(vector<int>& nums) {
		if (nums.empty()) return{};
		vector<vector<int>> res;
		vector<char> used(nums.size(), false);
		vector<int> v;
		helper(res, nums, used, v);
		return res;
	}
	void helper(vector<vector<int>> &res, vector<int> &nums, vector<char> &used, vector<int> &v) {
		int len1 = nums.size();
		int len2 = v.size();
		if (len1 == len2) {
			res.push_back(v);
			return;
		}
		for (int i = 0; i < len1; ++i) {
			if (used[i]) continue;
			used[i] = true;
			v.push_back(nums[i]);
			helper(res, nums, used, v);
			used[i] = false;
			v.pop_back();
		}
	}
};