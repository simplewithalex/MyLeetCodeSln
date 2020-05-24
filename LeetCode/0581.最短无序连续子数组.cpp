#include "header.h"

/*

给定一个整数数组，你需要寻找一个连续的子数组，如果对这个子数组进行升序排序，那么整个数组都会变为升序排序。
你找到的子数组应是最短的，请输出它的长度。

示例 1:
输入: [2, 6, 4, 8, 10, 9, 15]
输出: 5
解释: 你只需要对 [6, 4, 8, 10, 9] 进行升序排序，那么整个表都会变为升序排序。

说明 :
输入的数组长度范围在 [1, 10000]。
输入的数组可能包含重复元素 ，所以升序的意思是<=。

*/

//排序法，需要额外空间
class Solution1 {
public:
	int findUnsortedSubarray(vector<int> &nums)
	{
		int len = nums.size();
		vector<int> sortedNums(nums);
		sort(sortedNums.begin(), sortedNums.end());
		int start = 0, end = len - 1;
		while (start < len&&nums[start] == sortedNums[start]) ++start;
		while (start < end&&nums[end] == sortedNums[end]) --end;
		return end - start + 1;
	}
};
//https://leetcode.com/problems/shortest-unsorted-continuous-subarray/discuss/103066/Ideas-behind-the-O(n)-two-pass-and-one-pass-solutions

//线性时间复杂度
class Solution2 {
public:
	int findUnsortedSubarray(vector<int> &nums)
	{
		int len = nums.size();
		int maxNum = nums[0], minNum = nums[len - 1];
		int l = 0, r = -1;
		for (int i = 0; i < len; ++i)
		{
			if (maxNum>nums[i]) r = i;
			else maxNum = nums[i];
			if (minNum < nums[len - i - 1]) l = len - i - 1;
			else minNum = nums[len - i - 1];
		}
		return r - l + 1;
	}
};
