#include "header.h"

/*

假设按照升序排序的数组在预先未知的某个点上进行了旋转。(例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2])。请找出其中最小的元素。
注意数组中可能存在重复的元素。

示例 1：
输入: [1,3,5]
输出: 1

示例 2：
输入: [2,2,2,0,1]
输出: 0

*/

class Solution {
public:
	int findMin(vector<int> &nums)
	{

		int len = nums.size();
		if (len == 0) return 0;
		int lo = 0, hi = len - 1;
		while (lo < hi)
		{
			if (nums[lo] < nums[hi]) return nums[lo];
			int mi = lo + ((hi - lo) >> 1);
			(nums[mi] > nums[hi]) ? lo = mi + 1 : (nums[mi] < nums[hi] ? hi = mi : --hi);
		}
		return nums[lo];
	}
};