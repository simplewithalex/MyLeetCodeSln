#include "header.h"

/*

给你一个整数 n ，请你找出并返回第 n 个丑数。丑数就是只包含质因数 2、3 和/或 5 的正整数。

示例 1：
输入：n = 10
输出：12
解释：[1, 2, 3, 4, 5, 6, 8, 9, 10, 12] 是由前 10 个丑数组成的序列。

示例 2：
输入：n = 1
输出：1
解释：1 通常被视为丑数。
  
提示：1 <= n <= 1690

*/

// 优先级队列
class Solution1 {
public:
	int nthUglyNumber(int n) {
		vector<int> factors{ 2,3,5 };
		unordered_set<long long> s;
		priority_queue<long long, vector<long long>, greater<long long>> pq;
		s.insert(1LL);
		pq.push(1LL);
		int ugly = 0;
		for (int i = 0; i < n; ++i) {
			long long cur = pq.top();
			pq.pop();
			ugly = cur;
			for (int factor : factors) {
				long long next = cur*factor;
				if (!s.count(next)) {
					s.insert(next);
					pq.push(next);
				}
			}
		}
		return ugly;
	}
};

// 多路归并
class Solution2 {
public:
	int nthUglyNumber(int n) {
		vector<int> ugly(n, 0);
		ugly[0] = 1;
		int p2 = 0, p3 = 0, p5 = 0;
		for (int i = 1; i < n; ++i) {
			int u2 = ugly[p2] * 2, u3 = ugly[p3] * 3, u5 = ugly[p5] * 5;
			ugly[i] = min(u2, min(u3, u5));
			if (ugly[i] == u2) ++p2;
			if (ugly[i] == u3) ++p3;
			if (ugly[i] == u5) ++p5;
		}
		return ugly[n - 1];
	}
};