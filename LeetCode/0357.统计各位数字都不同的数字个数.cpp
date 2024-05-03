#include "header.h"

/*

357. ͳ�Ƹ�λ���ֶ���ͬ�����ָ���

����һ������ n ��ͳ�Ʋ����ظ�λ���ֶ���ͬ������ x �ĸ��������� 0 <= x < 10^n

ʾ�� 1��
���룺n = 2
�����91
���ͣ���ӦΪ��ȥ 11��22��33��44��55��66��77��88��99 �⣬�� 0 �� x < 100 ��Χ�ڵ��������֡�

ʾ�� 2��
���룺n = 0
�����1

��ʾ��
0 <= n <= 8

*/

class Solution {
public:
	int countNumbersWithUniqueDigits(int n) {
		if (n == 0) return 1;
		vector<int> dp(n + 1);
		dp[0] = 1, dp[1] = 10;
		for (int i = 2; i <= n; ++i) {
			dp[i] = dp[i - 1] + (dp[i - 1] - dp[i - 2]) * (10 - (i - 1));
		}
		return dp[n];
	}
};


