#include "header.h"

/*

629. K 个逆序对数组

对于一个整数数组 nums，逆序对是一对满足 0 <= i < j < nums.length 且 nums[i] > nums[j]的整数对 [i, j]

给你两个整数 n 和 k，找出所有包含从 1 到 n 的数字，且恰好拥有 k 个 逆序对 的不同的数组的个数
由于答案可能很大，只需要返回对 10^9 + 7 取余的结果

示例 1：
输入：n = 3, k = 0
输出：1
解释：
只有数组 [1,2,3] 包含了从1到3的整数并且正好拥有 0 个逆序对

示例 2：
输入：n = 3, k = 1
输出：2
解释：
数组 [1,3,2] 和 [2,1,3] 都有 1 个逆序对

提示：
1 <= n <= 1000
0 <= k <= 1000

*/


// 记忆化回溯，TLE
class Solution1 {
public:
	const int MOD = 1E9 + 7;
	vector<vector<long long>> memo;
	int kInversePairs(int n, int k) {
		memo.resize(n + 1, vector<long long>(k + 1, -1));
		return helper(n, k);
	}
	long long helper(int n, int k) {
		if (k > n * (n - 1) / 2) return 0;
		if (n == 1) return k == 0 ? 1 : 0;
		if (memo[n][k] != -1) return memo[n][k];
		long long ans = 0;
		for (int i = max(0, k - n + 1); i <= k; ++i) {
			ans += helper(n - 1, i);
		}
		return memo[n][k] = ans % MOD;
	}
};


// 记忆话回溯优化
class Solution2 {
public:
	const int MOD = 1E9 + 7;
	vector<vector<long long>> memo;
	int kInversePairs(int n, int k) {
		memo.resize(n + 1, vector<long long>(k + 1, -1));
		return helper(n, k);
	}
	long long helper(int n, int k) {
		if (k > n * (n - 1) / 2) return 0;
		if (n == 1) return k == 0 ? 1 : 0;
		if (memo[n][k] != -1) return memo[n][k];
		long long ans = 0;
		ans = (k >= 1 ? helper(n, k - 1) : 0) + helper(n - 1, k) -
			(k >= n ? helper(n - 1, k - n) : 0);
		return memo[n][k] = (ans + MOD) % MOD;
	}
};


// 自底而上的动态规划
class Solution3 {
public:
	const int MOD = 1E9 + 7;
	int kInversePairs(int n, int k) {
		vector<vector<long long>> dp(n + 1, vector<long long>(k + 1));
		dp[1][0] = 1;
		for (int i = 2; i <= n; ++i) {
			for (int j = 0; j <= min(k, i * (i - 1) / 2); ++j) {
				for (int x = max(0, j - i + 1); x <= j; ++x) {
					dp[i][j] = (dp[i][j] + dp[i - 1][x]) % MOD;
				}
			}
		}
		return dp[n][k];
	}
};


// 时间复杂度优化
class Solution4 {
public:
	const int MOD = 1E9 + 7;
	int kInversePairs(int n, int k) {
		vector<vector<long long>> dp(n + 1, vector<long long>(k + 1));
		dp[1][0] = 1;
		for (int i = 2; i <= n; ++i) {
			for (int j = 0; j <= min(k, i * (i - 1) / 2); ++j) {
				dp[i][j] = ((j >= 1 ? dp[i][j - 1] : 0) + dp[i - 1][j] -
					(j >= i ? dp[i - 1][j - i] : 0) + MOD) % MOD;
			}
		}
		return dp[n][k];
	}
};


// 空间复杂度优化
class Solution5 {
public:
	const int MOD = 1E9 + 7;
	int kInversePairs(int n, int k) {
		vector<vector<long long>> dp(2, vector<long long>(k + 1));
		dp[1][0] = 1;
		for (int i = 2; i <= n; ++i) {
			for (int j = 0; j <= min(k, i * (i - 1) / 2); ++j) {
				dp[i & 1][j] = ((j >= 1 ? dp[i & 1][j - 1] : 0) + dp[(i - 1) & 1][j] -
					(j >= i ? dp[(i - 1) & 1][j - i] : 0) + MOD) % MOD;
			}
		}
		return dp[n & 1][k];
	}
};

// https://leetcode.cn/problems/k-inverse-pairs-array/solutions/1096189/tong-ge-lai-shua-ti-la-yi-ti-wu-jie-bao-ej4ym/
// @author https://leetcode.cn/u/tong-zhu/


