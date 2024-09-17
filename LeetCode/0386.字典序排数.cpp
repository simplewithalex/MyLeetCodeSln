#include "header.h"

/*

386. �ֵ�������

����һ������ n �����ֵ��򷵻ط�Χ [1, n] ����������
��������һ��ʱ�临�Ӷ�Ϊ O(n) ��ʹ�� O(1) ����ռ���㷨

ʾ�� 1��
���룺n = 13
�����[1,10,11,12,13,2,3,4,5,6,7,8,9]

ʾ�� 2��
���룺n = 2
�����[1,2]

��ʾ��
1 <= n <= 5 * 10^4

*/


class Solution1 {
private:
	vector<int> ans;

public:
	vector<int> lexicalOrder(int n) {
		for (int i = 1; i <= 9; ++i) {
			if (i <= n) dfs(i, n);
		}
		return ans;
	}

private:
	void dfs(int cur, int limit) {
		ans.push_back(cur);
		for (int i = 0; i <= 9; ++i) {
			if ((cur * 10 + i) > limit) break;
			dfs(cur * 10 + i, limit);
		}
	}
};


class Solution2 {
public:
	vector<int> lexicalOrder(int n) {
		vector<int> ans;
		for (int i = 0, j = 1; i < n; ++i) {
			ans.push_back(j);
			if (j * 10 <= n) {
				j *= 10;
			} else {
				while (j % 10 == 9 || j + 1 > n) j /= 10;
				++j;
			}
		}
		return ans;
	}
};

