#include "header.h"

/*

实现 pow(x, n) ，即计算 x 的 n 次幂函数。

示例 1:
输入: 2.00000, 10
输出: 1024.00000

示例 2:
输入: 2.10000, 3
输出: 9.26100

示例 3:
输入: 2.00000, -2
输出: 0.25000

*/

class Solution {
public:
	double pow(double x, int n)
	{
		int exponent = n;
		if (n < 0)
		{
			if (n == INT_MIN)
			{
				++exponent;
				exponent = -exponent;
				return 1.0 / (x * posiPow(x, exponent));
			}
			exponent = -exponent;
		}
		double res = posiPow(x, exponent);
		if (n < 0)
			return 1.0 / res;
		return res;
	}
	double posiPow(double x, int n)
	{
		if (n == 1)
			return x;
		if (n == 0)
			return 1;
		double res = posiPow(x, n >> 1);
		res *= res;
		if (n & 1) res *= x;
		return res;
	}
};