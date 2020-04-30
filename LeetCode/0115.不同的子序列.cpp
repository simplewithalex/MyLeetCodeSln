#include "header.h"

/*

给定一个字符串 S 和一个字符串 T，计算在 S 的子序列中 T 出现的个数。
一个字符串的一个子序列是指，通过删除一些（也可以不删除）字符且不干扰剩余字符相对位置所组成的新字符串。
（例如，"ACE" 是 "ABCDE" 的一个子序列，而 "AEC" 不是）

示例 1:
输入: S = "rabbbit", T = "rabbit"
输出: 3

解释:
如下图所示, 有 3 种可以从 S 中得到 "rabbit" 的方案。
(上箭头符号 ^ 表示选取的字母)

rabbbit
^^^^ ^^
rabbbit
^^ ^^^^
rabbbit
^^^ ^^^

示例 2:
输入: S = "babgbag", T = "bag"
输出: 5

解释:
如下图所示, 有 5 种可以从 S 中得到 "bag" 的方案。
(上箭头符号 ^ 表示选取的字母)

babgbag
^^ ^
babgbag
^^    ^
babgbag
^    ^^
babgbag
  ^  ^^
babgbag
    ^^^

*/

//备忘录算法
class Solution1 {
public:
	int numDistinct(string S, string T)
	{
		int sLen = S.size(), tLen = T.size();
		vector<vector<int>> memo(sLen + 1, vector<int>(tLen + 1, -1));
		return helper(S, 0, T, 0, memo);
	}
	int helper(string &S,int si,string &T,int ti,vector<vector<int>> &memo)
	{
		if (ti == T.size()) return 1;
		if (si == S.size()) return 0;
		if (memo[si][ti] > -1) return memo[si][ti];
		int count = 0;
		if (S[si] == T[ti])
		{
			count = helper(S, si + 1, T, ti + 1, memo) + helper(S, si + 1, T, ti, memo);
		}
		else
		{
			count = helper(S, si + 1, T, ti, memo);
		}
		return memo[si][ti] = count;
	}
};

//动态规划
class Solution2 {
public:
	int numDistinct(string S, string T)
	{
		int slen = S.size();
		int tlen = T.size();
		vector<vector<unsigned>> dp(tlen + 1, vector<unsigned>(slen + 1));
		for (int i = 0; i < slen + 1; ++i)
		{
			dp[0][i] = 1;
		}
		for (int i = 0; i < tlen; ++i)
		{
			for (int j = 0; j < slen; ++j)
			{
				if (S[j] == T[i])
				{
					dp[i + 1][j + 1] = dp[i][j] + dp[i + 1][j];
				}
				else
				{
					dp[i + 1][j + 1] = dp[i + 1][j];
				}
			}
		}
		return dp[tlen][slen];
	}
};
//DP Solution. Thanks for this link.
//https://leetcode.com/problems/distinct-subsequences/discuss/37327/Easy-to-understand-DP-in-Java