#include "header.h"

/*

给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。
'.' 匹配任意单个字符
'*' 匹配零个或多个前面的那一个元素
所谓匹配，是要涵盖整个字符串s,而不是部分字符串。
说明:
s 可能为空，且只包含从 a-z 的小写字母。
p 可能为空，且只包含从 a-z 的小写字母，以及字符 . 和 *。

示例 1:
输入:
s = "aa"
p = "a"
输出: false
解释: "a" 无法匹配 "aa" 整个字符串。

示例 2:
输入:
s = "aa"
p = "a*"
输出: true
解释: 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。

示例 3:
输入:
s = "ab"
p = ".*"
输出: true
解释: ".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。

示例 4:
输入:
s = "aab"
p = "c*a*b"
输出: true
解释: 因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。

示例 5:
输入:
s = "mississippi"
p = "mis*is*p*."
输出: false


*/

//动态规划
class Solution1 {
public:
	bool isMatch(string s, string p)
	{
		int sLen = s.size(), pLen = p.size();
		vector<vector<int>> dp(sLen + 1, vector<int>(pLen + 1, 0));
		dp[0][0] = 1;
		for (int j = 1; j < dp[0].size(); ++j)
		{
			if (p[j - 1] == '*')
			{
				if (dp[0][j - 2]) dp[0][j] = 1;
			}
		}
		for (int i = 1; i < dp.size(); ++i)
		{
			for (int j = 1; j < dp[0].size(); ++j)
			{
				if (s[i - 1] == p[j - 1] || p[j - 1] == '.') dp[i][j] = dp[i - 1][j - 1];
				if (p[j - 1] == '*')
				{
					if (s[i - 1] != p[j - 2] && p[j - 2] != '.') dp[i][j] = dp[i][j - 2];
					else dp[i][j] = dp[i - 1][j] || dp[i][j - 1] || dp[i][j - 2];
				}
			}
		}
		return dp[sLen][pLen];
	}
};

//递归
class Solution2 {
public:
	bool isMatch(string s, string p)
	{
		return match(s, p, 0, 0);
	}
	bool match(string &s, string &p, int sid, int pid)
	{
		int sLen = s.size(), pLen = p.size();
		if (pid == pLen && sid != sLen) return false;
		if (sid == sLen && pid == pLen) return true;
		if (pid + 1 == pLen || p[pid + 1] != '*')
		{
			if (s[sid] == p[pid] || (sid != sLen&&p[pid] == '.'))
			{
				return match(s, p, sid + 1, pid + 1);
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (s[sid] == p[pid] || (sid != sLen&&p[pid] == '.'))
			{
				return match(s, p, sid, pid + 2) || match(s, p, sid + 1, pid);
			}
			else
			{
				return match(s, p, sid, pid + 2);
			}
		}
	}
};