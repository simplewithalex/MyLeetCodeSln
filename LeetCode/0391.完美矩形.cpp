#include "header.h"

/*

391. 完美矩形

给你一个数组 rectangles, 其中 rectangles[i] = [xi, yi, ai, bi] 表示一个坐标轴平行的矩形
这个矩形的左下顶点是 (xi, yi), 右上顶点是 (ai, bi)
如果所有矩形一起精确覆盖了某个矩形区域, 则返回 true; 否则返回 false

示例 1：
输入：rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]
输出：true
解释：5 个矩形一起可以精确地覆盖一个矩形区域。

示例 2：
输入：rectangles = [[1,1,2,3],[1,3,2,4],[3,1,4,2],[3,2,4,4]]
输出：false
解释：两个矩形之间有间隔，无法覆盖成一个矩形。

示例 3：
输入：rectangles = [[1,1,3,3],[3,1,4,2],[1,3,2,4],[2,2,4,4]]
输出：false
解释：因为中间有相交区域，虽然形成了矩形，但不是精确覆盖。

提示：
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
