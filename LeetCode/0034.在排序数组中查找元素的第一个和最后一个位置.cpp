#include "header.h"

/*

给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。
你的算法时间复杂度必须是 O(log n) 级别。
如果数组中不存在目标值，返回 [-1, -1]。

示例 1:
输入: nums = [5,7,7,8,8,10], target = 8
输出: [3,4]

示例 2:
输入: nums = [5,7,7,8,8,10], target = 6
输出: [-1,-1]

*/

class Solution1 {
public:
	vector<int> searchRange(vector<int> &nums, int target) 
	{
		int first = bisearch(nums, target - 1);
		int second = bisearch(nums, target);
		if (first == second)
			return { -1, -1 };
		else
			return { first, second - 1 };
	}
	int bisearch(vector<int> &nums, int target)
	{
		int lo = 0, hi = nums.size();
		while (lo < hi)
		{
			int mi = lo + ((hi - lo) >> 1);
			(nums[mi] > target) ? hi = mi : lo = mi + 1;
		}
		return lo;
	}
};

//根据035题标准二分查找模板
class Solution2 {
public:
	vector<int> searchRange(vector<int> &nums, int target)
	{
		if (nums.empty()) return{ -1, -1 };
		int first = lowerBound(nums, target);
		if (first == -1) return{ -1, -1 };
		int second = upBound(nums, target);
		return { first, second };
	}
	//得到相同目标元素的最左边一个
	int lowerBound(vector<int> &nums, int target)
	{
		int len = nums.size();
		int lo = 0, hi = len - 1;
		while (lo < hi)
		{
			int mi = lo + ((hi - lo) >> 1);
			(nums[mi] < target) ? lo = mi + 1 : hi = mi;
		}
		return nums[lo] == target ? lo : -1;
	}
	//得到相同目标元素的最右边一个
	int upBound(vector<int> &nums, int target)
	{
		int len = nums.size();
		int lo = 0, hi = len - 1;
		while (lo < hi)
		{
			int mi = lo + ((hi - lo + 1) >> 1);
			(nums[mi] > target) ? hi = mi - 1 : lo = mi;
		}
		return nums[lo] == target ? lo : -1;
	}
};