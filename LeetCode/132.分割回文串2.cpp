#include "header.h"

/*

给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。
返回符合要求的最少分割次数。

示例:

输入: "aab"
输出: 1
解释: 进行一次分割就可将 s 分割成 ["aa","b"] 这样两个回文子串。

*/

class Solution1 {
public:
	int minCut(string s)
	{
		int len = s.size();
		vector<int> dp(len + 1);
		//初始化dp数组：对于具有n个字符s[0,n-1]的字符串,它最多需要n-1个切割。 
		//因此，dp数组初始化为dp[i] = i-1，即i之前的字符串最多需要多少次切割。
		for (int i = 0; i <= len; ++i)
		{
			dp[i] = i - 1;
		}
		for (int i = 0; i < len; ++i)
		{
			extend(s, i, i, dp);
			extend(s, i, i + 1, dp);
		}
		return dp[len];
	}
	void extend(string &s, int i, int j, vector<int> &dp)
	{
		for (; i >= 0 && j < s.size(); --i, ++j)
		{
			if (s[i] != s[j])
				break;
			dp[j + 1] = min(dp[j + 1], dp[i] + 1);
		}
	}
};


//参考131题，使用普通的回溯方法。
class Solution2 {
public:
	int minCut(string s) 
	{
		int len = s.size();
		//首先用一个数组记录字符串i:j是否为回文串，避免了频繁调用isPal()
		vector<vector<bool>> dp(len, vector<bool>(len, false));
		for (int palLen = 1; palLen <= len; ++palLen)
		{
			for (int i = 0; i <= len - palLen; ++i)
			{
				int j = i + palLen - 1;
				dp[i][j] = (s[i] == s[j] && (palLen < 3 || dp[i + 1][j - 1]));
			}
		}
		//利用记忆化技术，记忆当前字符后的字符串还需要的最少切割次数。
		map<int, int> m;
		int res = INT_MAX;
		backTrack(s, 0, 0, dp, m, res);
		return res;
	}
	void backTrack(string &s, int start, int cutNum, vector<vector<bool>> &dp, map<int, int> &m, int &res)
	{
		if (m.count(start))
		{
			res = min(res, cutNum + m[start]);
			return;
		}
		if (dp[start][s.size() - 1])
		{
			res = min(res, cutNum);
			return;
		}
		for (int i = start; i < s.size(); ++i)
		{
			if (dp[start][i])
			{
				backTrack(s, i + 1, cutNum + 1, dp, m, res);
			}
		}
		//当前已经切割了cutNum次，回溯后保存之后的字符串还要切割的次数。
		//注意保证res > cutNum,回溯过程中，res可能在之前已经被赋了一个较小值。(比如"aaabaa"，一开始就遇到回文，res被置1)
		if (res>cutNum)
		{
			m[start] = res - cutNum;
		}
	}
};