#include "header.h"

/*

给定一个整数数组和一个整数 k，你需要找到该数组中和为 k 的连续的子数组的个数。

示例 1 :
输入:nums = [1,1,1], k = 2
输出: 2 , [1,1] 与 [1,1] 为两种不同的情况。

说明:
数组的长度为 [1, 20,000]。
数组中元素的范围是 [-1000, 1000] ，且整数 k 的范围是 [-1e7, 1e7]。

*/

//通过累计和暴力寻找
class Solution1 {
public:
	int subarraySum(vector<int> &nums, int k)
	{
		if (nums.empty()) return 0;
		int len = nums.size();
		int res = 0;
		for (int start = 0; start < len; ++start)
		{
			int sum = 0;
			for (int end = start; end < len; ++end)
			{
				sum += nums[end];
				if (sum == k) ++res;
			}
		}
		return res;
	}
};

//使用哈希表优化
class Solution2 {
public:
	int subarraySum(vector<int> &nums, int k)
	{
		if (nums.empty()) return 0;
		int len = nums.size();
		int sum = 0, res = 0;
		//m:索引的累积总和,相同累加和发生的次数
		unordered_map<int, int> m;
		m[0] = 1;
		for (int i = 0; i < len; ++i)
		{
			sum += nums[i];
			if (m.count(sum - k)) res += m[sum - k];
			m[sum] += 1;
		}
		return res;
	}
};