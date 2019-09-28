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

//动态规划
class Solution1 {
public:
	bool isInterleave(string s1, string s2, string s3)
	{
		int len1 = s1.size();
		int len2 = s2.size();
		int len3 = s3.size();
		if (len3 != len1 + len2)
			return false;
		vector<vector<bool>> dp(len1 + 1, vector<bool>(len2 + 1, false));
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

//记忆回溯法
class Solution2 {
public:
	bool isInterleave(string s1, string s2, string s3)
	{
		unordered_set<string> s;
		return backTrack(s1, 0, s2, 0, s3, 0, s);
	}
	bool backTrack(string &s1, int i, string &s2, int j, string &s3, int k, unordered_set<string> &s)
	{
		int len1 = s1.size(), len2 = s2.size(), len3 = s3.size();
		string key = to_string(i) + '#' + to_string(j);
		if (len1 + len2 != len3) return false;
		if (s.count(key)) return false;
		if (i == len1&&j == len2&&k == len3) return true;
		if (i == len1)
		{
			while (j < len2)
			{
				if (s2[j] != s3[k])
				{
					s.insert(key);
					return false;
				}
				++j, ++k;
			}
			return true;
		}
		if (j == len2)
		{
			while (i < len1)
			{
				if (s1[i] != s3[k])
				{
					s.insert(key);
					return false;
				}
				++i, ++k;
			}
			return true;
		}
		if (s1[i] == s3[k])
		{
			if (backTrack(s1, i + 1, s2, j, s3, k + 1, s)) return true;
		}
		if (s2[j] == s3[k])
		{
			if (backTrack(s1, i, s2, j + 1, s3, k + 1, s)) return true;
		}
		s.insert(key);
		return false;
	}
};