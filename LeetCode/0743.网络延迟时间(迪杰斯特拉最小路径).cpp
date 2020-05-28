#include "header.h"

/*

有 N 个网络节点，标记为 1 到 N。
给定一个列表 times，表示信号经过有向边的传递时间。 times[i] = (u, v, w)，其中 u 是源节点，v 是目标节点， w 是一个信号从源节点传递到目标节点的时间。
现在，我们向当前的节点 K 发送了一个信号。需要多久才能使所有节点都收到信号？如果不能使所有节点收到信号，返回 -1。

注意:

1、N 的范围在 [1, 100] 之间。
2、K 的范围在 [1, N] 之间。
3、times 的长度在 [1, 6000] 之间。
4、所有的边 times[i] = (u, v, w) 都有 1 <= u, v <= N 且 0 <= w <= 100。

示例：
Input: times = [[2,1,1],[2,3,1],[3,4,1]], N = 4, K = 2
Output: 2

*/

//典型的最小路径算法
class Solution {
public:
	int networkDelayTime(vector<vector<int>> &times, int N, int K)
	{
		vector<vector<pair<int, int>>> graph(N + 1);
		for (auto edge : times) graph[edge[0]].push_back({ edge[1], edge[2] });
		priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)*> pq(compare);
		pq.push({ 0, K });
		unordered_map<int, int> dist;
		while (!pq.empty())
		{
			auto info = pq.top();
			pq.pop();
			int d = info.first;
			int node = info.second;
			if (dist.count(node)) continue;
			dist[node] = d;
			for (auto edge : graph[node])
			{
				int neigh = edge.first, d2 = edge.second;
				if (!dist.count(neigh))
				{
					pq.push({ d + d2, neigh });
				}
			}
		}
		if (dist.size() != N) return -1;
		int res = 0;
		for (auto it : dist)
			res = max(res, it.second);
		return res;
	}
	static bool compare(const pair<int, int> &p1, const pair<int, int> &p2)
	{
		return p1.first > p2.first;
	}
};