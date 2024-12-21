#include "header.h"

/*

765. 情侣牵手

n 对情侣坐在连续排列的 2n 个座位上，想要牵到对方的手

人和座位由一个整数数组 row 表示，其中 row[i] 是坐在第 i 个座位上的人的 ID

情侣们按顺序编号，第一对是 (0, 1)，第二对是 (2, 3)，以此类推，最后一对是 (2n-2, 2n-1)

返回 最少交换座位的次数，以便每对情侣可以并肩坐在一起。 每次交换可选择任意两人，让他们站起来交换座位


示例 1:
输入: row = [0,2,1,3]
输出: 1
解释: 只需要交换row[1]和row[2]的位置即可

示例 2:
输入: row = [3,2,0,1]
输出: 0
解释: 无需交换座位，所有的情侣都已经可以手牵手了

提示:
2n == row.length
2 <= n <= 30
n 是偶数
0 <= row[i] < 2n
row 中所有元素均无重复

*/


// DFS
class Solution1 {
public:
	int ans = 0;
	vector<int> visited;
	int minSwapsCouples(vector<int> &row) {
		int len = row.size();
		visited.resize(len / 2, 0);
		vector<vector<int>> adj(len / 2);
		for (int i = 0; i < len; i += 2) {
			int x = row[i] / 2;
			int y = row[i + 1] / 2;
			if (x != y) {
				adj[x].push_back(y);
				adj[y].push_back(x);
			}
		}
		for (int i = 0; i < len / 2; ++i) {
			if (!visited[i] && !adj[i].empty()) dfs(adj, i);
		}
		return ans;
	}
	void dfs(vector<vector<int>> &adj, int idx) {
		visited[idx] = 1;
		for (int p : adj[idx]) {
			if (!visited[p]) {
				++ans;
				dfs(adj, p);
			}
		}
	}
};

// 并查集
class UF {
public:
	vector<int> id;
	int count = 0;
	UF(int len) {
		count = len;
		for (int i = 0; i < len; ++i) id.push_back(i);
	}
	int find(int x) {
		if (id[x] != x) id[x] = find(id[x]);
		return id[x];
	}
	void unionpq(int p, int q) {
		int pRoot = find(p);
		int qRoot = find(q);
		if (pRoot == qRoot) return;
		id[pRoot] = qRoot;
		--count;
	}
};
class Solution2 {
public:
	int minSwapsCouples(vector<int> &row) {
		int len = row.size();
		UF uf(len / 2);
		for (int i = 0; i < len; i += 2) {
			uf.unionpq(row[i] / 2, row[i + 1] / 2);
		}
		return len / 2 - uf.count;
	}
};

