#include "header.h"

/*

407. 接雨水 II

给你一个 m x n 的矩阵，其中的值均为非负整数，代表二维高度图每个单元的高度，请计算图中形状最多能接多少体积的雨水

示例 1:
输入: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
输出: 4
解释: 下雨后，雨水将会被上图蓝色的方块中。总的接雨水量为1+2+1=4

示例 2:
输入: heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
输出: 10

提示:
m == heightMap.length
n == heightMap[i].length
1 <= m, n <= 200
0 <= heightMap[i][j] <= 2 * 10^4

*/

class Solution {
public:
	int trapRainWater(vector<vector<int>> &heightMap) {
		int rows = heightMap.size(), cols = heightMap[0].size();
		priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
		vector<vector<char>> visited(rows, vector<char>(cols, false));
		for (int i = 0; i < cols; ++i) {
			pq.push({ heightMap[0][i], 0, i });
			pq.push({ heightMap[rows - 1][i], rows - 1, i });
			visited[0][i] = visited[rows - 1][i] = true;
		}
		for (int i = 1; i < rows - 1; ++i) {
			pq.push({ heightMap[i][0], i, 0 });
			pq.push({ heightMap[i][cols - 1], i, cols - 1 });
			visited[i][0] = visited[i][cols - 1] = true;
		}

		vector<vector<int>> dirs{ { 1, 0 },{ -1, 0 },{ 0, 1 },{ 0, -1 } };
		int ans = 0;
		while (!pq.empty()) {
			vector<int> tmp = pq.top();
			pq.pop();
			int h = tmp[0], x = tmp[1], y = tmp[2];
			for (auto dir : dirs) {
				int nx = x + dir[0], ny = y + dir[1];
				if (nx < 0 || nx >= rows || ny < 0 || ny >= cols) continue;
				if (visited[nx][ny]) continue;
				if (h > heightMap[nx][ny]) ans += h - heightMap[nx][ny];
				pq.push({ max(heightMap[nx][ny], h), nx, ny });
				visited[nx][ny] = true;
			}
		}
		return ans;
	}
};

// https://leetcode.cn/problems/trapping-rain-water-ii/solutions/1081138/gong-shui-san-xie-jing-dian-dijkstra-yun-13ik/
// @author https://leetcode.cn/u/ac_oier/
