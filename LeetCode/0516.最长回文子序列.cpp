#include "header.h"

/*

516. 最长回文子序列

给你一个字符串 s ，找出其中最长的回文子序列，并返回该序列的长度

子序列定义为：不改变剩余字符顺序的情况下，删除某些字符或者不删除任何字符形成的一个序列

示例 1：
输入：s = "bbbab"
输出：4
解释：一个可能的最长回文子序列为 "bbbb"

示例 2：
输入：s = "cbbd"
输出：2
解释：一个可能的最长回文子序列为 "bb"

提示：
1 <= s.length <= 1000
s 仅由小写英文字母组成

*/

// 记忆化搜索
class Solution1 {
public:
	vector<vector<int>> memo;
	int longestPalindromeSubseq(string s) {
		int len = s.size();
		memo.resize(len, vector<int>(len, -1));
		return helper(s, 0, len - 1);
	}
	int helper(const string &s, int i, int j) {
		if (i > j) return 0;
		if (i == j) return 1;
		if (memo[i][j] != -1) return memo[i][j];
		int res = 0;
		if (s[i] == s[j]) res = helper(s, i + 1, j - 1) + 2;
		else res = max(helper(s, i + 1, j), helper(s, i, j - 1));
		return memo[i][j] = res;
	}
};

// 自底而上的动态规划
class Solution2 {
public:
	int longestPalindromeSubseq(string s) {
		int len = s.size();
		vector<vector<int>> dp(len, vector<int>(len));
		for (int i = len - 1; i >= 0; --i) {
			dp[i][i] = 1;
			for (int j = i + 1; j < len; ++j) {
				dp[i][j] = s[i] == s[j] ? dp[i + 1][j - 1] + 2
					: max(dp[i + 1][j], dp[i][j - 1]);
			}
		}
		return dp[0][len - 1];
	}
};

// 空间复杂度优化
class Solution3 {
public:
	int longestPalindromeSubseq(string s) {
		int len = s.size();
		vector<int> dp(len);
		for (int i = len - 1; i >= 0; --i) {
			dp[i] = 1;
			int pre = 0;
			for (int j = i + 1; j < len; ++j) {
				int tmp = dp[j];
				dp[j] = s[i] == s[j] ? pre + 2 : max(dp[j], dp[j - 1]);
				pre = tmp;
			}
		}
		return dp[len - 1];
	}
};


