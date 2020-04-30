#include "header.h"

/*

给定两个二进制字符串，返回他们的和（用二进制表示）。
输入为非空字符串且只包含数字 1 和 0。

示例 1:
输入: a = "11", b = "1"
输出: "100"

示例 2:
输入: a = "1010", b = "1011"
输出: "10101"

*/

class Solution {
public:
	string addBinary(string a, string b)
	{
		string res;
		int i = a.size() - 1, j = b.size() - 1, flag = 0;
		while (i >= 0 || j >= 0)
		{
			int sum = flag;
			if (i >= 0) sum += a[i--] - '0';
			if (j >= 0) sum += b[j--] - '0';
			res.append(to_string(sum % 2));
			flag = sum >> 1;
		}
		if (flag)
			res.append(to_string(flag));
		reverse(res.begin(), res.end());
		return res;
	}
};