#include "header.h"

/*

887. 鸡蛋掉落

给你 k 枚相同的鸡蛋，并可以使用一栋从第 1 层到第 n 层共有 n 层楼的建筑。
已知存在楼层 f，满足 0 <= f <= n，任何从 高于 f 的楼层落下的鸡蛋都会碎，从 f 楼层或比它低的楼层落下的鸡蛋都不会破。
每次操作，你可以取一枚没有碎的鸡蛋并把它从任一楼层 x 扔下（满足 1 <= x <= n）。
如果鸡蛋碎了，你就不能再次使用它。如果某枚鸡蛋扔下后没有摔碎，则可以在之后的操作中 重复使用 这枚鸡蛋。

请你计算并返回要确定 f 确切的值 的 最小操作次数 是多少？

示例 1：
输入：k = 1, n = 2
输出：2
解释：
鸡蛋从 1 楼掉落。如果它碎了，肯定能得出 f = 0
否则，鸡蛋从 2 楼掉落。如果它碎了，肯定能得出 f = 1
如果它没碎，那么肯定能得出 f = 2
因此，在最坏的情况下我们需要移动 2 次以确定 f 是多少

示例 2：
输入：k = 2, n = 6
输出：3

示例 3：
输入：k = 3, n = 14
输出：4

提示：
1 <= k <= 100
1 <= n <= 10^4

*/


class Solution1 {
private:
	vector<vector<int>> memo;

public:
	int superEggDrop(int k, int n) {
		memo.resize(k + 1, vector<int>(n + 1, -1));
		return helper(k, n);
	}

private:
	int helper(int k, int n) {
		if (k == 1) return n;
		if (n == 0) return 0;
		if (memo[k][n] != -1) return memo[k][n];
		int res = INT_MAX;
		for (int i = 1; i <= n; ++i) {
			res = min(res, max(helper(k, n - i), helper(k - 1, i - 1)) + 1);
		}
		return memo[k][n] = res;
	}
};

// 二分查找优化
class Solution2 {
private:
	vector<vector<int>> memo;

public:
	int superEggDrop(int k, int n) {
		memo.resize(k + 1, vector<int>(n + 1, -1));
		return helper(k, n);
	}

private:
	int helper(int k, int n) {
		if (k == 1) return n;
		if (n == 0) return 0;
		if (memo[k][n] != -1) return memo[k][n];
		int lo = 1, hi = n;
		while (lo < hi) {
			int mi = lo + (hi - lo) / 2;
			int broken = helper(k - 1, mi - 1);
			int nbroken = helper(k, n - mi);
			broken < nbroken ? lo = mi + 1 : hi = mi;
		}
		return memo[k][n] = max(helper(k, n - lo), helper(k - 1, lo - 1)) + 1;
	}
};

/*

这个题目与 LeetCode 458 可怜的小猪 有点像，题意实际上是指在这些楼层中，能够保证找到一个任意的位置 f，
所需要的操作次数至少是多少。这个 f 可能在任意位置，所以结果需要在能够保证这一点的同时做到最少。

*/