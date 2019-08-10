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

//该算法使用了记忆化回溯，可以避免重复递归，回溯前可以先使用单词拆分1中的算法检查是否可拆分。
class Solution1 {
public:
	vector<string> wordBreak(string s, vector<string> &wordDict)
	{
		unordered_set<string> dict(wordDict.begin(), wordDict.end());
		unordered_map<int, vector<string>> m;
		if (!canBreak(s, dict)) return{};
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
						res.push_back(s.substr(index, i - index + 1) + (str.empty() ? "" : " ") + str);
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

//使用普通回溯，通过对比可以看出记忆化回溯的优势。
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