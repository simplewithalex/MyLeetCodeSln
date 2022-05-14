#include "header.h"

/*

超级丑数是一个正整数，并满足其所有质因数都出现在质数数组 primes 中。给你一个整数 n 和一个整数数组 primes ，返回第 n 个 超级丑数
题目数据保证第 n 个 超级丑数 在 32-bit 带符号整数范围内

示例 1：
输入：n = 12, primes = [2,7,13,19]
输出：32
解释：给定长度为 4 的质数数组 primes = [2,7,13,19]，前 12 个超级丑数序列为：[1,2,4,7,8,13,14,16,19,26,28,32] 。

示例 2：
输入：n = 1, primes = [2,3,5]
输出：1
解释：1 不含质因数，因此它的所有质因数都在质数数组 primes = [2,3,5] 中。

提示：
1 <= n <= 10^6
1 <= primes.length <= 100
2 <= primes[i] <= 1000
题目数据保证 primes[i] 是一个质数
primes中的所有值都互不相同 ，且按递增顺序排列

*/

// 参考0264，多路归并
class Solution {
public:
	int nthSuperUglyNumber(int n, vector<int> &primes) {
		vector<int> ugly(n);
		int len = primes.size();
		vector<int> p(len);
		vector<long long> nums(len);
		ugly[0] = 1;
		for (int i = 1; i < n; ++i) {
			long long minNum = INT_MAX;
			for (int j = 0; j < len; ++j) {
				nums[j] = ugly[p[j]] * primes[j];
				minNum = min(minNum, nums[j]);
			}
			ugly[i] = minNum;
			for (int j = 0; j < len; ++j) {
				if (ugly[i] == nums[j]) ++p[j];
			}
		}
		return ugly[n - 1];
	}
};