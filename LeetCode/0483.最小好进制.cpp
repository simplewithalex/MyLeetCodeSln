#include "header.h"

/*

483. 最小好进制

以字符串的形式给出 n, 以字符串的形式返回 n 的最小好进制

如果 n 的 k(k>=2) 进制数的所有数位全为 1，则称 k(k>=2) 是 n 的一个好进制

示例 1：
输入：n = "13"
输出："3"
解释：13 的 3 进制是 111

示例 2：
输入：n = "4681"
输出："8"
解释：4681 的 8 进制是 11111

示例 3：
输入：n = "1000000000000000000"
输出："999999999999999999"
解释：1000000000000000000 的 999999999999999999 进制是 11

提示：
n 的取值范围是 [3, 10^18]
n 没有前导 0

*/


typedef unsigned long long ULL;

class Solution {
public:
	string smallestGoodBase(string n) {
		ULL num = stoull(n);
		// 最大 61 个 1 ，最少 3 个 1 ，如果都不成立，则返回 num - 1 进制，即用 11 表示
		for (int i = 61; i > 2; --i) {
			ULL lo = 2, hi = num - 2;
			while (lo < hi) {
				ULL mi = lo + (hi - lo) / 2;
				cmp(num, i, mi) < 0 ? lo = mi + 1 : hi = mi;
			}
			if (!cmp(num, i, lo)) return to_string(lo);
		}
		return to_string(num - 1);
	}

private:
	char cmp(ULL num, int cnt, ULL base) {
		ULL cur = 0;
		// 秦九韶算法
		for (size_t i = 0; i < cnt; ++i) {
			// 防止越界
			if (cur >(num - 1) / base) return 1;
			cur = cur * base + 1;
		}
		if (cur < num) return -1;
		return 0;
	}
};
// 因为 n <= 10^18, 所以 n < (1<<62), 用2进制最多也不会超过62个1

