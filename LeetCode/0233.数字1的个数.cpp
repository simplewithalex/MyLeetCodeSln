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

// 数位DP
class Solution2 {
public:
	int countDigitOne(int n) {
		string s = to_string(n);
		int len = s.size();
		if (len == 1) return n == 0 ? 0 : 1;

		vector<int> dp1(len - 1);
		vector<int> dp2(len);
		// 求整块中1的个数
		dp1[0] = 1;
		for (int i = 1; i < len - 1; ++i) {
			dp1[i] = 10 * dp1[i - 1] + pow(10, i);
		}

		if (s[len - 1] == '0') dp2[0] = 0;
		else dp2[0] = 1;

		/*
		 * 以165为例子，这里存在三种情况
		 *（1）百位是1，百位上1的总个数，{1}00 - {1}65
		 *（2）百位是1，其他位上1的总个数，1{00} - 1{65}
		 *（3）百位是0，其他位上1的总个数，0 - 99
		 */
		for (int i = 1; i < len; ++i) {
			char c = s[len - 1 - i];
			if (c == '0') dp2[i] = dp2[i - 1];
			else if (c == '1') dp2[i] = (stoi(s.substr(len - i)) + 1) + dp2[i - 1] + dp1[i - 1];
			else dp2[i] = pow(10, i) + dp2[i - 1] + (c - '0')*dp1[i - 1];
		}
		return dp2[len - 1];
	}
};
