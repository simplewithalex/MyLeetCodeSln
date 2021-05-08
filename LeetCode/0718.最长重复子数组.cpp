#include "header.h"

/*

给两个整数数组 A 和 B ，返回两个数组中公共的、长度最长的子数组的长度。

示例：

输入：
A: [1,2,3,2,1]
B: [3,2,1,4,7]

输出：3

解释：
长度最长的公共子数组是 [3, 2, 1] 。
 

提示：
1 <= len(A), len(B) <= 1000
0 <= A[i], B[i] < 100

*/

// 备忘录
class Solution1 {
public:
	int findLength(vector<int> &nums1, vector<int> &nums2) 
	{
		int len1 = nums1.size(), len2 = nums2.size();
		vector<vector<int>> memo(len1, vector<int>(len2, -1));
		int maxLen = 0;
		helper(nums1, nums2, len1 - 1, len2 - 1, maxLen, memo);
		return maxLen;
	}
	// 使用memo数组记住在当前下标元素连续的长度
	int helper(vector<int> &nums1, vector<int> &nums2, int i, int j, int &maxLen, vector<vector<int>> &memo) 
	{
		if (i < 0 || j < 0) return 0;
		if (memo[i][j] != -1) return memo[i][j];
		int len = 0;
		if (nums1[i] == nums2[j]) 
		{
			len = helper(nums1, nums2, i - 1, j - 1, maxLen, memo) + 1;
			maxLen = max(len, maxLen);
		}
		helper(nums1, nums2, i - 1, j, maxLen, memo);
		helper(nums1, nums2, i, j - 1, maxLen, memo);
		return memo[i][j] = len;
	}
};

// 自底而上的动态规划
class Solution2 {
public:
	int findLength(vector<int> &nums1, vector<int> &nums2) 
	{
		int len1 = nums1.size(), len2 = nums2.size();
		vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
		int maxLen = 0;
		for (int i = 1; i <= len1; ++i) 
		{
			for (int j = 1; j <= len2; ++j) 
			{
				dp[i][j] = nums1[i - 1] == nums2[j - 1] ? dp[i - 1][j - 1] + 1 : 0;
				maxLen = max(dp[i][j], maxLen);
			}
		}
		return maxLen;
	}
};