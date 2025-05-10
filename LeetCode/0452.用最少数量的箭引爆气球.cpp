#include "header.h"

/*

452. �����������ļ���������

��һЩ������������һ���� XY ƽ���ʾ��ǽ����
ǽ���ϵ������¼���������� points ������points[i] = [xstart, xend] ��ʾˮƽֱ���� xstart �� xend֮�������
�㲻֪�������ȷ�� y ����

һ֧������������ x ��Ӳ�ͬ�� ��ȫ��ֱ ������������� x �����һ֧��������һ�������ֱ���Ŀ�ʼ�ͽ�������Ϊ xstart��xend��
������  xstart �� x �� xend���������ᱻ ����
��������Ĺ��������� û�����ƣ�����һ�������֮�󣬿������޵�ǰ��

����һ������ points ����������������������������� ��С ������

ʾ�� 1��
���룺points = [[10,16],[2,8],[1,6],[7,12]]
�����2
���ͣ����������2֧��������:
��x = 6�����������������[2,8]��[1,6]
��x = 11�����������������[10,16]��[7,12]

ʾ�� 2��
���룺points = [[1,2],[3,4],[5,6],[7,8]]
�����4
���ͣ�ÿ��������Ҫ���һ֧�����ܹ���Ҫ4֧��

ʾ�� 3��
���룺points = [[1,2],[2,3],[3,4],[4,5]]
�����2
���ͣ����������2֧��������:
��x = 2�����������������[1,2]��[2,3]
��x = 4�����������������[3,4]��[4,5]

��ʾ:
1 <= points.length <= 10^5
points[i].length == 2
-2^31 <= xstart < xend <= 2^31 - 1

*/

class Solution {
public:
	int findMinArrowShots(vector<vector<int>> &points) {
		if (points.empty()) return 0;
		sort(points.begin(), points.end(),
			[](const vector<int> &a, const vector<int> &b) {
			return a[1] < b[1];
		});
		int pos = points[0][1];
		int ans = 1;
		for (const vector<int> &balloon : points) {
			if (balloon[0] > pos) {
				pos = balloon[1];
				++ans;
			}
		}
		return ans;
	}
};

