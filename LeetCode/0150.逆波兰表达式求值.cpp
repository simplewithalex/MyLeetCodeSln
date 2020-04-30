#include "header.h"

/*

�����沨����ʾ��������ʽ��ֵ��
��Ч����������� +, -, *, / ��ÿ��������������������Ҳ��������һ���沨�����ʽ��

ʾ����
����: ["4", "13", "5", "/", "+"]
���: 6
����: (4 + (13 / 5)) = 6

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