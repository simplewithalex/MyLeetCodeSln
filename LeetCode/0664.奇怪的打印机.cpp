#include "header.h"

/*

664. ��ֵĴ�ӡ��

��̨��ֵĴ�ӡ����������������Ҫ��
��ӡ��ÿ��ֻ�ܴ�ӡ�� ͬһ���ַ� ��ɵ�����
ÿ�ο����ڴ���ʼ������������λ�ô�ӡ���ַ������һḲ�ǵ�ԭ�����е��ַ�

����һ���ַ��� s ����������Ǽ��������ӡ����ӡ����Ҫ�����ٴ�ӡ����

ʾ�� 1��
���룺s = "aaabbb"
�����2
���ͣ����ȴ�ӡ "aaa" Ȼ���ӡ "bbb"

ʾ�� 2��
���룺s = "aba"
�����2
���ͣ����ȴ�ӡ "aaa" Ȼ���ڵڶ���λ�ô�ӡ "b" ���ǵ�ԭ�����ַ� 'a'

��ʾ��
1 <= s.length <= 100
s ��СдӢ����ĸ���

*/


// ���仯����
class Solution1 {
public:
	vector<vector<int>> memo;
	int strangePrinter(string s) {
		int len = s.size();
		memo.resize(len, vector<int>(len));
		return helper(s, 0, len - 1);
	}
	int helper(const string &s, int i, int j) {
		if (i == j) return 1;
		if (memo[i][j]) return memo[i][j];
		int res = INT_MAX;
		if (s[i] == s[j]) {
			res = helper(s, i, j - 1);
		} else {
			for (int k = i; k < j; ++k) {
				res = min(res, helper(s, i, k) + helper(s, k + 1, j));
			}
		}
		return memo[i][j] = res;
	}
};


// �Ե����϶�̬�滮
class Solution2 {
public:
	int strangePrinter(string s) {
		int len = s.size();
		vector<vector<int>> dp(len, vector<int>(len, INT_MAX));
		for (int i = len - 1; i >= 0; --i) {
			dp[i][i] = 1;
			for (int j = i + 1; j < len; ++j) {
				if (s[i] == s[j]) {
					dp[i][j] = dp[i][j - 1];
				} else {
					for (int k = i; k < j; ++k) {
						dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
					}
				}
			}
		}
		return dp[0][len - 1];
	}
};

