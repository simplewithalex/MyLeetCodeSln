#include "header.h"

/*

483. ��С�ý���

���ַ�������ʽ���� n, ���ַ�������ʽ���� n ����С�ý���

��� n �� k(k>=2) ��������������λȫΪ 1����� k(k>=2) �� n ��һ���ý���

ʾ�� 1��
���룺n = "13"
�����"3"
���ͣ�13 �� 3 ������ 111

ʾ�� 2��
���룺n = "4681"
�����"8"
���ͣ�4681 �� 8 ������ 11111

ʾ�� 3��
���룺n = "1000000000000000000"
�����"999999999999999999"
���ͣ�1000000000000000000 �� 999999999999999999 ������ 11

��ʾ��
n ��ȡֵ��Χ�� [3, 10^18]
n û��ǰ�� 0

*/


typedef unsigned long long ULL;

class Solution {
public:
	string smallestGoodBase(string n) {
		ULL num = stoull(n);
		// ��� 61 �� 1 ������ 3 �� 1 ����������������򷵻� num - 1 ���ƣ����� 11 ��ʾ
		for (int i = 61; i > 2; --i) {
			ULL lo = 2, hi = num - 2;
			while (lo < hi) {
				ULL mi = lo + (hi - lo) / 2;
				cmp(num, i, mi) < 0 ? lo = mi + 1 : hi = mi;
			}
			if (!cmp(num, i, lo)) return to_string(lo);
		}
		return to_string(num - 1);
	}

private:
	char cmp(ULL num, int cnt, ULL base) {
		ULL cur = 0;
		// �ؾ����㷨
		for (size_t i = 0; i < cnt; ++i) {
			// ��ֹԽ��
			if (cur >(num - 1) / base) return 1;
			cur = cur * base + 1;
		}
		if (cur < num) return -1;
		return 0;
	}
};
// ��Ϊ n <= 10^18, ���� n < (1<<62), ��2�������Ҳ���ᳬ��62��1

