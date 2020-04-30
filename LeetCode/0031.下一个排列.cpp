#include "header.h"

/*

实现获取下一个排列的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。
如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。
必须原地修改，只允许使用额外常数空间。

以下是一些例子，输入位于左侧列，其相应输出位于右侧列。
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1

*/

class Solution {
public:
	void nextPermutation(vector<int> &num)
	{
		int len = num.size();
		int index = len - 2;
		while (index >= 0 && num[index] >= num[index + 1]) --index;
		if (index < 0)
		{
			reverse(num.begin(), num.end());
		}
		else
		{
			int i = len - 1;
			while (i >= 0 && num[i] <= num[index]) --i;
			swap(num[index], num[i]);
			reverse(num.begin() + index + 1, num.end());
		}
	}
};
//https://leetcode.wang/leetCode-31-Next-Permutation.html