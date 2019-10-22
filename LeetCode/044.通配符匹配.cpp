#include "header.h"

/*

给定一个字符串 (s) 和一个字符模式 (p) ，实现一个支持 '?' 和 '*' 的通配符匹配。
'?' 可以匹配任何单个字符。
'*' 可以匹配任意字符串(包括空字符串)
两个字符串完全匹配才算匹配成功

说明:
s 可能为空，且只包含从 a-z 的小写字母。
p 可能为空，且只包含从 a-z 的小写字母，以及字符 ? 和 *

示例 1:
输入:
s = "aa"
p = "a"
输出: false
解释: "a" 无法匹配 "aa" 整个字符串。

示例 2:
输入:
s = "aa"
p = "*"
输出: true
解释: '*' 可以匹配任意字符串。

示例 3:
输入:
s = "cb"
p = "?a"
输出: false
解释: '?' 可以匹配 'c', 但第二个 'a' 无法匹配 'b'。

示例 4:
输入:
s = "adceb"
p = "*a*b"
输出: true
解释: 第一个 '*' 可以匹配空字符串, 第二个 '*' 可以匹配字符串 "dce".

示例 5:
输入:
s = "acdcb"
p = "a*c?b"
输入: false

*/


//动态规划
class Solution1 {
public:
	bool isMatch(string s, string p) 
	{
		int sLen = s.size(), pLen = p.size();
		vector<vector<int>> dp(sLen + 1, vector<int>(pLen + 1, 0));
		dp[0][0] = 1;
		for (int i = 1; i <= pLen; ++i)
			dp[0][i] = dp[0][i - 1] && p[i - 1] == '*';
		for (int i = 1; i <= sLen; ++i)
		{
			for (int j = 1; j <= pLen; ++j)
			{
				//如果两个字符相等或匹配字符为'?'
				if (s[i - 1] == p[j - 1] || p[j - 1] == '?')
				{
					dp[i][j] = dp[i - 1][j - 1];
				}
				//如果匹配字符为'*',则存在两种情况，'*'匹配空或匹配多个字符
				if (p[j - 1] == '*')
				{
					dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
				}
			}
		}
		return dp[sLen][pLen];
	}
};


//迭代方法
class Solution2 {
public:
	bool isMatch(string s, string p)
	{
		int sLen = s.size(), pLen = p.size();
		int si = 0, pi = 0, match = 0, starIdx = -1;
		while (si < sLen)
		{
			if (pi < pLen && (p[pi] == '?' || p[pi] == s[si]))
				++si, ++pi;
			else if (pi < pLen && (p[pi] == '*'))
			{
				starIdx = pi;
				match = si;
				++pi;
			}
			else if (starIdx != -1)
			{
				pi = starIdx + 1;
				++match;
				si = match;
			}
			else
				return false;
		}
		while (pi < pLen&&p[pi] == '*')
			++pi;
		return pi == pLen;
	}
};
//https://leetcode.com/problems/wildcard-matching/discuss/17810/Linear-runtime-and-constant-space-solution