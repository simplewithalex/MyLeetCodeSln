#include "header.h"

/*

统计所有小于非负整数 n 的质数的数量。

示例 1：

输入：n = 10
输出：4
解释：小于 10 的质数一共有 4 个, 它们是 2, 3, 5, 7 。

示例 2：
输入：n = 0
输出：0

示例 3：
输入：n = 1
输出：0
  
提示：0 <= n <= 5 * 10^6

*/

// 输入n的数据规模较大, 10^6级别
// 朴素方法，会超时
class Solution1 {
public:
	int countPrimes(int n) {
		int cnt = 0;
		for (int i = 2; i < n; ++i) {
			if (isPrime(i)) ++cnt;
		}
		return cnt;
	}

private:
	bool isPrime(int num) {
		for (int i = 2; i * i <= num; ++i) {
			if (num % i == 0) return false;
		}
		return true;
	}
};

// 埃氏筛
class Solution2 {
public:
	int countPrimes(int n) {
		vector<char> isPrime(n, 1);
		for (int i = 2; i * i < n; ++i) {
			if (isPrime[i]) {
				for (int j = i * i; j < n; j += i) isPrime[j] = 0;
			}
		}
		int cnt = 0;
		for (int i = 2; i < n; ++i) {
			if (isPrime[i]) ++cnt;
		}
		return cnt;
	}
};
