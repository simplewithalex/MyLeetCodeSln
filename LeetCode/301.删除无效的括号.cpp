#include "header.h"

/*

删除最小数量的无效括号，使得输入的字符串有效，返回所有可能的结果。
说明: 输入可能包含了除 ( 和 ) 以外的字符。

示例 1:
输入: "()())()"
输出: ["()()()", "(())()"]

示例 2:
输入: "(a)())()"
输出: ["(a)()()", "(a())()"]

示例 3:
输入: ")("
输出: [""]

*/

//DFS
class Solution1 {
public:
	vector<string> removeInvalidParentheses(string s)
	{
		vector<string> res;
		removeHelper(s, res, 0, 0, '(', ')');
		return res;
	}
	void removeHelper(string s, vector<string> &res, int iStart, int jStart, char openParen, char closeParen)
	{
		int numOpen = 0, numClose = 0;
		int len = s.size();
		for (int i = iStart; i < len; ++i)
		{
			if (s[i] == openParen) ++numOpen;
			if (s[i] == closeParen) ++numClose;
			if (numClose > numOpen)
			{
				for (int j = jStart; j <= i; ++j)
				{
					if (s[j] == closeParen && (j == jStart || s[j - 1] != closeParen))
						removeHelper(s.substr(0, j) + s.substr(j + 1), res, i, j, openParen, closeParen);
				}
				return;
			}
		}
		reverse(s.begin(), s.end());
		if (openParen == '(')
			removeHelper(s, res, 0, 0, ')', '(');
		else
			res.push_back(s);
	}
};
//https://leetcode.com/problems/remove-invalid-parentheses/discuss/75027/Easy-Short-Concise-and-Fast-Java-DFS-3-ms-solution

//BFS
class Solution2 {
public:
	vector<string> removeInvalidParentheses(string s)
	{
		vector<string> res;
		if (s.empty()) return{ "" };
		set<string> visited;
		queue<string> q;
		q.push(s);
		visited.insert(s);
		bool reached = false;
		while (!q.empty())
		{
			int len = q.size();
			for (int i = 0; i < len; ++i)
			{
				string cur = q.front();
				q.pop();
				if (isValid(cur))
				{
					reached = true;
					res.push_back(cur);
				}
				if (!reached)
				{
					int curLen = cur.size();
					for (int j = 0; j < curLen; ++j)
					{
						if (cur[j] != '('&&cur[j] != ')') continue;
						string newStr = cur.substr(0, j) + cur.substr(j + 1);
						if (!visited.count(newStr))
						{
							q.push(newStr);
							visited.insert(newStr);
						}
					}
				}
			}
			if (reached) break;
		}
		return res;
	}
	bool isValid(string s)
	{
		int count = 0, len = s.size();
		for (int i = 0; i < len; ++i)
		{
			if (s[i] == '(') ++count;
			if (s[i] == ')'&&count-- == 0) return false;
		}
		return count == 0;
	}
};
