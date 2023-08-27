#include "header.h"

/*

391. ��������

����һ������ rectangles, ���� rectangles[i] = [xi, yi, ai, bi] ��ʾһ��������ƽ�еľ���
������ε����¶����� (xi, yi), ���϶����� (ai, bi)
������о���һ��ȷ������ĳ����������, �򷵻� true; ���򷵻� false

ʾ�� 1��
���룺rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]
�����true
���ͣ�5 ������һ����Ծ�ȷ�ظ���һ����������

ʾ�� 2��
���룺rectangles = [[1,1,2,3],[1,3,2,4],[3,1,4,2],[3,2,4,4]]
�����false
���ͣ���������֮���м�����޷����ǳ�һ�����Ρ�

ʾ�� 3��
���룺rectangles = [[1,1,3,3],[3,1,4,2],[1,3,2,4],[2,2,4,4]]
�����false
���ͣ���Ϊ�м����ཻ������Ȼ�γ��˾��Σ������Ǿ�ȷ���ǡ�

��ʾ��
1 <= rectangles.length <= 2 * 10^4
rectangles[i].length == 4
-10^5 <= xi, yi, ai, bi <= 10^5

*/

class Solution {
public:
	bool isRectangleCover(vector<vector<int>>& rectangles) {
		long long sum = 0;
		int x1 = INT_MAX, y1 = INT_MAX;
		int x2 = INT_MIN, y2 = INT_MIN;
		set<pair<int, int>> s;
		for (const auto &v : rectangles) {
			x1 = min(x1, v[0]), y1 = min(y1, v[1]);
			x2 = max(x2, v[2]), y2 = max(y2, v[3]);
			sum += (long long)(v[2] - v[0])*(v[3] - v[1]);
			pair<int, int> ll{ v[0],v[1] };
			pair<int, int> lh{ v[0],v[3] };
			pair<int, int> rl{ v[2],v[1] };
			pair<int, int> rh{ v[2],v[3] };

			if (s.count(ll)) s.erase(ll);
			else s.insert(ll);
			if (s.count(lh)) s.erase(lh);
			else s.insert(lh);
			if (s.count(rl)) s.erase(rl);
			else s.insert(rl);
			if (s.count(rh)) s.erase(rh);
			else s.insert(rh);
		}
		if (s.size() == 4 && s.count({ x1, y1 }) && s.count({ x1, y2 }) &&
			s.count({ x2, y1 }) && s.count({ x2, y2 })) {
			return sum == (long long)(y2 - y1) * (x2 - x1);
		}
		return false;
	}
};

// https://leetcode.cn/problems/perfect-rectangle/solutions/1104155/c-zui-tong-su-yi-dong-si-lu-by-heroding-npgj/
// @author https://leetcode.cn/u/heroding/
