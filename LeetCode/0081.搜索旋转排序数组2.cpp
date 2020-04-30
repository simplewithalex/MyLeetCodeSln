#include "header.h"

/*

假设按照升序排序的数组在预先未知的某个点上进行了旋转。
( 例如，数组 [0,0,1,2,2,5,6] 可能变为 [2,5,6,0,0,1,2] )。
编写一个函数来判断给定的目标值是否存在于数组中。若存在返回 true，否则返回 false。

示例 1:
输入: nums = [2,5,6,0,0,1,2], target = 0
输出: true

示例 2:
输入: nums = [2,5,6,0,0,1,2], target = 3
输出: false

进阶:
这是 搜索旋转排序数组 的延伸题目，本题中的nums可能包含重复元素。
这会影响到程序的时间复杂度吗？会有怎样的影响，为什么？

*/

//通用解法，同样可用于033题

class Solution1 {
public:
	bool search(vector<int> &nums, int target)
	{
		int len = nums.size();
		if (len == 0) return false;
		int lo = 0, hi = len - 1;
		while (lo < hi)
		{
			int mi = lo + ((hi - lo) >> 1);
			if (nums[mi] == target) return true;
			else if (nums[lo] < nums[mi])//左半部分有序
			{
				if (target<nums[mi] && nums[lo] <= target)
					hi = mi - 1;
				else
					lo = mi + 1;
			}
			else if (nums[lo] > nums[mi])//右半部分有序
			{
				if (target>nums[mi] && nums[hi] >= target)
					lo = mi + 1;
				else
					hi = mi - 1;
			}
			else
				++lo;
		}
		return nums[lo] == target;
	}
};

class Solution2 {
public:
	bool search(vector<int> &nums, int target)
	{
		if (nums.empty()) return false;
		int len = nums.size();
		int lo = 0, hi = len - 1;
		while (lo < hi)
		{
			int mi = lo + ((hi - lo) >> 1);
			if (nums[lo] < nums[mi]) //左半部分有序
			{
				if (target <= nums[mi] && nums[lo] <= target)
					hi = mi;
				else
					lo = mi + 1;
			}
			else if (nums[lo] > nums[mi])//右半部分有序
			{
				if (target > nums[mi] && nums[hi] >= target)
					lo = mi + 1;
				else
					hi = mi;
			}
			else
			{
				if (target == nums[mi]) return true;
				++lo;
			}
		}
		return nums[lo] == target;
	}
};
