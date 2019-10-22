#include "header.h"

/*

给定一个无序的整数数组，找到其中最长上升子序列的长度。

示例:
输入: [10,9,2,5,3,7,101,18]
输出: 4
解释: 最长的上升子序列是 [2,3,7,101]，它的长度是 4。

说明:
可能会有多种最长上升子序列的组合，你只需要输出对应的长度即可。
你算法的时间复杂度应该为 O(n^2) 。
进阶: 你能将算法的时间复杂度降低到 O(nlogn) 吗?

*/


//动态规划
class Solution1 {
public:
	int lengthOfLIS(vector<int> &nums) 
	{
		if (nums.empty()) return 0;
		int res = 0;
		int len = nums.size();
		vector<int> dp(len, 1);
		for (int i = 0; i < len; ++i)
		{
			for (int j = 0; j < i; ++j)
			{
				if (nums[j] < nums[i]) dp[i] = max(dp[i], dp[j] + 1);
			}
			res = max(dp[i], res);
		}
		return res;
	}
};


//动态规划+二分查找

//1、用dp数组保存最长上升子序列，该数组元素是递增的，将原序列的元素二分插入dp中
//2、如果dp中元素都比它小，将它插到最后，否则，用它覆盖掉比它大的元素中最小的那个
//3、总之，思想就是让dp中存储比较小的元素(值小的元素遇到比它大的元素的概率更大)。这样，dp中未必是真实的最长上升子序列，但长度是对的
class Solution2 {
public:
	int lengthOfLIS(vector<int> &nums)
	{
		int len = nums.size();
		vector<int> dp(len, 0);
		int res = 0;
		for (auto num : nums)
		{
			int lo = 0, hi = res;
			lo = biSearch(dp, lo, hi, num);
			if (lo == 0 || dp[lo - 1] < num)
			{
				dp[lo] = num;
				if (res == lo) ++res;
			}
		}
		return res;
	}
	int biSearch(vector<int> &nums, int lo, int hi, int target)
	{
		while (lo < hi)
		{
			int mi = lo + ((hi - lo) >> 1);
			(target < nums[mi]) ? hi = mi : lo = mi + 1;
		}
		return lo;
	}
};


//记忆化回溯
class Solution3 {
public:
	int lengthOfLIS(vector<int> &nums)
	{
		if (nums.empty()) return 0;
		int len = nums.size();
		//这里如果用哈希表，使用string作为词典关键码会导致内存超限
		vector<vector<int>> m(len + 1, vector<int>(len, -1));
		return backTrack(nums, -1, 0, m);
	}
	int backTrack(vector<int> &nums, int preIdx, int curIdx, vector<vector<int>> &m)
	{
		int len = nums.size();
		if (curIdx == len) return 0;
		pair<int, int> temp = { preIdx, curIdx };
		if (m[preIdx + 1][curIdx] >= 0) return m[preIdx + 1][curIdx];

		int increNum = 0;
		if (preIdx < 0 || nums[curIdx] > nums[preIdx])
		{
			increNum = 1 + backTrack(nums, curIdx, curIdx + 1, m);
		}
		int noIncreNum = backTrack(nums, preIdx, curIdx + 1, m);
		//使用词典记录前一个元素与当前元素作组合时升序序列的长度(它们不一定在升序的序列中)
		//preIdx+1看作是preIdx
		m[preIdx + 1][curIdx] = max(increNum, noIncreNum);
		return m[preIdx + 1][curIdx];
	}
};