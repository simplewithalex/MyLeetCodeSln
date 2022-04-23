#include "header.h"

/*

233. ���� 1 �ĸ���

����һ������ n����������С�ڵ��� n �ķǸ����������� 1 ���ֵĸ�����

ʾ�� 1��
���룺n = 13
�����6

ʾ�� 2��
���룺n = 0
�����0

��ʾ��0 <= n <= 10^9

*/

// �Ҽ�������
class Solution1 {
public:
	int countDigitOne(int n)
	{
		if (n <= 0) return 0;
		int res = 0;
		for (long long digit = 1; digit <= n; digit *= 10) {
			int a = n / digit, b = n % digit;
			res += (a + 8) / 10 * digit + (a % 10 == 1) * (b + 1);
		}
		return res;
	}
};
/**
 * https://leetcode-cn.com/problems/number-of-digit-one/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-50/
 * @author https://leetcode-cn.com/u/windliang/
*/

// ��λDP
class Solution2 {
public:
	int countDigitOne(int n) {
		string s = to_string(n);
		int len = s.size();
		if (len == 1) return n == 0 ? 0 : 1;

		vector<int> dp1(len - 1);
		vector<int> dp2(len);
		// ��������1�ĸ���
		dp1[0] = 1;
		for (int i = 1; i < len - 1; ++i) {
			dp1[i] = 10 * dp1[i - 1] + pow(10, i);
		}

		if (s[len - 1] == '0') dp2[0] = 0;
		else dp2[0] = 1;

		/*
		 * ��165Ϊ���ӣ���������������
		 *��1����λ��1����λ��1���ܸ�����{1}00 - {1}65
		 *��2����λ��1������λ��1���ܸ�����1{00} - 1{65}
		 *��3����λ��0������λ��1���ܸ�����0 - 99
		 */
		for (int i = 1; i < len; ++i) {
			char c = s[len - 1 - i];
			if (c == '0') dp2[i] = dp2[i - 1];
			else if (c == '1') dp2[i] = (stoi(s.substr(len - i)) + 1) + dp2[i - 1] + dp1[i - 1];
			else dp2[i] = pow(10, i) + dp2[i - 1] + (c - '0')*dp1[i - 1];
		}
		return dp2[len - 1];
	}
};
