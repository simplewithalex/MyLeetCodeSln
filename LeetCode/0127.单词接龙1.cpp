#include "header.h"

/*

给定两个单词（beginWord 和 endWord）和一个字典，找到从 beginWord 到 endWord 的最短转换序列的长度。
转换需遵循如下规则：
每次转换只能改变一个字母。
转换过程中的中间单词必须是字典中的单词。

说明:
如果不存在这样的转换序列，返回 0。
所有单词具有相同的长度。
所有单词只由小写字母组成。
字典中不存在重复的单词。
你可以假设 beginWord 和 endWord 是非空的，且二者不相同。

示例 1:
输入:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]
输出: 5
解释: 一个最短转换序列是 "hit" -> "hot" -> "dot" -> "dog" -> "cog",
返回它的长度 5。

示例 2:
输入:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]
输出: 0
解释: endWord "cog" 不在字典中，所以无法进行转换。

*/


class Solution {
public:
	int ladderLength(string start, string end, unordered_set<string> &dict)
	{
		queue<string> q;
		q.push(start);
		dict.erase(start);
		int ladder = 1;
		while (!q.empty())
		{
			int len = q.size();
			for (int i = 0; i < len; ++i)
			{
				string temp = q.front();
				q.pop();
				for (int j = 0; j < temp.size(); ++j)
				{
					char c = temp[j];
					for (int k = 0; k < 26; ++k)
					{
						temp[j] = 'a' + k;
						if (dict.find(temp) != dict.end())
						{
							if (temp == end) return ladder + 1;
							q.push(temp);
							dict.erase(temp);
						}
					}
					temp[j] = c;
				}
			}
			++ladder;
		}
		return 0;
	}
};
//典型的宽度优先搜索问题。
//https://leetcode.com/problems/word-ladder/discuss/40707/C%2B%2B-BFS