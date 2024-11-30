#include "header.h"

/*

400. 第 N 位数字

给你一个整数 n ，请你在无限的整数序列 [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...] 中找出并返回第 n 位上的数字

示例 1：
输入：n = 3
输出：3

示例 2：
输入：n = 11
输出：0
解释：第 11 位数字在序列 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... 里是 0 ，它是 10 的一部分

提示：
1 <= n <= 2^31 - 1

*/

class Solution {
public:
	int findNthDigit(int n) {
		int lo = 1, hi = 9;
		while (lo < hi) {
			int mi = lo + (hi - lo) / 2;
			totalDigits(mi) < n ? lo = mi + 1 : hi = mi;
		}
		int d = lo;
		int preDigits = totalDigits(d - 1);
		int index = n - preDigits - 1;
		int start = pow(10, d - 1);
		int num = start + index / d;
		int digitIdx = index % d;
		int digit = (int)(num / pow(10, d - digitIdx - 1)) % 10;
		return digit;
	}
	int totalDigits(int length) {
		int digits = 0;
		int curLen = 1, cnt = 9;
		while (curLen <= length) {
			digits += curLen * cnt;
			++curLen;
			cnt *= 10;
		}
		return digits;
	}
};

