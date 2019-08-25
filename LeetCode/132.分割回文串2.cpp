#include "header.h"

/*

给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。
返回符合要求的最少分割次数。

示例:

输入: "aab"
输出: 1
解释: 进行一次分割就可将 s 分割成 ["aa","b"] 这样两个回文子串。

*/

class Solution {
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