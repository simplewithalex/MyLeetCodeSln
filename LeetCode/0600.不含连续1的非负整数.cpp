#include "header.h"

/*

600. ��������1�ķǸ�����

����һ�������� n ������ͳ���� [0, n] ��Χ�ķǸ������У��ж��ٸ������Ķ����Ʊ�ʾ�в����� ������ 1

ʾ�� 1:
����: n = 5
���: 5
����: 
�����г���Χ�� [0, 5] �ķǸ����������Ӧ�Ķ����Ʊ�ʾ��
0 : 0
1 : 1
2 : 10
3 : 11
4 : 100
5 : 101
���У�ֻ������ 3 Υ������������������ 1�������� 5 ���������

ʾ�� 2:
����: n = 1
���: 2

ʾ�� 3:
����: n = 2
���: 3

��ʾ:
1 <= n <= 10^9

*/


class Solution {
private:
	int len = 0;
	int num = 0;
	vector<vector<int>> memo;

public:
	int findIntegers(int n) {
		len = log2(n);
		num = n;
		memo.resize(len + 1, vector<int>(2));
		return helper(0, 0, true);
	}

private:
	int helper(int i, int pre, bool isLimit) {
		if (i == len + 1) return 1;
		if (!isLimit && memo[i][pre]) return memo[i][pre];
		int up = isLimit ? (num >> (len - i)) & 1 : 1;
		int res = 0;
		for (int cur = 0; cur <= up; ++cur) {
			if (!(pre == 1 && cur == 1)) {
				res += helper(i + 1, cur, isLimit && cur == up);
			}
		}
		return isLimit ? res : memo[i][pre] = res;
		return res;
	}
};
// https://leetcode.cn/problems/numbers-at-most-n-given-digit-set/solutions/1900038/by-lfool-epqy/
// @author https://leetcode.cn/u/lfool/

// �÷�����״̬���岻�ʺϴ����Ч״̬̫�࣬�˷ѿռ�
