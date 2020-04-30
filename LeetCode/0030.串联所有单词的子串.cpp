#include "header.h"

/*

给定一个字符串 s 和一些长度相同的单词 words。找出 s 中恰好可以由 words 中所有单词串联形成的子串的起始位置。
注意子串要与 words 中的单词完全匹配，中间不能有其他字符，但不需要考虑 words 中单词串联的顺序。

示例 1：
输入：
s = "barfoothefoobarman",
words = ["foo","bar"]
输出：[0,9]
解释：
从索引 0 和 9 开始的子串分别是 "barfoo" 和 "foobar" 。
输出的顺序不重要, [9,0] 也是有效答案。
 
示例 2：
输入：
s = "wordgoodgoodgoodbestword",
words = ["word","good","best","word"]
输出：[]

*/

class Solution {
public:
	vector<int> findSubstring(string s, vector<string> &words) 
	{
		if (words.empty()) return {};
		unordered_map<string, int> m;
		for (auto word : words) ++m[word];
		vector<int> res;
		int len = s.size(), count = words.size(), num = words[0].size();
		for (int i = 0; i <= len - count*num; ++i)
		{
			unordered_map<string, int> seen;
			int j = 0;
			while (j < count)
			{
				string temp = s.substr(i + j * num, num);
				if (m.count(temp))
				{
					++seen[temp];
					if (seen[temp] > m[temp]) break;//连续多个相同超出实际数目
				}
				else break;
				++j;
			}
			if (j == count) res.push_back(i);
		}
		return res;
	}
};
//https://leetcode.com/problems/substring-with-concatenation-of-all-words/discuss/13658/Easy-Two-Map-Solution-(C%2B%2BJava)