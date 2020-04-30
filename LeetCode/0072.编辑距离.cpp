﻿#include "header.h"

/*

给定两个单词 word1 和 word2，计算出将 word1 转换成 word2 所使用的最少操作数 。
你可以对一个单词进行如下三种操作：

插入一个字符
删除一个字符
替换一个字符

示例 1:
输入: word1 = "horse", word2 = "ros"
输出: 3
解释:
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')

示例 2:
输入: word1 = "intention", word2 = "execution"
输出: 5
解释:
intention -> inention (删除 't')
inention -> enention (将 'i' 替换为 'e')
enention -> exention (将 'n' 替换为 'x')
exention -> exection (将 'n' 替换为 'c')
exection -> execution (插入 'u')

*/

//解题思路：
//https://leetcode-cn.com/problems/edit-distance/solution/bian-ji-ju-chi-mian-shi-ti-xiang-jie-by-labuladong/

//备忘录解法
class Solution1 {
public:
	int minDistance(string word1, string word2)
	{
		int len1 = word1.size(), len2 = word2.size();
		vector<vector<int>> memo(len1, vector<int>(len2, -1));
		return helper(word1, word2, len1 - 1, len2 - 1, memo);
	}
	int helper(string &s1,string &s2,int i, int j, vector<vector<int>> &memo)
	{
		if (i == -1) return j + 1;
		if (j == -1) return i + 1;
		if (memo[i][j] != -1) return memo[i][j];
		if (s1[i] == s2[j]) memo[i][j] = helper(s1, s2, i - 1, j - 1, memo);
		else memo[i][j] = min(min(helper(s1, s2, i, j - 1, memo) + 1, helper(s1, s2, i - 1, j, memo) + 1), helper(s1, s2, i - 1, j - 1, memo) + 1);
		return memo[i][j];
	}
};

//动态规划解法
class Solution2 {
public:
	int minDistance(string word1, string word2)
	{
		int len1 = word1.size(), len2 = word2.size();
		vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
		for (int i = 1; i <= len1; ++i) dp[i][0] = i;
		for (int j = 1; j <= len2; ++j) dp[0][j] = j;
		for (int i = 1; i <= len1; ++i)
		{
			for (int j = 1; j <= len2; ++j)
			{
				if (word1[i - 1] == word2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
				else
				{
					dp[i][j] = min(min(dp[i - 1][j] + 1, dp[i][j - 1] + 1), dp[i - 1][j - 1] + 1);
				}
			}
		}
		return dp[len1][len2];
	}
};