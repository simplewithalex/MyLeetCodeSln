#include "header.h"

/*

374. �����ִ�С

�����������������Ϸ����������Ϸ�Ĺ������£�

�һ�� 1 �� n ���ѡ��һ�����֡������ѡ�������ĸ�����
�����´��ˣ��һ�����㣬��ѡ�������ֱ���²�����ִ��˻���С��

�����ͨ������һ��Ԥ�ȶ���õĽӿ� int guess(int num) ����ȡ�²���������ֵһ�������ֿ��ܵ������
-1����µ����ֱ���ѡ�������ִ� ���� num > pick��
1����µ����ֱ���ѡ��������С ���� num < pick��
0����µ���������ѡ����������ȡ����� num == pick��

������ѡ��������

ʾ�� 1��
���룺n = 10, pick = 6
�����6

ʾ�� 2��
���룺n = 1, pick = 1
�����1

ʾ�� 3��
���룺n = 2, pick = 1
�����1

��ʾ��
1 <= n <= 2^31 - 1
1 <= pick <= n

*/



/**
* Forward declaration of guess API.
* @param  num   your guess
* @return 	     -1 if num is higher than the picked number
*			      1 if num is lower than the picked number
*               otherwise return 0
* int guess(int num);
*/
int guess(int num) { return 1; }

class Solution {
public:
	int guessNumber(int n) {
		int lo = 1, hi = n;
		while (lo < hi) {
			int mi = lo + (hi - lo) / 2;
			guess(mi) <= 0 ? hi = mi : lo = mi + 1;
		}
		return lo;
	}
};

