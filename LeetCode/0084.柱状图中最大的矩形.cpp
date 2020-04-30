#include "header.h"

/*

给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
求在该柱状图中，能够勾勒出来的矩形的最大面积。

例如，其中每个柱子的宽度为 1，给定的高度为 [2,1,5,6,2,3]。
图中阴影部分为所能勾勒出的最大矩形面积，其面积为 10 个单位。

示例:
输入: [2,1,5,6,2,3]
输出: 10

*/

class Solution {
public:
	int largestRectangleArea(vector<int> &height)
	{
		if (height.empty()) return 0;
		int len = height.size();
		int maxRes = 0;
		stack<int> s;
		for (int i = 0; i <= len;)
		{
			int h = (i == len) ? 0 : height[i];
			if (s.empty() || h >= height[s.top()])
			{
				s.push(i);
				++i;
			}
			else
			{
				int tempH = s.top();
				s.pop();
				maxRes = max(maxRes, height[tempH] * (s.empty() ? i : i - 1 - s.top()));
			}
		}
		return maxRes;
	}
};
//https://leetcode-cn.com/problems/largest-rectangle-in-histogram/solution/zhao-liang-bian-di-yi-ge-xiao-yu-ta-de-zhi-by-powc/