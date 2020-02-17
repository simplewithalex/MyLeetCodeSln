#include "header.h"

/*

给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那两个整数，并返回他们的数组下标。

你可以假设每种输入只会对应一个答案。
你不能重复利用数组中同一个元素。

示例:

给定 nums = [2, 7, 11, 15], target = 9
因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]

*/

class Solution {
public:
	vector<int> twoSum(vector<int> &numbers, int target)
	{
		int len = numbers.size();
		if (len < 2) return {};
		unordered_map<int, int> m;
		for (int i = 0; i<len; ++i)
		{
			int temp = target - numbers[i];
			if (!m.count(temp))
				m[numbers[i]] = i;
			else
				return{ m[temp], i };
		}
		return {};
	}
};