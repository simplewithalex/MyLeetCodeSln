#include "header.h"

/*

514. ����֮·


������Ϸ������4���У����� ��ͨ�����ɡ� Ҫ����ҵ�����Ϊ ��Freedom Trail Ring�� �Ľ������̣���ʹ�ñ���ƴд�ض��ؼ��ʲ��ܿ���

����һ���ַ��� ring ����ʾ�����⻷�ϵı��룻������һ���ַ��� key ����ʾ��Ҫƴд�Ĺؼ��ʡ�����Ҫ����ܹ�ƴд�ؼ����������ַ������ٲ���

�����ring �ĵ�һ���ַ��� 12:00 ������롣����Ҫ˳ʱ�����ʱ����ת ring ��ʹ key ��һ���ַ��� 12:00 ������룬Ȼ�������İ�ť���Դ����ƴд�� key �е������ַ�

��ת ring ƴ�� key �ַ� key[i] �Ľ׶��У�

1 �����Խ� ring ˳ʱ�����ʱ����ת һ��λ�� ����Ϊ1������ת������Ŀ���ǽ��ַ��� ring ��һ���ַ��� 12:00 ������룬��������ַ���������ַ� key[i]
2 ����ַ� key[i] �Ѿ����뵽12:00��������Ҫ�������İ�ť����ƴд����Ҳ������ 1 ��������֮�������Կ�ʼƴд key ����һ���ַ�����һ�׶Σ���ֱ���������ƴд


ʾ�� 1��
����: ring = "godding", key = "gd"
���: 4
����:
���� key �ĵ�һ���ַ� 'g'���Ѿ�����ȷ��λ��, ����ֻ��Ҫ1����ƴд����ַ�
���� key �ĵڶ����ַ� 'd'��������Ҫ��ʱ����ת ring "godding" 2��ʹ����� "ddinggo"
��Ȼ, ���ǻ���Ҫ1������ƴд
������յ������ 4

ʾ�� 2:
����: ring = "godding", key = "godding"
���: 13

��ʾ��
1 <= ring.length, key.length <= 100
ring �� key ֻ����СдӢ����ĸ
��֤ �ַ��� key һ���������ַ��� ring ��תƴ��

*/

// DFS + ���仯��֦
class Solution1 {
private:
	string key;
	string ring;
	unordered_map<char, vector<int>> indices;
	vector<vector<int>> memo;

public:
	int findRotateSteps(string ring, string key) {
		this->key = key, this->ring = ring;
		memo.resize(ring.size(), vector<int>(key.size(), -1));
		for (int i = 0; i < ring.size(); ++i) {
			indices[ring[i]].push_back(i);
		}
		return key.size() + dfs(0, 0);
	}

private:
	int dfs(int ridx, int kidx) {
		if (kidx == key.size()) return 0;
		if (memo[ridx][kidx] != -1) return memo[ridx][kidx];
		char c = key[kidx];
		int res = INT_MAX;
		for (int idx : indices[c]) {
			int d1 = abs(ridx - idx);
			int d2 = ring.size() - d1;
			int d = min(d1, d2);
			res = min(res, dfs(idx, kidx + 1) + d);
		}
		return memo[ridx][kidx] = res;
	}
};


// ���仯����
class Solution2 {
private:
	string key;
	string ring;
	vector<vector<int>> pos;
	vector<vector<int>> memo;

public:
	int findRotateSteps(string ring, string key) {
		this->key = key, this->ring = ring;
		pos.resize(26);
		for (int i = 0; i < ring.size(); ++i) {
			pos[ring[i] - 'a'].push_back(i);
		}
		memo.resize(ring.size(), vector<int>(key.size(), -1));
		int res = INT_MAX;
		for (int i : pos[key[key.size() - 1] - 'a']) {
			res = min(res, helper(i, key.size() - 1));
		}
		return res + key.size();
	}

private:
	int helper(int ridx, int kidx) {
		if (kidx == 0) return min(ridx, (int)(ring.size() - ridx));
		if (memo[ridx][kidx] != -1) return memo[ridx][kidx];
		int res = INT_MAX;
		for (int lastIdx : pos[key[kidx - 1] - 'a']) {
			int d1 = abs(ridx - lastIdx);
			int d2 = ring.size() - d1;
			int d = min(d1, d2);
			res = min(res, helper(lastIdx, kidx - 1) + d);
		}
		return memo[ridx][kidx] = res;
	}
};

// �޸�Ϊ��̬�滮
class Solution3 {
public:
	int findRotateSteps(string ring, string key) {
		int rLen = ring.size(), kLen = key.size();
		vector<vector<int>> pos(26);
		for (int i = 0; i < rLen; ++i) {
			pos[ring[i] - 'a'].push_back(i);
		}
		vector<vector<int>> dp(rLen, vector<int>(kLen, INT_MAX));
		for (int i : pos[key[0] - 'a']) dp[i][0] = min(i, rLen - i);
		for (int j = 1; j < kLen; ++j) {
			for (int curIdx : pos[key[j] - 'a']) {
				for (int lastIdx : pos[key[j - 1] - 'a']) {
					dp[curIdx][j] = min(dp[curIdx][j],
						dp[lastIdx][j - 1] +
						min(abs(curIdx - lastIdx),
							rLen - abs(curIdx - lastIdx)));
				}
			}
		}
		int res = INT_MAX;
		for (int idx : pos[key[kLen - 1] - 'a']) {
			res = min(res, dp[idx][kLen - 1]);
		}
		return kLen + res;
	}
};



// BFS
struct State {
	int dist = 0;
	int ridx = 0;
	int kidx = 0;
	State(int d, int ri, int ki) : dist(d), ridx(ri), kidx(ki) {}
	// ע������Ϊ������Ա����
	bool operator<(const State &s) const { return s.dist < this->dist; }
};

class Solution {
public:
	int findRotateSteps(string ring, string key) {
		int rLen = ring.size();
		int kLen = key.size();
		vector<vector<int>> pos(26);
		vector<vector<int>> memo(rLen, vector<int>(kLen, INT_MAX));
		for (int i = 0; i < rLen; ++i) pos[ring[i] - 'a'].push_back(i);
		priority_queue<State> pq;
		for (int idx : pos[key[0] - 'a']) {
			pq.push(State(min(idx, rLen - idx), idx, 0));
		}
		while (!pq.empty()) {
			State cur = pq.top();
			pq.pop();
			if (cur.kidx == kLen - 1) return cur.dist + kLen;
			for (int idx : pos[key[cur.kidx + 1] - 'a']) {
				int d1 = abs(cur.ridx - idx);
				int d2 = rLen - d1;
				int d = cur.dist + min(d1, d2);
				if (d < memo[idx][cur.kidx + 1]) {
					memo[idx][cur.kidx + 1] = d;
					pq.push(State(d, idx, cur.kidx + 1));
				}
			}
		}
		return 0;
	}
};

// https://leetcode.cn/problems/freedom-trail/solutions/480315/zi-you-zhi-lu-by-leetcode-solution/comments/662529
// �������ݣ����������0x3f3f3f��һЩ֪ʶ

