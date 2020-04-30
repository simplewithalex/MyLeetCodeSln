#include "header.h"

/*

给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

示例:
输入："23"
输出：["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
说明:
尽管上面的答案是按字典序排列的，但是你可以任意选择答案输出的顺序。

*/

//一种基于链表的迭代方式
class Solution1 {
public:
	vector<string> letterCombinations(string digits)
	{
		vector<string> v{ "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
		list<string> res(1, "");
		while (res.front().size() != digits.size())
		{
			string temp = res.front();
			res.pop_front();
			string str = v[digits[temp.size()] - '0'];
			for (auto c : str)
			{
				res.push_back(temp + c);
			}
		}
		return vector<string>(res.begin(), res.end());
	}
};

//普通递归法
class Solution2 {
public:
	vector<string> letterCombinations(string digits)
	{
		if (digits.empty()) return{};
		vector<string> v{ "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
		vector<string> res;
		string str;
		backtrack(digits, v, res, str, 0);
		return res;
	}
	void backtrack(string &digits, vector<string> &v, vector<string> &res, string &str, int index)
	{
		if (index == digits.size())
		{
			res.push_back(str);
			return;
		}
		for (int i = 0; i < v[digits[index] - '0'].size(); ++i)
		{
			str.push_back(v[digits[index] - '0'][i]);
			backtrack(digits, v, res, str, index + 1);
			str.pop_back();
		}
	}
};