#include "header.h"

/*

给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

示例:
输入: [0,1,0,3,12]
输出: [1,3,12,0,0]

说明:
必须在原数组上操作，不能拷贝额外的数组。
尽量减少操作次数。

*/

class Solution1 {
public:
	void moveZeroes(vector<int> &nums)
	{
		if (nums.empty()) return;
		int len = nums.size();
		int lastZero = 0;
		for (int cur = 0; cur < len; ++cur)
		{
			if (nums[cur] != 0)
				nums[lastZero++] = nums[cur];
		}
		for (int i = lastZero; i < len; ++i)
		{
			nums[i] = 0;
		}
	}
};

//在零元素比较多的情况比较好的解法
//例如：[0，0，0，…，0，1]
class Solution2 {
public:
	void moveZeroes(vector<int> &nums)
	{
		if (nums.empty()) return;
		int len = nums.size();
		for (int lastZero = 0, cur = 0; cur < len; ++cur)
		{
			if (nums[cur] != 0) swap(nums[lastZero++], nums[cur]);
		}
	}
};