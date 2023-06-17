#include "header.h"

/*

310. 最小高度树

树是一个无向图，其中任何两个顶点只通过一条路径连接。 换句话说，一个任何没有简单环路的连通图都是一棵树
给你一棵包含 n 个节点的树，标记为 0 到 n - 1；给定数字 n 和一个有 n - 1 条无向边的 edges 列表（每一个边都是一对标签），其中 edges[i] = [ai, bi] 表示树中节点 ai 和 bi 之间存在一条无向边
可选择树中任何一个节点作为根。当选择节点 x 作为根节点时，设结果树的高度为 h
在所有可能的树中，具有最小高度的树（即，min(h)）被称为 最小高度树，请你找到所有的 最小高度树 并按 任意顺序 返回它们的根节点标签列表
树的 高度 是指根节点和叶子节点之间最长向下路径上边的数量

示例 1：
输入：n = 4, edges = [[1,0],[1,2],[1,3]]
输出：[1]
解释：如图所示，当根是标签为 1 的节点时，树的高度是 1 ，这是唯一的最小高度树。

示例 2：
输入：n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
输出：[3,4]

提示：
1 <= n <= 2 * 10^4
edges.length == n - 1
0 <= ai, bi < n
ai != bi
所有 (ai, bi) 互不相同
给定的输入 保证 是一棵树，并且 不会有重复的边

*/

// 暴力BFS(超时)
class Solution1 {
public:
	vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges) {
		if (n == 1) return{ 0 };
		// 构建邻接表
		vector<vector<int>> adjList(n);
		for (int i = 0; i < edges.size(); ++i) {
			int v1 = edges[i][0];
			int v2 = edges[i][1];
			adjList[v1].push_back(v2);
			adjList[v2].push_back(v1);
		}

		int minDepth = INT_MAX;
		vector<int> ans;
		for (int i = 0; i < n; ++i) {
			int depth = bfs(adjList, i);
			if (depth > minDepth) continue;
			if (depth == minDepth) {
				ans.push_back(i);
			} else {
				ans.clear();
				ans.push_back(i);
				minDepth = depth;
			}
		}
		return ans;
	}

private:
	// BFS搜索，返回最大深度
	int bfs(const vector<vector<int>> &graph, int start) {
		int size = graph.size();
		if (start >= size) return -1;
		vector<char> visited(size, false);
		queue<int> q;
		q.push(start);
		visited[start] = true;
		int depth = 0;
		while (!q.empty()) {
			int len = q.size();
			++depth;
			while (len--) {
				int cur = q.front();
				q.pop();
				for (int adj : graph[cur]) {
					if (visited[adj]) continue;
					visited[adj] = true;
					q.push(adj);
				}
			}
		}
		return depth;
	}
};


// DFS + 备忘录优化(仍然超时)
class Solution2 {
public:
	vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges) {
		if (n == 1) return{ 0 };
		// 构建邻接表
		vector<vector<int>> adjList(n);
		for (int i = 0; i < edges.size(); ++i) {
			int v1 = edges[i][0];
			int v2 = edges[i][1];
			adjList[v1].push_back(v2);
			adjList[v2].push_back(v1);
		}

		int minDepth = INT_MAX;
		unordered_map<int, int> memo;
		vector<int> ans;
		for (int i = 0; i < n; ++i) {
			int depth = dfs(adjList, i, -1, memo);
			if (depth > minDepth) continue;
			if (depth == minDepth) {
				ans.push_back(i);
			} else {
				ans.clear();
				ans.push_back(i);
				minDepth = depth;
			}
		}
		return ans;
	}

private:
	int dfs(const vector<vector<int>> &graph, int start, int root,
		unordered_map<int, int> &memo) {
		// 备忘录使用unordered_map优化空间占用
		// 题目中n < 2 * 10^4，可以使用特殊数字作key
		int key = start * 1E5 + root;
		if (memo.count(key)) return memo[key];
		int ret = 0;
		for (int adj : graph[start]) {
			if (adj == root) continue;
			ret = max(ret, dfs(graph, adj, start, memo));
		}
		return memo[key] = ret + 1;
	}
};
// https://leetcode.cn/problems/minimum-height-trees/solutions/524029/c-xun-xu-jian-jin-de-si-lu-bfsdfstuo-bu-hmk2y/
// @author https://leetcode.cn/u/xiao-rong-jun/

// BFS拓扑排序
class Solution3 {
public:
	vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges) {
		if (n == 1) return{ 0 };
		// 构建邻接表和出度表
		vector<vector<int>> adjList(n);
		vector<int> degree(n);
		for (int i = 0; i < edges.size(); ++i) {
			int v1 = edges[i][0];
			int v2 = edges[i][1];
			adjList[v1].push_back(v2);
			adjList[v2].push_back(v1);
			++degree[v1];
			++degree[v2];
		}
		return bfs(adjList, degree);
	}

private:
	// BFS搜索，返回最大深度
	vector<int> bfs(const vector<vector<int>> &graph, vector<int> &degree) {
		queue<int> q;
		vector<int> ans;
		for (int i = 0; i < graph.size(); ++i) {
			if (degree[i] == 1) q.push(i);
		}
		while (!q.empty()) {
			ans.clear();
			int len = q.size();
			for (int i = 0; i < len; ++i) {
				int cur = q.front();
				q.pop();
				ans.push_back(cur);
				for (int adj : graph[cur]) {
					--degree[adj];
					if (degree[adj] == 1) q.push(adj);
				}
			}
		}
		return ans;
	}
};
// https://leetcode.cn/problems/minimum-height-trees/solutions/242910/zui-rong-yi-li-jie-de-bfsfen-xi-jian-dan-zhu-shi-x/
// @author https://leetcode.cn/u/xiao-xin-28/

