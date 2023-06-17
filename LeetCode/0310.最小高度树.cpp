#include "header.h"

/*

310. ��С�߶���

����һ������ͼ�������κ���������ֻͨ��һ��·�����ӡ� ���仰˵��һ���κ�û�м򵥻�·����ͨͼ����һ����
����һ�ð��� n ���ڵ���������Ϊ 0 �� n - 1���������� n ��һ���� n - 1 ������ߵ� edges �б�ÿһ���߶���һ�Ա�ǩ�������� edges[i] = [ai, bi] ��ʾ���нڵ� ai �� bi ֮�����һ�������
��ѡ�������κ�һ���ڵ���Ϊ������ѡ��ڵ� x ��Ϊ���ڵ�ʱ���������ĸ߶�Ϊ h
�����п��ܵ����У�������С�߶ȵ���������min(h)������Ϊ ��С�߶����������ҵ����е� ��С�߶��� ���� ����˳�� �������ǵĸ��ڵ��ǩ�б�
���� �߶� ��ָ���ڵ��Ҷ�ӽڵ�֮�������·���ϱߵ�����

ʾ�� 1��
���룺n = 4, edges = [[1,0],[1,2],[1,3]]
�����[1]
���ͣ���ͼ��ʾ�������Ǳ�ǩΪ 1 �Ľڵ�ʱ�����ĸ߶��� 1 ������Ψһ����С�߶�����

ʾ�� 2��
���룺n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
�����[3,4]

��ʾ��
1 <= n <= 2 * 10^4
edges.length == n - 1
0 <= ai, bi < n
ai != bi
���� (ai, bi) ������ͬ
���������� ��֤ ��һ���������� �������ظ��ı�

*/

// ����BFS(��ʱ)
class Solution1 {
public:
	vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges) {
		if (n == 1) return{ 0 };
		// �����ڽӱ�
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
	// BFS����������������
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


// DFS + ����¼�Ż�(��Ȼ��ʱ)
class Solution2 {
public:
	vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges) {
		if (n == 1) return{ 0 };
		// �����ڽӱ�
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
		// ����¼ʹ��unordered_map�Ż��ռ�ռ��
		// ��Ŀ��n < 2 * 10^4������ʹ������������key
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

// BFS��������
class Solution3 {
public:
	vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges) {
		if (n == 1) return{ 0 };
		// �����ڽӱ�ͳ��ȱ�
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
	// BFS����������������
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

