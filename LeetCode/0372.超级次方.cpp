#include "header.h"

/*

你的任务是计算 ab 对 1337 取模，a 是一个正整数，b 是一个非常大的正整数且会以数组形式给出


示例 1：
输入：a = 2, b = [3]
输出：8

示例 2：
输入：a = 2, b = [1,0]
输出：1024

示例 3：
输入：a = 1, b = [4,3,3,8,5,2]
输出：1

示例 4：
输入：a = 2147483647, b = [2,0,0]
输出：1198

提示：
1 <= a <= 2^31 - 1
1 <= b.length <= 2000
0 <= b[i] <= 9
b 不含前导 0

*/


class Solution {
private:
	int MOD = 1337;

public:
	int superPow(int a, vector<int>& b) { return helper(a, b, b.size() - 1); }

private:
	int helper(int a, vector<int>& b, int idx) {
		if (idx == -1) return 1;
		return (quickPow(helper(a, b, idx - 1), 10) * quickPow(a, b[idx])) % MOD;
	}
	int quickPow(int a, int b) {
		a %= MOD;
		int res = 1;
		while (b) {
			if (b & 1) res = (res * a) % MOD;
			a = (a * a) % MOD;
			b >>= 1;
		}
		return res;
	}
};
// https://leetcode.cn/problems/super-pow/solutions/1139068/gong-shui-san-xie-di-gui-kuai-su-mi-ying-yx1j/
// @author https://leetcode.cn/u/ac_oier/

