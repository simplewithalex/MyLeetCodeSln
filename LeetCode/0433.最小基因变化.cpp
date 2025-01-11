#include "header.h"

/*

433. 最小基因变化

基因序列可以表示为一条由 8 个字符组成的字符串，其中每个字符都是 'A'、'C'、'G' 和 'T' 之一

假设我们需要调查从基因序列 start 变为 end 所发生的基因变化。一次基因变化就意味着这个基因序列中的一个字符发生了变化
例如，"AACCGGTT" --> "AACCGGTA" 就是一次基因变化

另有一个基因库 bank 记录了所有有效的基因变化，只有基因库中的基因才是有效的基因序列。（变化后的基因必须位于基因库 bank 中）

给你两个基因序列 start 和 end ，以及一个基因库 bank ，请你找出并返回能够使 start 变化为 end 所需的最少变化次数。如果无法完成此基因变化，返回 -1
注意：起始基因序列 start 默认是有效的，但是它并不一定会出现在基因库中

示例 1：
输入：start = "AACCGGTT", end = "AACCGGTA", bank = ["AACCGGTA"]
输出：1

示例 2：
输入：start = "AACCGGTT", end = "AAACGGTA", bank = ["AACCGGTA","AACCGCTA","AAACGGTA"]
输出：2

示例 3：
输入：start = "AAAAACCC", end = "AACCCCCC", bank = ["AAAACCCC","AAACCCCC","AACCCCCC"]
输出：3

提示：
start.length == 8
end.length == 8
0 <= bank.length <= 10
bank[i].length == 8
start、end 和 bank[i] 仅由字符 ['A', 'C', 'G', 'T'] 组成

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


// 双向BFS
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

