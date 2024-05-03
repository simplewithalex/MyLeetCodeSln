#include "header.h"

/*

440. �ֵ���ĵ�KС����

�������� n �� k������  [1, n] ���ֵ���� k С������

ʾ�� 1:
����: n = 13, k = 2
���: 10
����: �ֵ���������� [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9]�����Եڶ�С�������� 10

ʾ�� 2:
����: n = 1, k = 1
���: 1

��ʾ:
1 <= k <= n <= 10^9

*/

class Solution {
public:
	int findKthNumber(int n, int k) {
		long long p = 1;
		long long prefix = 1;
		while (p < k) {
			long long count = getCount(prefix, n);
			if (p + count > k) {
				prefix *= 10;
				++p;
			}
			else {
				++prefix;
				p += count;
			}
		}
		return static_cast<int>(prefix);
	}

private:
	long long getCount(long long prefix, int n) {
		long long cur = prefix;
		long long next = prefix + 1;
		long long count = 0;
		while (cur <= n) {
			count += min((long long)(n + 1), next) - cur;
			cur *= 10;
			next *= 10;
		}
		return count;
	}
};
// https://leetcode.cn/problems/k-th-smallest-in-lexicographical-order/solutions/27645/ben-ti-shi-shang-zui-wan-zheng-ju-ti-de-shou-mo-sh/
// @author https://leetcode.cn/u/user7056k/
