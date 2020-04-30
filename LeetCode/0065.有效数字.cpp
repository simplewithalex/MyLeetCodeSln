#include "header.h"

/*

验证给定的字符串是否可以解释为十进制数字。

例如:

"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
" -90e3   " => true
" 1e" => false
"e3" => false
" 6e-1" => true
" 99e2.5 " => false
"53.5e93" => true
" --6 " => false
"-+3" => false
"95a54e53" => false

说明: 我们有意将问题陈述地比较模糊。在实现代码之前，你应当事先思考所有可能的情况。这里给出一份可能存在于有效十进制数字中的字符列表：

数字 0-9
指数 - "e"
正/负号 - "+"/"-"
小数点 - "."
当然，在输入中，这些字符的上下文也很重要。


*/

class Solution {
public:
	bool isNumber(string s)
	{
		bool point = false, hasE = false, seeNum = false, sign = false;
		int i = 0;
		for (; s[i] == ' '; ++i);
		int first = i;
		for (; i < s.size(); ++i)
		{
			if (s[i] >= '0'&&s[i] <= '9')
			{
				seeNum = true;
			}
			else if (s[i] == '.')
			{
				if (hasE || point) return false;
				point = true;
			}
			else if (s[i] == 'E' || s[i] == 'e')
			{
				if (hasE || !seeNum) return false;
				hasE = true;
				seeNum = false;
			}
			else if (s[i] == '-' || s[i] == '+')
			{
				if (i != first && s[i - 1] != 'E' && s[i - 1] != 'e') return false;
				sign = true;
			}
			else if (s[i] == ' ')
			{
				while (i < s.size())
				{
					if (s[i] != ' ')
						return false;
					++i;
				}
			}
			else
				return false;
		}
		return seeNum;
	}
};