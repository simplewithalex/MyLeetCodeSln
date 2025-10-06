#include "header.h"

/*

给定一个非空字符串 s 和一个包含非空单词列表的字典 wordDict，
判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词。

说明：
拆分时可以重复使用字典中的单词。
你可以假设字典中没有重复的单词。

输入: s = "applepenapple", wordDict = ["apple", "pen"]
输出: true
解释: 返回 true 因为 "applepenapple" 可以被拆分成 "apple pen apple"。
     注意你可以重复使用字典中的单词。

*/

//备忘录
class Solution1 {
public:
	bool wordBreak(string s, unordered_set<string> &dict)
	{
		int len = s.size();
		vector<char> memo(len, -1);
		return helper(s, dict, 0, memo);
	}
	bool helper(string &s, unordered_set<string> &dict, int start, vector<char> &memo)
	{
		int len = s.size();
		if (start == len) return true;
		if (memo[start] != -1) return memo[start];
		for (int i = start; i < len; ++i)
		{
			if (dict.count(s.substr(start, i - start + 1)) && helper(s, dict, i + 1, memo)) return memo[start] = true;
		}
		return memo[start] = false;
	}
};

//自底向上动态规划
class Solution2 {
public:
	bool wordBreak(string s, unordered_set<string> &dict)
	{
		int len = s.size();
		vector<bool> conc(len + 1, false);
		conc[0] = true;
		for (int i = 1; i <= len; ++i)
		{
			for (int j = 0; j < i; ++j)
			{
				if (conc[j] && dict.count(s.substr(j, i - j)))
				{
					conc[i] = true;
					break;
				}
			}
		}
		return conc[len];
	}
};


// 灵神的方法
// 记忆化
class Solution3 {
public:
	vector<int> memo;
	unordered_set<string> set;
	int max_length = 0;
	bool wordBreak(string s, vector<string> &wordDict) {
		set.insert(wordDict.begin(), wordDict.end());
		for (const auto &str : wordDict) max_length = max(max_length, (int)str.length());
		int len = s.size();
		memo.resize(len + 1, -1);
		return helper(s, len);
	}
	bool helper(string &s, int i) {
		if (i == 0) return true;
		if (memo[i] != -1) return memo[i];
		for (int j = i - 1; j >= max(i - max_length, 0); --j) {
			if (set.count(s.substr(j, i - j)) && helper(s, j)) return memo[i] = true;
		}
		return memo[i] = false;
	}
};

// 动态规划
class Solution4 {
public:
	bool wordBreak(string s, vector<string> &wordDict) {
		unordered_set<string> set(wordDict.begin(), wordDict.end());
		int max_length = 0;
		for (const auto &str : wordDict) max_length = max(max_length, (int)str.length());
		int len = s.size();
		vector<int> dp(len + 1);
		dp[0] = true;
		for (int i = 1; i <= len; ++i) {
			for (int j = i - 1; j >= max(i - max_length, 0); --j) {
				if (set.count(s.substr(j, i - j)) && dp[j]) {
					dp[i] = true;
					break;
				}
			}
		}
		return dp[len];
	}
};

// https://leetcode.cn/problems/word-break/solutions/2968135/jiao-ni-yi-bu-bu-si-kao-dpcong-ji-yi-hua-chrs/
// @author https://leetcode.cn/u/endlesscheng/


