#include "header.h"

/*

一条包含字母 A-Z 的消息通过以下方式进行了编码：

'A' -> 1
'B' -> 2
...
'Z' -> 26
给定一个只包含数字的非空字符串，请计算解码方法的总数。

示例 1:
输入: "12"
输出: 2
解释: 它可以解码为 "AB"（1 2）或者 "L"（12）。

示例 2:
输入: "226"
输出: 3
解释: 它可以解码为 "BZ" (2 26), "VF" (22 6), 或者 "BBF" (2 2 6) 。

*/

//备忘录算法
class Solution1 {
public:
	int numDecodings(string s)
	{
		int len = s.size();
		vector<int> memo(len, -1);
		return s.empty() ? 0 : helper(s, 0, memo);
	}
	int helper(string &s, int i, vector<int> &memo)
	{
		int len = s.size();
		if (i == len) return 1;
		if (s[i] == '0') return 0;
		if (memo[i] > 0) return memo[i];
		int res = helper(s, i + 1, memo);
		if (i < len - 1 && (s[i] == '1' || (s[i] == '2'&&s[i + 1] < '7'))) res += helper(s, i + 2, memo);
		return memo[i] = res;
	}
};

//自底而上的动态规划
class Solution2 {
public:
	int numDecodings(string s)
	{
		if (s.empty()) return 0;
		int len = s.size();
		vector<int> dp(len + 1, 0);
		dp[len] = 1;
		for (int i = len - 1; i >= 0; --i)
		{
			if (s[i] == '0') dp[i] = 0;
			else
			{
				dp[i] = dp[i + 1];
				if (i < len - 1 && (s[i] == '1' || (s[i] == '2'&&s[i + 1] < '7'))) dp[i] += dp[i + 2];
			}
		}
		return dp[0];
	}
};

//空间优化
class Solution3 {
public:
	int numDecodings(string s)
	{
		if (s.empty()) return 0;
		int len = s.size();
		int res = 1, k = 0;
		for (int i = len - 1; i >= 0; --i)
		{
			int cur = (s[i] == '0') ? 0 : res;
			if (i < len - 1 && (s[i] == '1' || (s[i] == '2'&&s[i + 1] < '7'))) cur += k;
			k = res;
			res = cur;
		}
		return res;
	}
};