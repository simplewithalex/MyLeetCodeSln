#include "header.h"

/*

397. �����滻

����һ�������� n������������²�����
��� n ��ż�������� n / 2�滻 n
��� n ��������������� n + 1 �� n - 1 �滻 n
���� n ��Ϊ 1 ����� ��С�滻����

ʾ�� 1��
���룺n = 8
�����3
���ͣ�8 -> 4 -> 2 -> 1

ʾ�� 2��
���룺n = 7
�����4
���ͣ�7 -> 8 -> 4 -> 2 -> 1
�� 7 -> 6 -> 3 -> 2 -> 1

ʾ�� 3��
���룺n = 4
�����2

��ʾ��
1 <= n <= 2^31 - 1

*/

// ���仯
class Solution1 {
private:
	unordered_map<int, int> memo;

public:
	int integerReplacement(int n) {
		if (n == 1) return 0;
		if (memo.count(n)) return memo[n];
		if (n % 2 == 0) {
			memo[n] = 1 + integerReplacement(n / 2);
		} else {
			memo[n] = 2 + min(integerReplacement(n / 2),
							  integerReplacement(n / 2 + 1));
		}
		return memo[n];
	}
};

// �Ե׶��϶�̬�滮������MLE
class Solution2 {
public:
	int integerReplacement(int n) {
		vector<int> dp(n + 1);
		for (int i = 2; i <= n; ++i) {
			dp[i] = i & 1 ? 2 + min(dp[i / 2], dp[i / 2 + 1]) : 1 + dp[i / 2];
		}
		return dp[n];
	}
};

// �ռ��Ż�
class Solution3 {
public:
	int integerReplacement(int n) {
		int dp0 = 0, dp1 = 1;
		string bits = intToBits(n);
		for (int i = 1; i < bits.length(); ++i) {
			int bit = bits[i] - '0';
			if (bit & 1) {
				dp0 = 2 + min(dp0, dp1);
				dp1 = dp1 + 1;
			} else {
				dp1 = 2 + min(dp0, dp1);
				dp0 = dp0 + 1;
			}
		}
		return dp0;
	}

private:
	string intToBits(int num) {
		string bits;
		for (int i = sizeof(num) * 8 - 1; i >= 0; --i) {
			bits += ((num >> i) & 1) ? '1' : '0';
		}
		int pos = bits.find_first_of("1");
		return bits.substr(pos);
	}
};
// https://leetcode.cn/problems/integer-replacement/solutions/1110394/dong-tai-gui-hua-kong-jian-you-hua-by-sh-pxes/
// @author https://leetcode.cn/u/shi-5c/

