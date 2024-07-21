#include "header.h"

/*

552. ѧ�����ڼ�¼ II

�������ַ�����ʾһ��ѧ���ĳ��ڼ�¼�����е�ÿ���ַ�������ǵ���ĳ��������ȱ�ڡ��ٵ�������������¼��ֻ�����������ַ���
'A'��Absent��ȱ��
'L'��Late���ٵ�
'P'��Present������
���ѧ���ܹ� ͬʱ ����������������������Ի�ó��ڽ�����

�� �ܳ��� �ƣ�ѧ��ȱ�ڣ�'A'���ϸ� ��������
ѧ�� ���� ���� ���� 3 ��� ���� 3 �����ϵĳٵ���'L'����¼

����һ������ n ����ʾ���ڼ�¼�ĳ��ȣ������������㷵�ؼ�¼����Ϊ n ʱ�����ܻ�ó��ڽ����ļ�¼��� ����
�𰸿��ܴܺ����Է��ض� 10^9 + 7 ȡ�� �Ľ��


ʾ�� 1��
���룺n = 2
�����8
���ͣ�
�� 8 �ֳ���Ϊ 2 �ļ�¼������Ϊ�ɽ�����
"PP" , "AP", "PA", "LP", "PL", "AL", "LA", "LL"
ֻ��"AA"���ᱻ��Ϊ�ɽ�������Ϊȱ�ڴ���Ϊ 2 �Σ���Ҫ���� 2 �Σ�

ʾ�� 2��
���룺n = 1
�����3

ʾ�� 3��
���룺n = 10101
�����183236316

��ʾ��
1 <= n <= 10^5

*/


// ���仯����
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
	// ���� n �죬��ǰ�Ѿ���¼Ϊ 'A' �������������� 'L' ������
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

// ����ȫ�ּ��仯
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


// ��̬�滮
// ֱ��ʹ�� Solution2 �еĶ���
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

