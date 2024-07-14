#include "header.h"

/*

479. 最大回文数乘积

给定一个整数 n ，返回 可表示为两个 n 位整数乘积的 最大回文整数

因为答案可能非常大，所以返回它对 1337 取余

示例 1：
输入：n = 2
输出：987
解释：99 x 91 = 9009, 9009 % 1337 = 987

示例 2：
输入：n = 1
输出：9

提示:
1 <= n <= 8


*/


class Solution {
public:
	int largestPalindrome(int n) {
		if (n == 1) return 9;
		int maxNum = pow(10, n) - 1;
		for (int i = maxNum; i >= 10; --i) {
			long long num = i;
			int b = i;
			while (b != 0) {
				num = num * 10 + b % 10;
				b /= 10;
			}
			for (long long j = maxNum; j * j >= num; --j) {
				if (num % j == 0) return (int)(num % 1337);
			}
		}
		return -1;
	}
};
// https://leetcode.cn/problems/largest-palindrome-product/solutions/1424568/by-ac_oier-t8j7/comments/1509501
// @author https://leetcode.cn/u/A23187/


