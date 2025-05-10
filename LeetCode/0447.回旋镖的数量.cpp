#include "header.h"

/*

447. �����ڵ�����

����ƽ���� n �� ������ͬ �ĵ� points ������ points[i] = [xi, yi]
������ ���ɵ� (i, j, k) ��ʾ��Ԫ�� ������ i �� j ֮���ŷʽ����� i �� k ֮���ŷʽ������ȣ���Ҫ����Ԫ���˳��
����ƽ�������л����ڵ�����

ʾ�� 1��
���룺points = [[0,0],[1,0],[2,0]]
�����2
���ͣ�����������Ϊ [[1,0],[0,0],[2,0]] �� [[1,0],[2,0],[0,0]]

ʾ�� 2��
���룺points = [[1,1],[2,2],[3,3]]
�����2

ʾ�� 3��
���룺points = [[1,1]]
�����0

��ʾ��
n == points.length
1 <= n <= 500
points[i].length == 2
-10^4 <= xi, yi <= 10^4
���е㶼 ������ͬ

*/

class Solution {
public:
	int numberOfBoomerangs(vector<vector<int>> &points) {
		int ans = 0;
		unordered_map<int, int> cnt;
		for (const auto &p1 : points) {
			cnt.clear();
			for (const auto &p2 : points) {
				int d = (p1[0] - p2[0]) * (p1[0] - p2[0]) +
					(p1[1] - p2[1]) * (p1[1] - p2[1]);
				ans += cnt[d] * 2;
				++cnt[d];
			}
		}
		return ans;
	}
};

