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
		helper(nums1, nums2, 0, 0, maxLen, memo);
		return maxLen;
	}
	// memo记录当前下标两字符串的最长公共前缀，同时也标记了该下标对已被访问，避免重复计算
	int helper(vector<int> &nums1, vector<int> &nums2, int i, int j, int &maxLen, vector<vector<int>> &memo)
	{
		if (i == nums1.size() || j == nums2.size()) return 0;
		if (memo[i][j] != -1) return memo[i][j];
		int len = 0;
		if (nums1[i] == nums2[j])
		{
			len = helper(nums1, nums2, i + 1, j + 1, maxLen, memo) + 1;
			maxLen = max(len, maxLen);
		}
		helper(nums1, nums2, i + 1, j, maxLen, memo);
		helper(nums1, nums2, i, j + 1, maxLen, memo);
		return memo[i][j] = len;
	}
};
/*

该方法将f(i,j)定义为两个字符串的最长公共前缀，所以结果为 max{f(i,j)} (0 < i < len1, 0 < j < len2)
          
		           (1) f(i-1,j-1) + 1 (A(i) == B(j))
状态方程：f(i,j) = 
		           (2) 0 (A(i) != B(j))

*/

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

// 另一种备忘录
class Solution3 {
public:
	int findLength(vector<int> &nums1, vector<int> &nums2)
	{
		int len1 = nums1.size(), len2 = nums2.size();
		vector<vector<int>> memo(len1 + 1, vector<int>(len2 + 1, -1));
		vector<vector<int>> common(len1, vector<int>(len2, -1));
		return helper(nums1, nums2, len1, len2, memo, common, false);
	}
	// memo与common共同标记已被访问的下标
	// memo记录[0:i)与[0:j)的最长公共子串
	// common记录当前下标两字符串的相同连续元素（这里是后缀）
	int helper(vector<int> &nums1, vector<int> &nums2, int i, int j, vector<vector<int>> &memo, vector<vector<int>> &common, bool isComm)
	{
		if (i == 0 || j == 0) return 0;
		if (isComm)
		{
			if (common[i - 1][j - 1] != -1) return common[i - 1][j - 1];
		}
		else if (memo[i][j] != -1)
		{
			return memo[i][j];
		}
		int len1 = 0, len2 = 0, len3 = 0;
		if (nums1[i - 1] == nums2[j - 1])
		{
			len1 = helper(nums1, nums2, i - 1, j - 1, memo, common, true) + 1;
		}
		len2 = helper(nums1, nums2, i - 1, j, memo, common, false);
		len3 = helper(nums1, nums2, i, j - 1, memo, common, false);
		common[i - 1][j - 1] = len1;
		memo[i][j] = max(len1, max(len2, len3));
		return isComm ? common[i - 1][j - 1] : memo[i][j];
	}
};
/*

该问题自顶向下的备忘录算法不太直观，关键在于f(i,j)的定义，这里将f(i,j)定义为[0,i)，[0,j)的最长公共子串

状态方程:
	         (1) common(i-1,j-1) + 1 (A(i) == B(j))
f(i,j) = max (2) f(i,j-1)
             (3) f(i-1,j)

该方法比较混乱，不太推荐

*/