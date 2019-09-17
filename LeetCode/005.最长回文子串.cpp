#include "header.h"

/*

给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。

示例 1：
输入: "babad"
输出: "bab"
注意: "aba" 也是一个有效答案。

示例 2：
输入: "cbbd"
输出: "bb"

*/

class Solution {
public:
	string longestPalindrome(string s)
	{
		int maxNum = 0, idx = 0;
		for (int i = 0; i < s.size(); ++i)
		{
			int len1 = extend(s, i, i), len2 = extend(s, i, i + 1);
			if (maxNum < max(len1, len2))
			{
				idx = (len1>len2) ? (i - len1 / 2) : (i - len2 / 2 + 1);
				maxNum = max(len1, len2);
			}
		}
		return s.substr(idx, maxNum);
	}
	int extend(const string &s, int i, int j)
	{
		for (; i >= 0 && j < s.size(); --i, ++j)
			if (s[i] != s[j])
				break;
		return j - i - 1;
	}
};