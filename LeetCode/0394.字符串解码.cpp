#include "header.h"

/*

给定一个经过编码的字符串，返回它解码后的字符串。

编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。

你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。

此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。

示例:
s = "3[a]2[bc]", 返回 "aaabcbc".
s = "3[a2[c]]", 返回 "accaccacc".
s = "2[abc]3[cd]ef", 返回 "abcabccdcdcdef".

*/

//递归法
class Solution1 {
public:
	string decodeString(string s)
	{
		int index = 0;
		return dfs(s, index);
	}
	string dfs(string &s, int &index)
	{
		string res;
		int len = s.size();
		while (index < len&&s[index] != ']')
		{
			if (!isdigit(s[index])) res += s[index++];
			else
			{
				int n = 0;
				while (index < len&&isdigit(s[index]))
					n = n * 10 + s[index++] - '0';
				++index;//'['的下一个位置
				string temp = dfs(s, index);
				++index;//']'的下一个位置
				while (n--) res += temp;
			}
		}
		return res;
	}
};

//栈解法
class Solution2 {
public:
	string decodeString(string s)
	{
		string res;
		int num = 0;
		stack<int> sNum;
		stack<string> sStr;
		for (auto c : s)
		{
			if (c == '[')
			{
				sNum.push(num);
				sStr.push(res);
				num = 0;
				res.clear();
			}
			else if (c == ']')
			{
				string temp;
				int curNum = sNum.top();
				sNum.pop();
				while (curNum--) temp.append(res);
				res = sStr.top() + temp;
				sStr.pop();
			}
			else if (isdigit(c)) num = num * 10 + (c - '0');
			else res.append(1, c);
		}
		return res;
	}
};
//https://leetcode-cn.com/problems/decode-string/solution/decode-string-fu-zhu-zhan-fa-di-gui-fa-by-jyd/