#include "header.h"

/*

给定一个整数数组 nums ，找到一个具有最大和的连续子数组
（子数组最少包含一个元素），返回其最大和。

示例:

输入: [-2,1,-3,4,-1,2,1,-5,4],
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。

如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的分治法求解。

*/

//O(n)时间复杂度

class Solution1 {
public:
	int maxSubArray(vector<int> &nums)
	{
		if (nums.empty()) return 0;
		int maxNum = INT_MIN;
		int len = nums.size();
		int temp = 0;
		for (int i = 0; i < len; ++i)
		{
			temp += nums[i];
			maxNum = max(temp, maxNum);
			if (temp < 0)
				temp = 0;
		}
		return maxNum;
	}
};

//分治法，方法有些奇怪

struct res
{
	int l, r, m, s;
	res(int lMax, int rMax, int maxNum, int sum)
		:l(lMax), r(rMax), m(maxNum), s(sum) {}
};
class Solution2 {
public:
	int maxSubArray(vector<int> &nums)
	{
		if (nums.empty()) return 0;
		int len = nums.size();
		res obj = findMax(nums, 0, len);
		return obj.m;
	}
	res findMax(vector<int> &nums, int lo, int hi)
	{
		if (hi - lo < 2) return res(nums[lo], nums[lo], nums[lo], nums[lo]);
		int mi = (lo + hi) >> 1;
		res lhs = findMax(nums, lo, mi), rhs = findMax(nums, mi, hi);
		int l, r, m, s;
		l = max(lhs.l, lhs.s + rhs.l);
		r = max(rhs.r, lhs.r + rhs.s);
		m = max(lhs.r + rhs.l, max(lhs.m, rhs.m));
		s = lhs.s + rhs.s;
		return res(l, r, m, s);
	}
};
//Thanks for this Solution about divide and conquer approach.
//https://leetcode.com/problems/maximum-subarray/discuss/20200/Share-my-solutions-both-greedy-and-divide-and-conquer
