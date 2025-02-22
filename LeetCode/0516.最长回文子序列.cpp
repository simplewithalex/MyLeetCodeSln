#include "header.h"

/*

516. �����������

����һ���ַ��� s ���ҳ�������Ļ��������У������ظ����еĳ���

�����ж���Ϊ�����ı�ʣ���ַ�˳�������£�ɾ��ĳЩ�ַ����߲�ɾ���κ��ַ��γɵ�һ������

ʾ�� 1��
���룺s = "bbbab"
�����4
���ͣ�һ�����ܵ������������Ϊ "bbbb"

ʾ�� 2��
���룺s = "cbbd"
�����2
���ͣ�һ�����ܵ������������Ϊ "bb"

��ʾ��
1 <= s.length <= 1000
s ����СдӢ����ĸ���

*/

// ���仯����
class Solution1 {
public:
	vector<vector<int>> memo;
	int longestPalindromeSubseq(string s) {
		int len = s.size();
		memo.resize(len, vector<int>(len, -1));
		return helper(s, 0, len - 1);
	}
	int helper(const string &s, int i, int j) {
		if (i > j) return 0;
		if (i == j) return 1;
		if (memo[i][j] != -1) return memo[i][j];
		int res = 0;
		if (s[i] == s[j]) res = helper(s, i + 1, j - 1) + 2;
		else res = max(helper(s, i + 1, j), helper(s, i, j - 1));
		return memo[i][j] = res;
	}
};

// �Ե׶��ϵĶ�̬�滮
class Solution2 {
public:
	int longestPalindromeSubseq(string s) {
		int len = s.size();
		vector<vector<int>> dp(len, vector<int>(len));
		for (int i = len - 1; i >= 0; --i) {
			dp[i][i] = 1;
			for (int j = i + 1; j < len; ++j) {
				dp[i][j] = s[i] == s[j] ? dp[i + 1][j - 1] + 2
					: max(dp[i + 1][j], dp[i][j - 1]);
			}
		}
		return dp[0][len - 1];
	}
};

// �ռ临�Ӷ��Ż�
class Solution3 {
public:
	int longestPalindromeSubseq(string s) {
		int len = s.size();
		vector<int> dp(len);
		for (int i = len - 1; i >= 0; --i) {
			dp[i] = 1;
			int pre = 0;
			for (int j = i + 1; j < len; ++j) {
				int tmp = dp[j];
				dp[j] = s[i] == s[j] ? pre + 2 : max(dp[j], dp[j - 1]);
				pre = tmp;
			}
		}
		return dp[len - 1];
	}
};


