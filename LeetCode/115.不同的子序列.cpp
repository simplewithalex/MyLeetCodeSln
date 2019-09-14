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


class Solution1 {
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


//普通的记忆化回溯方法供参考
class Solution2 {
public:
	int numDistinct(string s, string t) 
	{
		int res = 0;
		unordered_map<string, int> m;
		backTrack(s, 0, t, 0, res, m);
		return res;
	}
	void backTrack(string &s, int sIdx, string &t, int tIdx, int &res, unordered_map<string, int> &m)
	{
		if (tIdx == t.size())
		{
			++res;
			return;
		}
		if (sIdx == s.size())
		{
			return;
		}
		//使用哈希表记录在当前s下标与t下标时，后面的字符串会增加的匹配数量。
		string key = to_string(sIdx) + "@" + to_string(tIdx);
		if (m.count(key))
		{
			res += m[key];
			return;
		}
		int preCount = res;
		for (int i = sIdx; i < s.size(); ++i)
		{
			if (s[i] == t[tIdx])
			{
				backTrack(s, i + 1, t, tIdx + 1, res, m);
			}
		}
		m[key] = res - preCount;
	}
};
