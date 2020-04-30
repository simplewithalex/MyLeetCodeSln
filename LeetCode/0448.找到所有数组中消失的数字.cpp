﻿#include "header.h"

/*

给定一个范围在  1 ≤ a[i] ≤ n ( n = 数组大小 ) 的整型数组，数组中的元素一些出现了两次，另一些只出现一次。
找到所有在 [1, n] 范围之间没有出现在数组中的数字。

您能在不使用额外空间且时间复杂度为O(n)的情况下完成这个任务吗? 
你可以假定返回的数组不算在额外空间内。

示例:
输入:
[4,3,2,7,8,2,3,1]
输出:
[5,6]

*/

//基于异或的交换，不使用任何额外空间
class Solution1 {
public:
	vector<int> findDisappearedNumbers(vector<int> &nums)
	{
		vector<int> res;
		int len = nums.size();
		for (int i = 0; i < len; ++i)
		{
			while (nums[i] != nums[nums[i] - 1]) swap(nums[i], nums[nums[i] - 1]);
		}
		for (int i = 0; i < len; ++i)
		{
			if (nums[i] != i + 1) res.push_back(i + 1);
		}
		return res;
	}
	void swap(int &a, int &b)
	{
		a = a^b;
		b = a^b;
		a = a^b;
	}
};

//技巧性方法
class Solution2 {
public:
	vector<int> findDisappearedNumbers(vector<int> &nums)
	{
		int len = nums.size();
		for (int i = 0; i < len; ++i)
		{
			int idx = abs(nums[i]) - 1;
			if (nums[idx] > 0) nums[idx] = -nums[idx];
		}
		vector<int> res;
		for (int i = 0; i < len; ++i)
		{
			if (nums[i] > 0) res.push_back(i + 1);
		}
		return res;
	}
};