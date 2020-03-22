#include "header.h"

/*

给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。
返回 s 所有可能的分割方案。

示例:

输入: "aab"
输出:
[
    ["aa","b"],
    ["a","a","b"]
]

*/

class Solution {
public:
	vector<vector<string>> partition(string s)
	{
		if (s.empty()) return {};
		vector<vector<string>> res;
		vector<string> vec;
		dfs(s, 0, vec, res);
		return res;
	}
	void dfs(string &s, int pos, vector<string> &vec, vector<vector<string>> &res)
	{
		if (pos == s.size())
			res.push_back(vec);
		for (int i = pos; i < s.size(); ++i)
		{
			if (isPal(s, pos, i))
			{
				vec.push_back(s.substr(pos, i - pos + 1));
				dfs(s, i + 1, vec, res);
				vec.pop_back();
			}
		}
	}
	bool isPal(string &s, int low, int high)
	{
		while (low < high)
		{
			if (s[low++] != s[high--])
				return false;
		}
		return true;
	}
};