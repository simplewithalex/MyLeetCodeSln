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

// 从备忘录到动态规划
// https://leetcode-cn.com/problems/regular-expression-matching/solution/zheng-ze-biao-da-shi-pi-pei-by-leetcode/

// 备忘录
class Solution1 {
public:
	bool isMatch(string s, string p)
	{
		int sLen = s.size(), pLen = p.size();
		vector<vector<char>> memo(sLen + 1, vector<char>(pLen + 1, -1));
		return helper(0, s, 0, p, memo);
	}
	bool helper(int i, string &s, int j, string &p, vector<vector<char>> &memo)
	{
		if (memo[i][j] != -1) return memo[i][j];
		int sLen = s.size(), pLen = p.size();
		if (j == pLen) return memo[i][j] = (i == sLen);
		if (j + 1 < pLen && p[j + 1] == '*')
		{
			if (helper(i, s, j + 2, p, memo) || (i < sLen && (p[j] == '.' || s[i] == p[j]) && helper(i + 1, s, j, p, memo))) return memo[i][j] = true;
		}
		else
		{
			if (i < sLen && ((p[j] == '.' || s[i] == p[j]) && helper(i + 1, s, j + 1, p, memo))) return memo[i][j] = true;
		}
		return memo[i][j] = false;
	}
};

// 备忘录
class Solution2 {
public:
	vector<vector<char>> memo;
	bool isMatch(string s, string p) {
		int sLen = s.size(), pLen = p.size();
		memo.resize(sLen + 1, vector<char>(pLen + 1, -1));
		return helper(sLen, pLen, s, p);
	}
	bool helper(int i, int j, const string &s, const string &p) {
		if (j == 0) return i == 0;
		if (memo[i][j] != -1) return memo[i][j];
		if (p[j - 1] == '*') {
			return memo[i][j] =
				helper(i, j - 2, s, p) ||
				(i > 0 && (p[j - 2] == '.' || s[i - 1] == p[j - 2]) &&
					helper(i - 1, j, s, p));
		} else {
			return memo[i][j] = i > 0 &&
				(p[j - 1] == '.' || s[i - 1] == p[j - 1]) &&
				helper(i - 1, j - 1, s, p);
		}
		return memo[i][j] = false;
	}
};

//动态规划
class Solution3 {
public:
	bool isMatch(string s, string p)
	{
		int sLen = s.size(), pLen = p.size();
		vector<vector<char>> dp(sLen + 1, vector<char>(pLen + 1, false));
		dp[sLen][pLen] = true;
		for (int i = sLen; i >= 0; --i)
		{
			for (int j = pLen - 1; j >= 0; --j)
			{
				if (j + 1 < pLen&&p[j + 1] == '*')
					dp[i][j] = dp[i][j + 2] || (i < sLen && (p[j] == '.' || s[i] == p[j]) && dp[i + 1][j]);
				else
					dp[i][j] = i < sLen && (p[j] == '.' || s[i] == p[j]) && dp[i + 1][j + 1];
			}
		}
		return dp[0][0];
	}
};


//其他方法
//动态规划
class Solution4 {
public:
	bool isMatch(string s, string p)
	{
		int sLen = s.size(), pLen = p.size();
		vector<vector<char>> dp(sLen + 1, vector<char>(pLen + 1, false));
		dp[0][0] = true;
		for (int j = 2; j <= pLen; ++j)
		{
			dp[0][j] = dp[0][j - 2] && p[j - 1] == '*';
		}
		for (int i = 1; i <= sLen; ++i)
		{
			for (int j = 1; j <= pLen; ++j)
			{
				if (p[j - 1] == '*')
				{
					dp[i][j] = dp[i][j - 2] || ((s[i - 1] == p[j - 2] || p[j - 2] == '.') && dp[i - 1][j]);
				}
				else
				{
					if (s[i - 1] == p[j - 1] || p[j - 1] == '.') dp[i][j] = dp[i - 1][j - 1];
				}
			}
		}
		return dp[sLen][pLen];
	}
};

//递归
class Solution5 {
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

