#include "header.h"

/*

365. ˮ������

������ˮ���������ֱ�Ϊ x �� y ����ˮ�Ĺ�Ӧ�����޵ġ�ȷ���Ƿ��п���ʹ����������׼ȷ�õ� target ��

����ԣ�
װ������һ��ˮ��
�������һ��ˮ��
��ˮ��һ��ˮ��������һ��ˮ����ֱ����ˮ����������ˮ���ѿ�

ʾ�� 1:
����: x = 3,y = 5,target = 4
���: true
���ͣ�
�������²���������Դﵽ�ܹ� 4 ��ˮ��
1. װ�� 5 ����ˮ��(0, 5)��
2. �� 5 ����ˮ������ 3 ����ˮ�������� 2 ��(3, 2)��
3. ���� 3 ����ˮ��(0, 2)��
4. �� 2 ��ˮ�� 5 ����ˮ��ת�Ƶ� 3 ����ˮ��(2, 0)��
5. �ٴμ��� 5 ����ˮ��(2, 5)��
6. �� 5 ����ˮ���� 3 ����ˮ����ˮֱ�� 3 ����ˮ��������5 ����ˮ���������� 4 ��ˮ(3, 4)��
7. ���� 3 ����ˮ�������ڣ�5 ����ˮ���������� 4 ��ˮ(0, 4)��
�ο������������� "Die Hard"

ʾ�� 2:
����: x = 2, y = 6, target = 5
���: false

ʾ�� 3:
����: x = 1, y = 2, target = 3
���: true
���ͣ�ͬʱ��������ˮ������������ˮ����ˮ���������� 3��

��ʾ:
1 <= x, y, target <= 10^3

*/

// DFS
class Solution1 {
private:
	int xcap;
	int ycap;
	int tar;
	unordered_set<string> s;

public:
	bool canMeasureWater(int x, int y, int target) {
		xcap = x;
		ycap = y;
		tar = target;
		return dfs(x, y);
	}

private:
	bool dfs(int remain_x, int remain_y) {
		string remain = to_string(remain_x) + "#" + to_string(remain_y);
		if (s.count(remain)) return false;
		s.insert(remain);
		if (remain_x == tar || remain_y == tar || remain_x + remain_y == tar) return true;
		return dfs(xcap, remain_y) || dfs(remain_x, ycap) ||
			dfs(0, remain_y) || dfs(remain_x, 0) ||
			dfs(remain_x - min(remain_x, ycap - remain_y),
				remain_y + min(remain_x, ycap - remain_y)) ||
			dfs(remain_x + min(remain_y, xcap - remain_x),
				remain_y - min(remain_y, xcap - remain_x));
	}
};

// BFS
class Solution2 {
public:
	bool canMeasureWater(int x, int y, int target) {
		queue<pair<int, int>> q;
		unordered_set<string> s;
		q.push({ x, y });
		while (!q.empty()) {
			pair<int, int> tmp = q.front();
			q.pop();
			string cur = to_string(tmp.first) + "#" + to_string(tmp.second);
			if (s.count(cur)) continue;
			s.insert(cur);
			if (tmp.first == target || tmp.second == target ||
				tmp.first + tmp.second == target) {
				return true;
			}
			q.push({ x, tmp.second });
			q.push({ tmp.first, y });
			q.push({ 0, tmp.second });
			q.push({ tmp.first, 0 });
			q.push({ tmp.first - min(tmp.first, y - tmp.second),
				tmp.second + min(tmp.first, y - tmp.second) });
			q.push({ tmp.first + min(tmp.second, x - tmp.first),
				tmp.second - min(tmp.second, x - tmp.first) });
		}
		return false;
	}
};


