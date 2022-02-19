#include "header.h"

/*

城市的 天际线 是从远处观看该城市中所有建筑物形成的轮廓的外部轮廓。给你所有建筑物的位置和高度，请返回 由这些建筑物形成的 天际线 。

每个建筑物的几何信息由数组 buildings 表示，其中三元组 buildings[i] = [left(i), right(i), height(i)] 表示：
left(i) 是第 i 座建筑物左边缘的 x 坐标。
right(i) 是第 i 座建筑物右边缘的 x 坐标。
height(i) 是第 i 座建筑物的高度。

你可以假设所有的建筑都是完美的长方形，在高度为 0 的绝对平坦的表面上。

天际线 应该表示为由 “关键点” 组成的列表，格式 [[x1,y1],[x2,y2],...] ，并按 x 坐标进行排序。关键点是水平线段的左端点。列表中最后一个点是最右侧建筑物的终点，y 坐标始终为 0，仅用于标记天际线的终点。

此外，任何两个相邻建筑物之间的地面都应被视为天际线轮廓的一部分。

注意：输出天际线中不得有连续的相同高度的水平线。例如 [...[2 3], [4 5], [7 5], [11 5], [12 7]...] 是不正确的答案；三条高度为 5 的线应该在最终输出中合并为一个：[...[2 3], [4 5], [12 7], ...]


示例 1：
输入：buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
输出：[[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
解释：
图 A 显示输入的所有建筑物的位置和高度，
图 B 显示由这些建筑物形成的天际线。图 B 中的红点表示输出列表中的关键点。

示例 2：
输入：buildings = [[0,2,3],[2,5,3]]
输出：[[0,3],[5,0]]

提示：
1 <= buildings.length <= 10^4
0 <= lefti < righti <= 2^31 - 1
1 <= heighti <= 2^31 - 1
buildings 按 left(i) 非递减排序

*/

// 优先级队列
class Solution1 {
public:
	vector<vector<int>> getSkyline(vector<vector<int>> &buildings) {
		vector<vector<int>> res;
		vector<vector<int>> pointArray;
		for (auto b : buildings) {
			int l = b[0], r = b[1], h = b[2];
			pointArray.push_back({ l, -h });
			pointArray.push_back({ r, h });
		}
		sort(pointArray.begin(), pointArray.end(), [](const vector<int> &a, const vector<int> &b) -> bool {
			if (a[0] != b[0]) return a[0] < b[0];
			else return a[1] < b[1];
		});
		priority_queue<int> pq;
		unordered_map<int, int> m;
		int prev = 0;
		pq.push(prev);
		for (auto p : pointArray) {
			int x = p[0], height = p[1];
			if (height < 0) pq.push(-height);
			else ++m[height];

			while (!pq.empty()) {
				int maxHeight = pq.top();
				if (m.count(maxHeight)) {
					if (m[maxHeight] == 1) m.erase(maxHeight);
					else --m[maxHeight];
					pq.pop();
				}
				else {
					break;
				}
			}

			int cur = pq.top();
			if (cur != prev) {
				res.push_back({ x, cur });
				prev = cur;
			}
		}
		return res;
	}
};
// https://leetcode-cn.com/problems/the-skyline-problem/solution/gong-shui-san-xie-sao-miao-xian-suan-fa-0z6xc/

// 归并思想
class Solution2 {
public:
	vector<vector<int>> getSkyline(vector<vector<int>> &buildings) {
		int len = buildings.size();
		if (len == 0) return{};
		return merge(buildings, 0, len - 1);
	}

private:
	vector<vector<int>> merge(vector<vector<int>> &buildings, int lo, int hi) {
		vector<vector<int>> res;
		if (lo == hi) {
			res.push_back({ buildings[lo][0], buildings[lo][2] });
			res.push_back({ buildings[lo][1], 0 });
			return res;
		}
		int mi = lo + (hi - lo) / 2;
		vector<vector<int>> skyLine1 = merge(buildings, lo, mi);
		vector<vector<int>> skyLine2 = merge(buildings, mi + 1, hi);

		// 合并处理
		int x = 0, h1 = 0, h2 = 0;
		int i = 0, j = 0;
		while (i < skyLine1.size() && j < skyLine2.size()) {
			int x1 = skyLine1[i][0], x2 = skyLine2[j][0];
			if (x1 < x2) {
				h1 = skyLine1[i][1];
				x = x1;
				++i;
			}
			else if (x1 > x2) {
				h2 = skyLine2[j][1];
				x = x2;
				++j;
			}
			else {
				h1 = skyLine1[i][1];
				h2 = skyLine2[j][1];
				x = x1;
				++i, ++j;
			}
			int h = max(h1, h2);
			if (res.empty() || h != res.back()[1]) res.push_back({ x, h });
		}
		while (i < skyLine1.size()) res.push_back(skyLine1[i++]);
		while (j < skyLine2.size()) res.push_back(skyLine2[j++]);
		return res;
	}
};
// https://leetcode-cn.com/problems/the-skyline-problem/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by--45/