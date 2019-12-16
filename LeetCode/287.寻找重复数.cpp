#include "header.h"

/*

给定一个包含 n + 1 个整数的数组 nums，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。
假设只有一个重复的整数，找出这个重复的数。

示例 1:
输入: [1,3,4,2,2]
输出: 2

示例 2:
输入: [3,1,3,4,2]
输出: 3

说明：
不能更改原数组（假设数组是只读的）。
只能使用额外的 O(1) 的空间。
时间复杂度小于 O(n^2) 。
数组中只有一个重复的数字，但它可能不止重复出现一次。

*/

//二分查找解法
class Solution1 {
public:
	int findDuplicate(vector<int> &nums)
	{
		int len = nums.size();
		int lo = 1, hi = len - 1;
		while (lo < hi)
		{
			int mi = lo + ((hi - lo) >> 1);
			int count = 0;
			for (auto n : nums)
			{
				if (n <= mi) ++count;
			}
			if (count>mi) hi = mi;
			else lo = mi + 1;
		}
		return lo;
	}
};
//https://leetcode-cn.com/problems/find-the-duplicate-number/solution/er-fen-fa-si-lu-ji-dai-ma-python-by-liweiwei1419/


//快慢指针方法（技巧性）
class Solution2 {
public:
	int findDuplicate(vector<int> &nums)
	{
		int slow = 0, fast = 0;
		while (true)
		{
			fast = nums[nums[fast]];
			slow = nums[slow];
			if (fast == slow)
				break;
		}
		int finder = 0;
		while (finder != slow)
		{
			finder = nums[finder];
			slow = nums[slow];
		}
		return slow;
	}
};
//https://leetcode-cn.com/problems/find-the-duplicate-number/solution/kuai-man-zhi-zhen-de-jie-shi-cong-damien_undoxie-d/

/*
为什么finder和slow相遇在入口
假设相遇时slow走了n步，则fast走了2n步，起点到环的入口距离为m，环的周长为c
1、fast比slow多走的n步一直在环中做循环，所以n%c==0
2、fast和slow相遇时，slow在环中行进的距离是n-m，其中n%c==0。这时我们再让slow前进m步，也就是在环中走了n步了。
3、而n%c==0即slow在环里面走的距离是环的周长的整数倍，就回到了环的入口了，而入口就是重复的数字。
4、我们不知道起点到入口的长度m，所以弄个finder和slow一起走，他们必定会在入口处相遇。
*/