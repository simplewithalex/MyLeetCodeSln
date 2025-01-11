#include "header.h"

/*

433. ��С����仯

�������п��Ա�ʾΪһ���� 8 ���ַ���ɵ��ַ���������ÿ���ַ����� 'A'��'C'��'G' �� 'T' ֮һ

����������Ҫ����ӻ������� start ��Ϊ end �������Ļ���仯��һ�λ���仯����ζ��������������е�һ���ַ������˱仯
���磬"AACCGGTT" --> "AACCGGTA" ����һ�λ���仯

����һ������� bank ��¼��������Ч�Ļ���仯��ֻ�л�����еĻ��������Ч�Ļ������С����仯��Ļ������λ�ڻ���� bank �У�

���������������� start �� end ���Լ�һ������� bank �������ҳ��������ܹ�ʹ start �仯Ϊ end ��������ٱ仯����������޷���ɴ˻���仯������ -1
ע�⣺��ʼ�������� start Ĭ������Ч�ģ�����������һ��������ڻ������

ʾ�� 1��
���룺start = "AACCGGTT", end = "AACCGGTA", bank = ["AACCGGTA"]
�����1

ʾ�� 2��
���룺start = "AACCGGTT", end = "AAACGGTA", bank = ["AACCGGTA","AACCGCTA","AAACGGTA"]
�����2

ʾ�� 3��
���룺start = "AAAAACCC", end = "AACCCCCC", bank = ["AAAACCCC","AAACCCCC","AACCCCCC"]
�����3

��ʾ��
start.length == 8
end.length == 8
0 <= bank.length <= 10
bank[i].length == 8
start��end �� bank[i] �����ַ� ['A', 'C', 'G', 'T'] ���

*/


// DFS
class Solution1 {
public:
	vector<char> used;
	int ans = 10;
	int minMutation(string startGene, string endGene, vector<string> &bank) {
		used.resize(bank.size(), false);
		dfs(startGene, endGene, bank, 0);
		return ans == 10 ? -1 : ans;
	}
	void dfs(string start, string end, vector<string> &bank, int t) {
		if (t >= ans) return;
		if (start == end) {
			ans = min(ans, t);
			return;
		}
		for (int i = 0; i < bank.size(); ++i) {
			if (used[i]) continue;
			int diff = 0;
			for (int j = 0; j < start.size(); ++j) {
				diff += start[j] != bank[i][j] ? 1 : 0;
			}
			if (diff == 1) {
				used[i] = true;
				dfs(bank[i], end, bank, t + 1);
				used[i] = false;
			}
		}
	}
};


// BFS
class Solution2 {
public:
	int minMutation(string startGene, string endGene, vector<string> &bank) {
		unordered_set<string> s(bank.begin(), bank.end());
		queue<string> q;
		q.push(startGene);
		int step = 0;
		while (!q.empty()) {
			int len = q.size();
			while (len--) {
				string tmp = q.front();
				q.pop();
				if (tmp == endGene) return step;
				for (char c : "ACGT") {
					for (int i = 0; i < tmp.size(); ++i) {
						if (tmp[i] == c) continue;
						string next = tmp;
						next[i] = c;
						if (s.count(next)) {
							q.push(next);
							s.erase(next);
						}
					}
				}
			}
			++step;
		}
		return -1;
	}
};


// ˫��BFS
class Solution3 {
public:
	int minMutation(string startGene, string endGene, vector<string> &bank) {
		unordered_set<string> s(bank.begin(), bank.end());
		if (!s.count(endGene)) return -1;
		queue<string> q1, q2;
		q1.push(startGene), q2.push(endGene);
		unordered_map<string, int> m1, m2;
		m1[startGene] = 0, m2[endGene] = 0;
		while (!q1.empty() && !q2.empty()) {
			int t = -1;
			if (q1.size() <= q2.size()) t = update(q1, m1, m2, s);
			else t = update(q2, m2, m1, s);
			if (t != -1) return t;
		}
		return -1;
	}
	int update(queue<string> &q, unordered_map<string, int> &cur,
		unordered_map<string, int> &other, unordered_set<string> &s) {
		int len = q.size();
		while (len--) {
			string tmp = q.front();
			q.pop();
			int step = cur[tmp];
			for (char c : "ACGT") {
				for (int i = 0; i < tmp.size(); ++i) {
					if (tmp[i] == c) continue;
					string next = tmp;
					next[i] = c;
					if (s.count(next) && !cur.count(next)) {
						if (other.count(next)) return other[next] + step + 1;
						q.push(next);
						cur[next] = step + 1;
					}
				}
			}
		}
		return -1;
	}
};

