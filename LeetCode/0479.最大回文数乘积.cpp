#include "header.h"

/*

479. ���������˻�

����һ������ n ������ �ɱ�ʾΪ���� n λ�����˻��� ����������

��Ϊ�𰸿��ܷǳ������Է������� 1337 ȡ��

ʾ�� 1��
���룺n = 2
�����987
���ͣ�99 x 91 = 9009, 9009 % 1337 = 987

ʾ�� 2��
���룺n = 1
�����9

��ʾ:
1 <= n <= 8


*/


class Solution {
public:
	int largestPalindrome(int n) {
		if (n == 1) return 9;
		int maxNum = pow(10, n) - 1;
		for (int i = maxNum; i >= 10; --i) {
			long long num = i;
			int b = i;
			while (b != 0) {
				num = num * 10 + b % 10;
				b /= 10;
			}
			for (long long j = maxNum; j * j >= num; --j) {
				if (num % j == 0) return (int)(num % 1337);
			}
		}
		return -1;
	}
};
// https://leetcode.cn/problems/largest-palindrome-product/solutions/1424568/by-ac_oier-t8j7/comments/1509501
// @author https://leetcode.cn/u/A23187/


