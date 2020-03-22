#include "header.h"

/*

给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。
返回符合要求的最少分割次数。

示例:

输入: "aab"
输出: 1
解释: 进行一次分割就可将 s 分割成 ["aa","b"] 这样两个回文子串。

*/

//中心扩展法
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


//参考131题，备忘录到自底而上的动态规划

//备忘录
class Solution2 {
public:
	int minCut(string s) 
	{
		int len = s.size();
		//首先用一个数组记录字符串i:j是否为回文串，避免了频繁调用isPal()
		vector<vector<char>> isPal(len, vector<char>(len, false));
		for (int palLen = 1; palLen <= len; ++palLen)
		{
			for (int i = 0; i <= len - palLen; ++i)
			{
				int j = i + palLen - 1;
				isPal[i][j] = (s[i] == s[j] && (palLen < 3 || isPal[i + 1][j - 1]));
			}
		}
		//利用记忆化技术存储前面已经得到的结果
		vector<int> memo(len, -1);
		return helper(s, 0, isPal, memo);
	}
	int helper(string &s, int start, vector<vector<char>> &isPal, vector<int> &memo)
	{
		if (memo[start] != -1) return memo[start];
		int len = s.size();
		if (isPal[start][len - 1]) return 0;
		int minNum = INT_MAX;
		for (int i = start; i < len; ++i)
		{
			if (isPal[start][i]) minNum = min(minNum, 1 + helper(s, i + 1, isPal, memo));
		}
		memo[start] = minNum;
		return minNum;
	}
};

//自底而上的动态规划
class Solution3 {
public:
	int minCut(string s) 
	{
		int len = s.size();
		//首先用一个数组记录字符串i:j是否为回文串，避免了频繁调用isPal()
		vector<vector<char>> isPal(len, vector<char>(len, false));
		for (int palLen = 1; palLen <= len; ++palLen)
		{
			for (int i = 0; i <= len - palLen; ++i)
			{
				int j = i + palLen - 1;
				isPal[i][j] = (s[i] == s[j] && (palLen < 3 || isPal[i + 1][j - 1]));
			}
		}
		vector<int> dp(len + 1);
		dp[0] = -1;
		for (int i = 0; i < len; ++i)
		{
			int minNum = INT_MAX;
			//这里不一定后面字符串是回文串就是最优情况，比如abbab，还是需要向后继续判断
			for (int j = 0; j <= i; ++j)
			{
				if (isPal[j][i]) minNum = min(minNum, dp[j] + 1);
			}
			dp[i + 1] = minNum;
		}
		return dp[len];
	}
};

//优化上一解法中isPal数组和dp数组的求值
class Solution4 {
public:
	int minCut(string s) 
	{
		int len = s.size();
		vector<vector<char>> isPal(len, vector<char>(len, false));
		vector<int> dp(len + 1);
		dp[0] = -1;
		for (int i = 0; i < len; ++i)
		{
			int minNum = INT_MAX;
			for (int j = 0; j <= i; ++j)
			{
				if (s[i] == s[j] && (j + 1 > i - 1 || isPal[j + 1][i - 1]))
				{
					isPal[j][i] = true;
					minNum = min(minNum, dp[j] + 1);
				}
			}
			dp[i + 1] = minNum;
		}
		return dp[len];
	}
};