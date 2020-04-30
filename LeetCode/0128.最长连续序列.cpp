#include "header.h"

/*

给定一个未排序的整数数组，找出最长连续序列的长度。
要求算法的时间复杂度为 O(n)。

示例:

输入: [100, 4, 200, 1, 3, 2]
输出: 4
解释: 最长连续序列是 [1, 2, 3, 4]。它的长度为 4。

*/


//使用m记录边界的连续长度，比如连续数字1、2、3、4、5，则m[1]和m[5]的值都为5
class Solution {
public:
	int longestConsecutive(vector<int> &nums)
	{
		int len = nums.size();
		if (len <= 1) return len;
		int res = 0;
		unordered_map<int, int> m;
		for (auto n : nums)
		{
			if (!m.count(n))
			{
				int left = m.count(n - 1) ? m[n - 1] : 0;
				int right = m.count(n + 1) ? m[n + 1] : 0;
				m[n] = left + right + 1;
				res = max(res, m[n]);
				m[n - left] = m[n];
				m[n + right] = m[n];
			}
			else
			{
				continue;
			}
		}
		return res;
	}
};