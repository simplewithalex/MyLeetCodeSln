#include "header.h"

/*

给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，
使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。

注意：
答案中不可以包含重复的四元组。

示例：
给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。
满足要求的四元组集合为：
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]

*/


//这里使用一种通用的求kSum的方法。
class Solution {
public:
	vector<vector<int>> fourSum(vector<int> &nums, int target) 
	{
		sort(nums.begin(), nums.end());
		return kSum(nums, target, 4, 0);
	}
	vector<vector<int>> kSum(vector<int> &nums, int target, int k, int index)
	{
		int len = nums.size();
		vector<vector<int>> res;
		if (k == 2)
		{
			int i = index, j = len - 1;
			while (i < j)
			{
				if (nums[i] + nums[j] == target)
				{
					res.push_back(vector<int>{nums[i], nums[j]});
					while (i < j&&nums[i] == nums[i + 1]) ++i;
					while (i < j&&nums[j] == nums[j - 1]) --j;
					++i, --j;
				}
				else if (nums[i] + nums[j] < target)
				{
					++i;
				}
				else
				{
					--j;
				}
			}
		}
		else
		{
			for (int i = index; i <= len - k; ++i)
			{
				vector<vector<int>> temp = kSum(nums, target - nums[i], k - 1, i + 1);
				if (!temp.empty())
				{
					for (auto &v : temp)
					{
						v.insert(v.begin(), nums[i]);
						res.push_back(v);
					}
				}
				while (i < len - 1 && nums[i] == nums[i + 1]) ++i;
			}
		}
		return res;
	}
};
//https://leetcode.com/problems/4sum/discuss/8609/My-solution-generalized-for-kSums-in-JAVA