#include "header.h"

/*

400. �� N λ����

����һ������ n �����������޵��������� [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...] ���ҳ������ص� n λ�ϵ�����

ʾ�� 1��
���룺n = 3
�����3

ʾ�� 2��
���룺n = 11
�����0
���ͣ��� 11 λ���������� 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... ���� 0 ������ 10 ��һ����

��ʾ��
1 <= n <= 2^31 - 1

*/

class Solution {
public:
	int findNthDigit(int n) {
		int lo = 1, hi = 9;
		while (lo < hi) {
			int mi = lo + (hi - lo) / 2;
			totalDigits(mi) < n ? lo = mi + 1 : hi = mi;
		}
		int d = lo;
		int preDigits = totalDigits(d - 1);
		int index = n - preDigits - 1;
		int start = pow(10, d - 1);
		int num = start + index / d;
		int digitIdx = index % d;
		int digit = (int)(num / pow(10, d - digitIdx - 1)) % 10;
		return digit;
	}
	int totalDigits(int length) {
		int digits = 0;
		int curLen = 1, cnt = 9;
		while (curLen <= length) {
			digits += curLen * cnt;
			++curLen;
			cnt *= 10;
		}
		return digits;
	}
};

