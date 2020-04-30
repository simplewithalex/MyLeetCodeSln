﻿#include "header.h"

/*

实现 strStr() 函数。
给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。如果不存在，则返回  -1。

示例 1:
输入: haystack = "hello", needle = "ll"
输出: 2

示例 2:
输入: haystack = "aaaaa", needle = "bba"
输出: -1

说明:
当 needle 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。
对于本题而言，当 needle 是空字符串时我们应当返回 0 。这与C语言的 strstr() 以及 Java的 indexOf() 定义相符。

*/

class Solution1 {
public:
	int strStr(string haystack, string needle)
	{
		if (needle.empty()) return 0;
		int len1 = haystack.size(), len2 = needle.size();
		for (int i = 0; i <= len1 - len2; ++i)
		{
			int j = 0;
			for (; j < len2&&haystack[i + j] == needle[j]; ++j);
			if (j == len2) return i;
		}
		return -1;
	}
};


//KMP算法
class Solution2 {
public:
	int strStr(string haystack, string needle)
	{
		int patLen = needle.size();
		int hayLen = haystack.size();
		if (patLen == 0) return 0;
		vector<vector<int>> dp(patLen, vector<int>(26, 0));
		kmp(needle, dp);
		int j = 0;
		for (int i = 0; i < hayLen; ++i)
		{
			j = dp[j][haystack[i] - 'a'];
			if (j == patLen) return i - patLen + 1;
		}
		return -1;
	}
	void kmp(const string &pat, vector<vector<int>> &dp)
	{
		int len = pat.size();
		dp[0][pat[0] - 'a'] = 1;
		int flag = 0;
		for (int i = 1; i < len; ++i)
		{
			for (int ch = 0; ch < 26; ++ch)
				dp[i][ch] = dp[flag][ch];
			dp[i][pat[i] - 'a'] = i + 1;
			flag = dp[flag][pat[i] - 'a'];
		}
	}
};
//https://leetcode-cn.com/problems/implement-strstr/solution/kmp-suan-fa-xiang-jie-by-labuladong/