#include "header.h"

/*

给定一个非空字符串 s 和一个包含非空单词列表的字典 wordDict，
在字符串中增加空格来构建一个句子，使得句子中所有的单词都在词典中。
返回所有这些可能的句子。

说明：
分隔时可以重复使用字典中的单词。
你可以假设字典中没有重复的单词。

输入:
s = "catsanddog"
wordDict = ["cat", "cats", "and", "sand", "dog"]

输出:
[
  "cats and dog",
  "cat sand dog"
]

*/

// 该算法使用了记忆化回溯，可以避免重复递归，回溯前可以先使用 单词拆分 1 中的算法检查是否可拆分。
class Solution1 {
public:
	vector<string> wordBreak(string s, vector<string> &wordDict)
	{
		unordered_set<string> dict(wordDict.begin(), wordDict.end());
		unordered_map<int, vector<string>> m;
		if (!canBreak(s, dict)) return {};
		return backtrack(s, 0, m, dict);
	}
	vector<string> backtrack(string &s, int index, unordered_map<int, vector<string>> &m, unordered_set<string> &dict)
	{
		if (m.count(index)) return m[index];
		vector<string> res;
		if (index == s.size())
		{
			res.push_back("");
		}
		else
		{
			for (int i = index; i < s.size(); ++i)
			{
				if (dict.count(s.substr(index, i - index + 1)))
				{
					vector<string> tmp = backtrack(s, i + 1, m, dict);
					for (auto &str : tmp)
					{
						res.push_back(s.substr(index, i - index + 1) + (str.empty() ? "" : " ") + str);
					}
				}
			}
		}
		m[index] = res;
		return res;
	}
	bool canBreak(string &s, unordered_set<string> &dict)
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

// 使用普通回溯，通过对比可以看出记忆化回溯的优势。
class Solution2 {
public:
	vector<string> wordBreak(string s, vector<string> &wordDict)
	{
		unordered_set<string> dict(wordDict.begin(), wordDict.end());
		vector<string> res;
		vector<string> tmp;
		if (!canBreak(s, dict)) return{};
		backtrack(s, 0, res, tmp, dict);
		return res;
	}
	void backtrack(string &s, int start, vector<string> &res, vector<string> &tmp, unordered_set<string> &dict)
	{
		if (start == s.size())
		{
			string str;
			for (auto str1 : tmp)
				str += str1 + " ";
			str.pop_back();
			res.push_back(str);
		}
		for (int end = start; end < s.size(); ++end)
		{
			if (dict.count(s.substr(start, end - start + 1)))
			{
				tmp.push_back(s.substr(start, end - start + 1));
				backtrack(s, end + 1, res, tmp, dict);
				tmp.pop_back();
			}
		}
	}
	bool canBreak(string &s, unordered_set<string> &dict)
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


// 借鉴 单词拆分 1 中灵神的方法
// 记忆化
class Solution3 {
public:
	unordered_set<string> set;
	unordered_map<int, vector<string>> map;
	int max_length = 0;
	vector<string> wordBreak(string s, vector<string> &wordDict) {
		set.insert(wordDict.begin(), wordDict.end());
		for (const auto &str : wordDict) max_length = max(max_length, (int)str.length());
		int len = s.size();
		helper(s, len);
		return map[len];
	}
	void helper(string &s, int i) {
		if (map.count(i)) return;
		map[i] = {};
		if (i == 0) {
			map[i].push_back("");
			return;
		}
		for (int j = i - 1; j >= max(i - max_length, 0); --j) {
			string word = s.substr(j, i - j);
			if (set.count(word)) {
				helper(s, j);
				for (const string &prefix : map[j]) {
					map[i].push_back(prefix.empty() ? word
													: prefix + " " + word);
				}
			}
		}
	}
};

// 动态规划
class Solution4 {
public:
	vector<string> wordBreak(string s, vector<string> &wordDict) {
		unordered_set<string> set(wordDict.begin(), wordDict.end());
		int max_length = 0;
		for (const auto &str : wordDict) max_length = max(max_length, (int)str.length());
		int len = s.size();
		unordered_map<int, vector<string>> dp;
		dp[0] = { "" };
		for (int i = 1; i <= len; ++i) {
			dp[i] = {};
			for (int j = i - 1; j >= max(i - max_length, 0); --j) {
				string word = s.substr(j, i - j);
				if (set.count(word)) {
					for (const string &prefix : dp[j]) {
						dp[i].push_back(prefix.empty() ? word
													   : prefix + " " + word);
					}
				}
			}
		}
		return dp[len];
	}
};
// 这个方法对于某些case有缺陷，比如：
// s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
// wordDict = ["a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa"]
// 这个case实际上 i下标 不会遍历到 0，在中间某个值 不符条件 就可以返回了，剩下的可以全部剪掉，所以 记忆化 优于 自底而上的动态规划



