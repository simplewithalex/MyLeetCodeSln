#include "header.h"

/*

给定一个大小为 n 的数组，找到其中的众数。众数是指在数组中出现次数大于 ⌊ n/2 ⌋ 的元素。

你可以假设数组是非空的，并且给定的数组总是存在众数。

示例 1:

输入: [3,2,3]
输出: 3

示例 2:

输入: [2,2,1,1,1,2,2]
输出: 2

*/

//快速划分法，平均时间复杂度O(n)
class Solution1 {
public:
	int majorityElement(vector<int> &nums)
	{
		int len = nums.size();
		int lo = 0, hi = len - 1;
		int mi = len >> 1;
		int index = partition(nums, lo, hi);
		while (index != mi)
		{
			if (index > mi)
			{
				hi = index - 1;
				index = partition(nums, lo, hi);
			}
			else
			{
				lo = index + 1;
				index = partition(nums, lo, hi);
			}
		}
		return nums[mi];
	}
	int partition(vector<int> &nums, int lo, int hi)
	{
		swap(nums[lo], nums[lo + rand() % (hi - lo + 1)]);
		int pivot = nums[lo];
		while (lo < hi)
		{
			while (lo < hi)
			{
				if (pivot < nums[hi]) --hi;
				else
				{
					nums[lo++] = nums[hi];
					break;
				}
			}
			while (lo < hi)
			{
				if (pivot > nums[lo]) ++lo;
				else
				{
					nums[hi--] = nums[lo];
					break;
				}
			}
		}
		nums[lo] = pivot;
		return lo;
	}
};

//针对本题目特点的技巧性方法
class Solution2 {
public:
	int majorityElement(vector<int> &nums)
	{
		if (nums.empty()) return 0;
		int len = nums.size();
		int cur = nums[0];
		int times = 1;
		for (int i = 1; i < len; ++i)
		{
			if (times == 0)
			{
				cur = nums[i];
				times = 1;
			}
			else if (nums[i] == cur)
			{
				times += 1;
			}
			else
			{
				times -= 1;
			}
		}
		return cur;
	}
};