#include "header.h"

/*

552. 学生出勤记录 II

可以用字符串表示一个学生的出勤记录，其中的每个字符用来标记当天的出勤情况（缺勤、迟到、到场）。记录中只含下面三种字符：
'A'：Absent，缺勤
'L'：Late，迟到
'P'：Present，到场
如果学生能够 同时 满足下面两个条件，则可以获得出勤奖励：

按 总出勤 计，学生缺勤（'A'）严格 少于两天
学生 不会 存在 连续 3 天或 连续 3 天以上的迟到（'L'）记录

给你一个整数 n ，表示出勤记录的长度（次数）。请你返回记录长度为 n 时，可能获得出勤奖励的记录情况 数量
答案可能很大，所以返回对 10^9 + 7 取余 的结果


示例 1：
输入：n = 2
输出：8
解释：
有 8 种长度为 2 的记录将被视为可奖励：
"PP" , "AP", "PA", "LP", "PL", "AL", "LA", "LL"
只有"AA"不会被视为可奖励，因为缺勤次数为 2 次（需要少于 2 次）

示例 2：
输入：n = 1
输出：3

示例 3：
输入：n = 10101
输出：183236316

提示：
1 <= n <= 10^5

*/


// 记忆化搜索
class Solution1 {
private:
	int mod = 1E9 + 7;
	vector<vector<vector<int>>> memo;

public:
	int checkRecord(int n) {
		memo.resize(n + 1, vector<vector<int>>(2, vector<int>(3, -1)));
		return helper(n, 0, 0);
	}

private:
	// 还有 n 天，当前已经记录为 'A' 的数量，和连续 'L' 的数量
	int helper(int n, int acnt, int lcnt) {
		if (acnt == 2) return 0;
		if (lcnt == 3) return 0;
		if (n == 0) return 1;
		if (memo[n][acnt][lcnt] != -1) return memo[n][acnt][lcnt];
		int ans = 0;
		ans = helper(n - 1, acnt + 1, 0) % mod;
		ans = (ans + helper(n - 1, acnt, lcnt + 1)) % mod;
		ans = (ans + helper(n - 1, acnt, 0)) % mod;
		return memo[n][acnt][lcnt] = ans;
	}
};

// 可以全局记忆化
const int N = 10E5 + 1;
static int memo[N][2][3] = {};
static int mod = 1E9 + 7;

class Solution2 {
public:
	int checkRecord(int n) { return helper(n, 0, 0); }

private:
	int helper(int n, int acnt, int lcnt) {
		if (acnt == 2) return 0;
		if (lcnt == 3) return 0;
		if (n == 0) return 1;
		if (memo[n][acnt][lcnt] != 0) return memo[n][acnt][lcnt];
		int ans = 0;
		ans = helper(n - 1, acnt + 1, 0) % mod;
		ans = (ans + helper(n - 1, acnt, lcnt + 1)) % mod;
		ans = (ans + helper(n - 1, acnt, 0)) % mod;
		return memo[n][acnt][lcnt] = ans;
	}
};


// 动态规划
// 直接使用 Solution2 中的定义
// const int N = 10E5 + 1;
// static int mod = 1E9 + 7;

class Solution3 {
public:
	int checkRecord(int n) {
		int dp[N][2][3] = {};
		for (int j = 0; j < 2; ++j) {
			for (int k = 0; k < 3; ++k) dp[0][j][k] = 1;
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < 2; ++j) {
				for (int k = 0; k < 3; ++k) {
					int ans = 0;
					ans = (ans + (j == 0 ? dp[i - 1][j + 1][0] : 0)) % mod;
					ans = (ans + (k < 2 ? dp[i - 1][j][k + 1] : 0)) % mod;
					ans = (ans + dp[i - 1][j][0]) % mod;
					dp[i][j][k] = ans;
				}
			}
		}
		return dp[n][0][0];
	}
};

// https://leetcode.cn/problems/student-attendance-record-ii/solutions/943007/gong-shui-san-xie-yi-ti-san-jie-ji-yi-hu-fdfx/
// @author https://leetcode.cn/u/ac_oier/

