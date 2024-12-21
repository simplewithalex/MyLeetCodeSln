#include "header.h"

/*

765. ����ǣ��

n �����������������е� 2n ����λ�ϣ���Ҫǣ���Է�����

�˺���λ��һ���������� row ��ʾ������ row[i] �����ڵ� i ����λ�ϵ��˵� ID

�����ǰ�˳���ţ���һ���� (0, 1)���ڶ����� (2, 3)���Դ����ƣ����һ���� (2n-2, 2n-1)

���� ���ٽ�����λ�Ĵ������Ա�ÿ�����¿��Բ�������һ�� ÿ�ν�����ѡ���������ˣ�������վ����������λ


ʾ�� 1:
����: row = [0,2,1,3]
���: 1
����: ֻ��Ҫ����row[1]��row[2]��λ�ü���

ʾ�� 2:
����: row = [3,2,0,1]
���: 0
����: ���轻����λ�����е����¶��Ѿ�������ǣ����

��ʾ:
2n == row.length
2 <= n <= 30
n ��ż��
0 <= row[i] < 2n
row ������Ԫ�ؾ����ظ�

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

// ���鼯
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

