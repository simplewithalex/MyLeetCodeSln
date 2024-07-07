#include "header.h"

/*

546. �Ƴ�����

����һЩ��ͬ��ɫ�ĺ��� boxes �����ӵ���ɫ�ɲ�ͬ��������ʾ

�㽫���������ֲ���ȥȥ�����ӣ�ֱ�����еĺ��Ӷ�ȥ��Ϊֹ��ÿһ��������Ƴ�������ͬ��ɫ������ k �����ӣ�k >= 1��������һ��֮���㽫�õ� k * k ������

���� ���ܻ�õ������ֺ�

ʾ�� 1��
���룺boxes = [1,3,2,2,2,3,4,3,1]
�����23
���ͣ�
[1, 3, 2, 2, 2, 3, 4, 3, 1]
----> [1, 3, 3, 4, 3, 1] (3*3=9 ��)
----> [1, 3, 3, 3, 1] (1*1=1 ��)
----> [1, 1] (3*3=9 ��)
----> [] (2*2=4 ��)

ʾ�� 2��
���룺boxes = [1,1,1]
�����9

ʾ�� 3��
���룺boxes = [1]
�����1

��ʾ��
1 <= boxes.length <= 100
1 <= boxes[i] <= 100

*/

class Solution {
private:
	vector<vector<vector<int>>> memo;

public:
	int removeBoxes(vector<int> &boxes) {
		int len = boxes.size();
		memo.resize(len, vector<vector<int>>(len, vector<int>(len, -1)));
		return helper(boxes, 0, len - 1, 0);
	}

private:
	int helper(vector<int> &boxes, int l, int r, int k) {
		if (l > r) return 0;
		if (memo[l][r][k] != -1) return memo[l][r][k];
		int res = 0;
		int r1 = r, k1 = k;
		while (r1 > l && boxes[r1] == boxes[r1 - 1]) {
			--r1;
			++k1;
		}
		res = helper(boxes, l, r1 - 1, 0) + (k1 + 1) * (k1 + 1);
		for (int i = l; i < r1; ++i) {
			if (boxes[i] == boxes[r1]) {
				res = max(res, helper(boxes, l, i, k1 + 1) +
					helper(boxes, i + 1, r1 - 1, 0));
			}
		}
		return memo[l][r][k] = res;
	}
};


