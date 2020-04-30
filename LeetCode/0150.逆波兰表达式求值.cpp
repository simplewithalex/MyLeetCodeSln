#include "header.h"

/*

根据逆波兰表示法，求表达式的值。
有效的运算符包括 +, -, *, / 。每个运算对象可以是整数，也可以是另一个逆波兰表达式。

示例：
输入: ["4", "13", "5", "/", "+"]
输出: 6
解释: (4 + (13 / 5)) = 6

*/

class Solution {
public:
	int evalRPN(vector<string> &tokens)
	{
		if (tokens.empty())
			return 0;
		stack<int> sta;
		int len = tokens.size();
		for (int i = 0; i < len; ++i)
		{
			string temp = tokens[i];
			if (temp == "+")
			{
				int num1 = sta.top();
				sta.pop();
				int num2 = sta.top();
				sta.pop();
				num1 = num2 + num1;
				sta.push(num1);
			}
			else if (temp == "-")
			{
				int num1 = sta.top();
				sta.pop();
				int num2 = sta.top();
				sta.pop();
				num1 = num2 - num1;
				sta.push(num1);
			}
			else if (temp == "*")
			{
				int num1 = sta.top();
				sta.pop();
				int num2 = sta.top();
				sta.pop();
				num1 = num2*num1;
				sta.push(num1);
			}
			else if (temp == "/")
			{
				int num1 = sta.top();
				sta.pop();
				int num2 = sta.top();
				sta.pop();
				num1 = num2 / num1;
				sta.push(num1);
			}
			else
			{
				int num = stoi(temp);
				sta.push(num);
			}
		}
		return sta.top();
	}
};