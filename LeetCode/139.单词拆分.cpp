﻿#include "header.h"

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

class Solution {
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