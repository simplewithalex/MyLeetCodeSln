#include "header.h"

/*

给出 n 代表生成括号的对数，请你写出一个函数，使其能够生成所有可能的并且有效的括号组合。
例如，给出 n = 3，生成结果为：

[
 "((()))",
 "(()())",
 "(())()",
 "()(())",
 "()()()"
]

*/

class Solution {
public:
	vector<string> generateParenthesis(int n)
	{
		if (n == 0) return {};
		vector<string> res;
		recursion(res, "", 0, 0, n);
		return res;
	}
	void recursion(vector<string> &res, string str, int open, int close, int max)
	{
		if (str.size() == max * 2)
		{
			res.push_back(str);
			return;
		}
		if (open < max)
			recursion(res, str + "(", open + 1, close, max);
		if (close < open)
			recursion(res, str + ")", open, close + 1, max);
	}
};