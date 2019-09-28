#include "header.h"

/*

给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水。

示例:
输入: [0,1,0,2,1,0,1,3,2,1,2,1]
输出: 6

*/

class Solution {
public:
	int trap(int A[], int n)
	{
		stack<int> s;
		int res = 0;
		for (int i = 0; i < n;)
		{
			if (s.empty() || A[i] <= A[s.top()])
			{
				s.push(i++);
			}
			else
			{
				int pre = s.top();
				s.pop();
				if (!s.empty())
				{
					int minHeight = min(A[i], A[s.top()]);
					res += (minHeight - A[pre])*(i - s.top() - 1);
				}
			}
		}
		return res;
	}
};
//栈解法：https://leetcode.com/problems/trapping-rain-water/discuss/17414/A-stack-based-solution-for-reference-inspired-by-Histogram
