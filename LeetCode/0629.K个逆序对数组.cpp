#include "header.h"

/*

629. K �����������

����һ���������� nums���������һ������ 0 <= i < j < nums.length �� nums[i] > nums[j]�������� [i, j]

������������ n �� k���ҳ����а����� 1 �� n �����֣���ǡ��ӵ�� k �� ����� �Ĳ�ͬ������ĸ���
���ڴ𰸿��ܴܺ�ֻ��Ҫ���ض� 10^9 + 7 ȡ��Ľ��

ʾ�� 1��
���룺n = 3, k = 0
�����1
���ͣ�
ֻ������ [1,2,3] �����˴�1��3��������������ӵ�� 0 �������

ʾ�� 2��
���룺n = 3, k = 1
�����2
���ͣ�
���� [1,3,2] �� [2,1,3] ���� 1 �������

��ʾ��
1 <= n <= 1000
0 <= k <= 1000

*/


// ���仯���ݣ�TLE
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


// ���仰�����Ż�
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


// �Ե׶��ϵĶ�̬�滮
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


// ʱ�临�Ӷ��Ż�
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


// �ռ临�Ӷ��Ż�
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


