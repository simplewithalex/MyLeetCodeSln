#include "header.h"

/*

给定两个单词（beginWord 和 endWord）和一个字典 wordList，找出所有从 beginWord 到 endWord 的最短转换序列。
转换需遵循如下规则：
每次转换只能改变一个字母。
转换过程中的中间单词必须是字典中的单词。

说明:
如果不存在这样的转换序列，返回一个空列表。
所有单词具有相同的长度。
所有单词只由小写字母组成。
字典中不存在重复的单词。
你可以假设 beginWord 和 endWord 是非空的，且二者不相同。

示例 1:
输入:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]
输出:
[
  ["hit","hot","dot","dog","cog"],
  ["hit","hot","lot","log","cog"]
]

示例 2:
输入:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]
输出: []
解释: endWord "cog" 不在字典中，所以不存在符合要求的转换序列。

*/

class Solution {
public:
	vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList)
	{
		unordered_set<string> dict(wordList.begin(), wordList.end());
		vector<vector<string>> res;
		unordered_map<string, vector<string>> nodeNeighbors;
		unordered_map<string, int> distance;
		vector<string> vec;
		dict.insert(beginWord);
		bfs(beginWord, endWord, dict, nodeNeighbors, distance);
		dfs(beginWord, endWord, dict, nodeNeighbors, distance, vec, res);
		return res;
	}
	void bfs(string &start, string &end, unordered_set<string> &dict, unordered_map<string, vector<string>> &nodeNeighbors, unordered_map<string, int> &distance)
	{
		queue<string> q;
		q.push(start);
		distance[start] = 0;
		while (!q.empty())
		{
			int len = q.size();
			bool foundEnd = false;
			for (int i = 0; i < len; ++i)
			{
				string temp = q.front();
				q.pop();
				int curDistance = distance[temp];
				vector<string> neighbors = getNeighbors(temp, dict);
				for (auto neighbor : neighbors)
				{
					nodeNeighbors[temp].push_back(neighbor);
					if (!distance.count(neighbor))
					{
						distance[neighbor] = curDistance + 1;
						if (neighbor == end)
							foundEnd = true;
						else
							q.push(neighbor);
					}
				}
			}
			if (foundEnd) break;
		}
	}
	vector<string> getNeighbors(string &node, unordered_set<string> &dict)
	{
		vector<string> res;
		for (int i = 0; i < node.size(); ++i)
		{
			char c = node[i];
			for (int j = 0; j < 26; ++j)
			{
				node[i] = 'a' + j;
				if (node[i] == c) continue;
				if (dict.count(node)) res.push_back(node);
			}
			node[i] = c;
		}
		return res;
	}
	void dfs(string &start, string &end, unordered_set<string> &dict, unordered_map<string, vector<string>> &nodeNeighbors, unordered_map<string, int> &distance, vector<string> vec, vector<vector<string>> &res)
	{
		vec.push_back(start);
		if (start == end) res.push_back(vec);
		else
		{
			for (auto str : nodeNeighbors[start])
			{
				if (distance[str] == distance[start] + 1)
					dfs(str, end, dict, nodeNeighbors, distance, vec, res);
			}
		}
	}
};