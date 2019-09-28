#include "header.h"

/*

给定一个包括 n 个整数的数组 nums 和 一个目标值 target。
找出 nums 中的三个整数，使得它们的和与 target 最接近。
返回这三个数的和。假定每组输入只存在唯一答案。

例如，给定数组 nums = [-1，2，1，-4], 和 target = 1.
与 target 最接近的三个数的和为 2. (-1 + 2 + 1 = 2).


*/

class Solution {
public:
	int threeSumClosest(vector<int> &nums, int target)
	{
		sort(nums.begin(), nums.end());
		int len = nums.size();
		int sum = nums[0] + nums[1] + nums[len - 1];
		int res = sum;
		for (int i = 0; i < len - 2; ++i)
		{
			int lo = i + 1, hi = len - 1;
			if (i == 0 || nums[i] != nums[i - 1])
			{
				while (lo < hi)
				{
					sum = nums[i] + nums[lo] + nums[hi];
					if (sum == target)
					{
						return sum;
					}
					else if (sum < target)
					{
						while (lo < hi&&nums[lo] == nums[lo + 1])
							++lo;
						++lo;
					}
					else
					{
						while (lo < hi&&nums[hi] == nums[hi - 1])
							--hi;
						--hi;
					}
					if (abs(sum - target) < abs(res - target))
						res = sum;
				}
			}
		}
		return res;
	}
};