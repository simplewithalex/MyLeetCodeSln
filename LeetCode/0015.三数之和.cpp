﻿#include "header.h"

/*

给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？
找出所有满足条件且不重复的三元组。
注意：答案中不可以包含重复的三元组。

例如, 给定数组 nums = [-1, 0, 1, 2, -1, -4]，
满足要求的三元组集合为：
[
  [-1, 0, 1],
  [-1, -1, 2]
]

*/

class Solution {
public:
	vector<vector<int>> threeSum(vector<int> &nums)
	{
		sort(nums.begin(), nums.end());
		vector<vector<int>> res;
		int len = nums.size();
		for (int i = 0; i < len - 2; ++i)
		{
			if (i == 0 || (i>0 && nums[i] != nums[i - 1]))
			{
				int lo = i + 1, hi = len - 1, sum = 0 - nums[i];
				while (lo < hi)
				{
					if (nums[lo] + nums[hi] == sum)
					{
						res.push_back(vector<int>{nums[i], nums[lo], nums[hi]});
						while (lo < hi&&nums[lo] == nums[lo + 1])
							++lo;
						while (lo < hi&&nums[hi] == nums[hi - 1])
							--hi;
						++lo, --hi;
					}
					else if (nums[lo] + nums[hi] < sum)
					{
						++lo;
					}
					else
					{
						--hi;
					}
				}
			}
		}
		return res;
	}
};
