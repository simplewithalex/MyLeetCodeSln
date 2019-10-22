#include "header.h"

/*

给定两个以字符串形式表示的非负整数 num1 和 num2，返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式。

示例 1:
输入: num1 = "2", num2 = "3"
输出: "6"

示例 2:
输入: num1 = "123", num2 = "456"
输出: "56088"

说明：
num1 和 num2 的长度小于110。
num1 和 num2 只包含数字 0-9。
num1 和 num2 均不以零开头，除非是数字 0 本身。
不能使用任何标准库的大数类型（比如 BigInteger）或直接将输入转换为整数来处理。

*/

class Solution {
public:
	string multiply(string num1, string num2)
	{
		int len1 = num1.size(), len2 = num2.size();
		vector<int> v(len1 + len2);
		for (int i = len1 - 1; i >= 0; --i)
		{
			for (int j = len2 - 1; j >= 0; --j)
			{
				int mul = (num1[i] - '0')*(num2[j] - '0');
				int p1 = i + j, p2 = i + j + 1;
				int sum = mul + v[p2];
				v[p1] += sum / 10;
				v[p2] = sum % 10;
			}
		}
		string res;
		for (auto i : v)
		{
			if (!(res.empty() && i == 0))
			{
				res += to_string(i);
			}
		}
		return res.empty() ? "0" : res;
	}
};
//https://leetcode.com/problems/multiply-strings/discuss/17605/Easiest-JAVA-Solution-with-Graph-Explanation