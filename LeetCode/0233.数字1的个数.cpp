#include "header.h"

/*

233. 数字 1 的个数

给定一个整数 n，计算所有小于等于 n 的非负整数中数字 1 出现的个数。

示例 1：
输入：n = 13
输出：6

示例 2：
输入：n = 0
输出：0

提示：0 <= n <= 10^9

*/

// 找计数规律
class Solution1 {
public:
	int countDigitOne(int n)
	{
		if (n <= 0) return 0;
		int res = 0;
		for (long long digit = 1; digit <= n; digit *= 10) {
			int a = n / digit, b = n % digit;
			res += (a + 8) / 10 * digit + (a % 10 == 1) * (b + 1);
		}
		return res;
	}
};
/**
 * https://leetcode-cn.com/problems/number-of-digit-one/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-50/
 * @author https://leetcode-cn.com/u/windliang/
*/

// TODO 数位DP