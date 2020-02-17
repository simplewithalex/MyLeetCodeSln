#include "header.h"

/*

给定两个整数，被除数 dividend 和除数 divisor。将两数相除，要求不使用乘法、除法和 mod 运算符。
返回被除数 dividend 除以除数 divisor 得到的商。

示例 1:
输入: dividend = 10, divisor = 3
输出: 3

示例 2:
输入: dividend = 7, divisor = -3
输出: -2

说明:
被除数和除数均为 32 位有符号整数。除数不为 0。
假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−2^31,  2^31 − 1]。本题中，如果除法结果溢出，则返回 2^31-1

*/

class Solution {
public:
	int divide(int dividend, int divisor)
	{
		if (dividend == INT_MIN)
		{
			if (divisor == -1)
				return INT_MAX;
			else if (divisor == 1)
				return dividend;
			else
				return ((divisor & 1) == 1) ? divide(dividend + 1, divisor) : divide(dividend >> 1, divisor >> 1);
		}
		if (divisor == INT_MIN)
			return 0;

		int dvd = abs(dividend), dvs = abs(divisor), ans = 0;
		int sign = (dividend > 0) ^ (divisor > 0) ? -1 : 1;
		while (dvd >= dvs)
		{
			int temp = dvs, m = 1;
			//避免temp << 1 成为0或负数
			while ((temp << 1 <= dvd) && (temp << 1) > 0)
			{
				temp <<= 1;
				m <<= 1;
			}
			dvd -= temp;
			ans += m;
		}
		return ans*sign;
	}
};
//https://leetcode.com/problems/divide-two-integers/discuss/13407/C++-bit-manipulations/13605