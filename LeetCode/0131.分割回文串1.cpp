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

class Solution1 {
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


class Solution2 {
private:
	vector<vector<char>> isPal;
	vector<vector<string>> res;
	vector<string> path;

public:
	vector<vector<string>> partition(string s) {
		int len = s.size();
		isPal.resize(len, vector<char>(len, false));
		for (int palLen = 1; palLen <= len; ++palLen) {
			for (int i = 0; i <= len - palLen; ++i) {
				int j = i + palLen - 1;
				isPal[i][j] =
					(s[i] == s[j] && (palLen < 3 || isPal[i + 1][j - 1]));
			}
		}
		backtrack(s, 0);
		return res;
	}

private:
	void backtrack(const string &s, int idx) {
		if (idx == s.size()) {
			res.push_back(path);
			return;
		}
		for (int j = idx; j < s.size(); ++j) {
			if (isPal[idx][j]) {
				path.push_back(s.substr(idx, j - idx + 1));
				backtrack(s, j + 1);
				path.pop_back();
			}
		}
	}
};

// 中心扩展法作预处理
class Solution3 {
private:
	vector<vector<char>> isPal;
	vector<vector<string>> res;
	vector<string> path;

public:
	vector<vector<string>> partition(string s) {
		int len = s.size();
		isPal.resize(len, vector<char>(len, false));
		for (int i = 0; i < len; ++i) {
			extend(s, i, i, isPal);
			extend(s, i, i + 1, isPal);
		}
		backtrack(s, 0);
		return res;
	}

private:
	void backtrack(const string &s, int idx) {
		if (idx == s.size()) {
			res.push_back(path);
			return;
		}
		for (int j = idx; j < s.size(); ++j) {
			if (isPal[idx][j]) {
				path.push_back(s.substr(idx, j - idx + 1));
				backtrack(s, j + 1);
				path.pop_back();
			}
		}
	}
	void extend(string &s, int i, int j, vector<vector<char>> &isPal) {
		for (; i >= 0 && j < s.size(); --i, ++j) {
			if (s[i] != s[j]) break;
			isPal[i][j] = true;
		}
	}
};
