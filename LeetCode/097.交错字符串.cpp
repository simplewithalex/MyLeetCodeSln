#include "header.h"

/*

给定三个字符串 s1, s2, s3, 验证 s3 是否是由 s1 和 s2 交错组成的。

示例 1:
输入: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
输出: true

示例 2:
输入: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
输出: false

*/

//备忘录算法
class Solution1 {
public:
	bool isInterleave(string s1, string s2, string s3)
	{
		int len1 = s1.size(), len2 = s2.size();
		vector<vector<char>> memo(len1, vector<char>(len2, -1));
		return helper(s1, 0, s2, 0, s3, 0, memo);
	}
	bool helper(string &s1, int i, string &s2, int j, string &s3, int k, vector<vector<char>> &memo)
	{
		int len1 = s1.size(), len2 = s2.size();
		if (i == len1) return s2.substr(j) == s3.substr(k);
		if (j == len2) return s1.substr(i) == s3.substr(k);
		if (memo[i][j] != -1) return memo[i][j];
		memo[i][j] = (s1[i] == s3[k] && helper(s1, i + 1, s2, j, s3, k + 1, memo)) ||
			         (s2[j] == s3[k] && helper(s1, i, s2, j + 1, s3, k + 1, memo));
		return memo[i][j];
	}
};

//动态规划
class Solution2 {
public:
	bool isInterleave(string s1, string s2, string s3)
	{
		int len1 = s1.size();
		int len2 = s2.size();
		int len3 = s3.size();
		if (len3 != len1 + len2)
			return false;
		vector<vector<char>> dp(len1 + 1, vector<char>(len2 + 1, false));
		for (int i = 0; i < len1 + 1; ++i)
		{
			for (int j = 0; j < len2 + 1; ++j)
			{
				if (i == 0 && j == 0)
					dp[i][j] = true;
				else if (j == 0)
					dp[i][j] = dp[i - 1][j] && s1[i - 1] == s3[i + j - 1];
				else if (i == 0)
					dp[i][j] = dp[i][j - 1] && s2[j - 1] == s3[i + j - 1];
				else
					dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]) || (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
			}
		}
		return dp[len1][len2];
	}
};

//优化为一维数组
class Solution3 {
public:
	bool isInterleave(string s1, string s2, string s3)
	{
		int len1 = s1.size(), len2 = s2.size(), len3 = s3.size();
		if (len3 != len1 + len2) return false;
		vector<char> dp(len2 + 1, false);
		for (int i = 0; i <= len1; ++i)
		{
			for (int j = 0; j <= len2; ++j)
			{
				if (i == 0 && j == 0)
					dp[j] = true;
				else if (i == 0)
					dp[j] = dp[j - 1] && s2[j - 1] == s3[i + j - 1];
				else if (j == 0)
					dp[j] = dp[j] && s1[i - 1] == s3[i + j - 1];
				else
					dp[j] = (dp[j] && s1[i - 1] == s3[i + j - 1]) || (dp[j - 1] && s2[j - 1] == s3[i + j - 1]);
			}
		}
		return dp[len2];
	}
};

