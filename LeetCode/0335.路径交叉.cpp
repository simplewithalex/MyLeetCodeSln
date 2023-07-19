#include "header.h"

/*

335. ·������

����һ���������� distance

�� X-Y ƽ���ϵĵ� (0,0) ��ʼ�������ƶ� distance[0] �ף�Ȼ�������ƶ� distance[1] �ף������ƶ� distance[2] �ף����ƶ� distance[3] �ף������ƶ���

Ҳ����˵��ÿ���ƶ�����ķ�λ�ᷢ����ʱ��仯��

�ж�����������·���Ƿ��ཻ������ཻ������ true �����򣬷��� false ��


ʾ�� 1��
���룺distance = [2,1,1,2]
�����true

ʾ�� 2��
���룺distance = [1,2,3,4]
�����false

ʾ�� 3��
���룺distance = [1,1,1,1]
�����true

��ʾ��
1 <= distance.length <= 10^5
1 <= distance[i] <= 10^5

*/

class Solution {
public:
	bool isSelfCrossing(vector<int> &dis) {
		int len = dis.size();
		if (len < 4) return false;
		for (int i = 3; i < len; ++i) {
			if (dis[i] >= dis[i - 2] && dis[i - 1] <= dis[i - 3]) return true;
			if (i >= 4 && dis[i - 1] == dis[i - 3] &&
				dis[i] + dis[i - 4] >= dis[i - 2]) {
				return true;
			}
			if (i >= 5 && dis[i - 1] <= dis[i - 3] && dis[i - 2] > dis[i - 4] &&
				dis[i] + dis[i - 4] >= dis[i - 2] &&
				dis[i - 1] + dis[i - 5] >= dis[i - 3]) {
				return true;
			}
		}
		return false;
	}
};

// https://leetcode.cn/problems/self-crossing/solutions/1072162/gong-shui-san-xie-fen-qing-kuang-tao-lun-zdrb/
// @author https://leetcode.cn/u/ac_oier/