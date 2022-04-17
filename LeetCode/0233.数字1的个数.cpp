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

// TODO ��λDP