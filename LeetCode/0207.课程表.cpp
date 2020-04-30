#include "header.h"

/*

现在你总共有 n 门课需要选，记为 0 到 n-1。

在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们: [0,1]

给定课程总量以及它们的先决条件，判断是否可能完成所有课程的学习？

示例 1:

输入: 2, [[1,0]]
输出: true
解释: 总共有 2 门课程。学习课程 1 之前，你需要完成课程 0。所以这是可能的。

示例 2:

输入: 2, [[1,0],[0,1]]
输出: false
解释: 总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0；并且学习课程 0 之前，你还应先完成课程 1。这是不可能的。

说明:

输入的先决条件是由边缘列表表示的图形。
你可以假定输入的先决条件中没有重复的边。

提示:

这个问题相当于查找一个循环是否存在于有向图中。如果存在循环，则不存在拓扑排序，因此不可能选取所有课程进行学习。
通过 DFS 进行拓扑排序，拓扑排序也可以通过 BFS 完成。

*/


//图的问题可以通过构建邻接表来完成
//BFS方法
class Solution1 {
public:
	bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
	{
		//构建邻接表
		vector<vector<int>> adj(numCourses);
		//统计入度
		vector<int> indegrees(numCourses);
		for (auto node : prerequisites)
		{
			adj[node[1]].push_back(node[0]);
			++indegrees[node[0]];
		}
		queue<int> q;
		for (int i = 0; i < numCourses; ++i) if (indegrees[i] == 0) q.push(i);
		while (!q.empty())
		{
			int temp = q.front();
			q.pop();
			--numCourses;
			for (auto next : adj[temp]) if (--indegrees[next] == 0) q.push(next);
		}
		return numCourses == 0;
	}
};

//DFS方法
class Solution2 {
public:
	bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
	{
		vector<vector<int>> adj(numCourses);
		vector<int> flags(numCourses);
		for (auto node : prerequisites) adj[node[1]].push_back(node[0]);
		for (int i = 0; i < numCourses; ++i)
		{
			if (!dfs(adj, flags, i)) return false;
		}
		return true;
	}
	bool dfs(vector<vector<int>> &adj, vector<int> &flags, int i)
	{
		if (flags[i] == 1) return false;
		if (flags[i] == -1) return true;
		flags[i] = 1;
		for (auto v : adj[i])
		{
			if (!dfs(adj, flags, v)) return false;
		}
		flags[i] = -1;
		return true;
	}
};
//https://leetcode-cn.com/problems/course-schedule/solution/course-schedule-tuo-bu-pai-xu-bfsdfsliang-chong-fa/
