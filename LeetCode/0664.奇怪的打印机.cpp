#include "header.h"

/*

664. 奇怪的打印机

有台奇怪的打印机有以下两个特殊要求：
打印机每次只能打印由 同一个字符 组成的序列
每次可以在从起始到结束的任意位置打印新字符，并且会覆盖掉原来已有的字符

给你一个字符串 s ，你的任务是计算这个打印机打印它需要的最少打印次数

示例 1：
输入：s = "aaabbb"
输出：2
解释：首先打印 "aaa" 然后打印 "bbb"

示例 2：
输入：s = "aba"
输出：2
解释：首先打印 "aaa" 然后在第二个位置打印 "b" 覆盖掉原来的字符 'a'

提示：
1 <= s.length <= 100
s 由小写英文字母组成

*/


// 记忆化搜索
class Solution1 {
public:
	vector<vector<int>> memo;
	int strangePrinter(string s) {
		int len = s.size();
		memo.resize(len, vector<int>(len));
		return helper(s, 0, len - 1);
	}
	int helper(const string &s, int i, int j) {
		if (i == j) return 1;
		if (memo[i][j]) return memo[i][j];
		int res = INT_MAX;
		if (s[i] == s[j]) {
			res = helper(s, i, j - 1);
		} else {
			for (int k = i; k < j; ++k) {
				res = min(res, helper(s, i, k) + helper(s, k + 1, j));
			}
		}
		return memo[i][j] = res;
	}
};


// 自底向上动态规划
class Solution2 {
public:
	int strangePrinter(string s) {
		int len = s.size();
		vector<vector<int>> dp(len, vector<int>(len, INT_MAX));
		for (int i = len - 1; i >= 0; --i) {
			dp[i][i] = 1;
			for (int j = i + 1; j < len; ++j) {
				if (s[i] == s[j]) {
					dp[i][j] = dp[i][j - 1];
				} else {
					for (int k = i; k < j; ++k) {
						dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
					}
				}
			}
		}
		return dp[0][len - 1];
	}
};

