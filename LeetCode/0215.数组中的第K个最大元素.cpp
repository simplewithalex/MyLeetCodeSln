#include "header.h"

/*

在未排序的数组中找到第 k 个最大的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

示例 1:

输入: [3,2,1,5,6,4] 和 k = 2
输出: 5

示例 2:

输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
输出: 4

说明:
你可以假设 k 总是有效的，且 1 ≤ k ≤ 数组的长度。

*/

class Solution {
public:
	int findKthLargest(vector<int> &nums, int k)
	{
		int len = nums.size();
		int lo = 0, hi = len - 1;
		int target = len - k;
		int index = partition(nums, lo, hi);
		while (index != target)
		{
			if (index > target)
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
		return nums[index];
	}
	int partition(vector<int> &nums, int lo, int hi)
	{
		swap(nums[lo], nums[lo + rand() % (hi - lo + 1)]);
		int pivot = nums[lo];
		while (lo < hi)
		{
			while (lo < hi)
			{
				if (nums[hi] > pivot) --hi;
				else
				{
					nums[lo++] = nums[hi];
					break;
				}
			}
			while (lo < hi)
			{
				if (nums[lo] < pivot) ++lo;
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