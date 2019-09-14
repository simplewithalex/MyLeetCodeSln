#include "header.h"

/*

给定一个包含红色、白色和蓝色，一共 n 个元素的数组，
原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

注意:
不能使用代码库中的排序函数来解决这道题。

示例:
输入: [2,0,2,1,1,0]
输出: [0,0,1,1,2,2]

进阶：
一个直观的解决方案是使用计数排序的两趟扫描算法。
首先，迭代计算出0、1 和 2 元素的个数，然后按照0、1、2的排序，重写当前数组。
你能想出一个仅使用常数空间的一趟扫描算法吗？

*/

class Solution1 {
public:
	void sortColors(int A[], int n)
	{
		int front = 0, behind = n - 1;
		for (int i = 0; i <= behind; ++i)
		{
			while (A[i] == 2 && i < behind)
			{
				swap(A[i], A[behind--]);
			}
			while (A[i] == 0 && i>front)
			{
				swap(A[i], A[front++]);
			}
		}
	}
};

//如果不是3个数而是多个数，可以考虑扩展下面的方法。
class Solution2 {
public:
	void sortColors(vector<int> &nums)
	{
		int n0 = -1, n1 = -1, n2 = -1;
		int len = nums.size();
		for (int i = 0; i < len; ++i)
		{
			if (nums[i] == 0)
			{
				++n2;
				nums[n2] = 2;
				++n1;
				nums[n1] = 1;
				++n0;
				nums[n0] = 0;
			}
			else if (nums[i] == 1)
			{
				++n2;
				nums[n2] = 2;
				++n1;
				nums[n1] = 1;
			}
			else if (nums[i] == 2)
			{
				++n2;
				nums[n2] = 2;
			}
		}
	}
};
//方法参考：https://leetcode.wang/leetCode-75-Sort-Colors.html