#include "header.h"

/*

给定两个单词 word1 和 word2，找到使得 word1 和 word2 相同所需的最小步数，每步可以删除任意一个字符串中的一个字符。

示例：
输入: "sea", "eat"
输出: 2
解释: 第一步将"sea"变为"ea"，第二步将"eat"变为"ea"
  
提示：
给定单词的长度不超过500。
给定单词中的字符只含有小写字母。

*/

//备忘录
class Solution1 {
public:
	int minDistance(string word1, string word2)
	{
		int len1 = word1.size(), len2 = word2.size();
		vector<vector<int>> memo(len1 + 1, vector<int>(len2 + 1, -1));
		return len1 + len2 - 2 * helper(word1, word2, len1, len2, memo);
	}
	int helper(string &word1, string &word2, int m, int n, vector<vector<int>> &memo)
	{
		if (m == 0 || n == 0) return 0;
		if (memo[m][n] != -1) return memo[m][n];
		if (word1[m - 1] == word2[n - 1]) memo[m][n] = 1 + helper(word1, word2, m - 1, n - 1, memo);
		else memo[m][n] = max(helper(word1, word2, m - 1, n, memo), helper(word1, word2, m, n - 1, memo));
		return memo[m][n];
	}
};

//自底而上的动态规划
class Solution2 {
public:
	int minDistance(string word1, string word2) 
	{
		int len1 = word1.size(), len2 = word2.size();
		vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
		for (int i = 0; i <= len1; ++i)
		{
			for (int j = 0; j <= len2; ++j)
			{
				if (i == 0 || j == 0) continue;
				if (word1[i - 1] == word2[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
				else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
		return len1 + len2 - 2 * dp[len1][len2];
	}
};
