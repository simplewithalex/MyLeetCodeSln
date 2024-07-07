#include "header.h"

/*

514. 自由之路


电子游戏“辐射4”中，任务 “通向自由” 要求玩家到达名为 “Freedom Trail Ring” 的金属表盘，并使用表盘拼写特定关键词才能开门

给定一个字符串 ring ，表示刻在外环上的编码；给定另一个字符串 key ，表示需要拼写的关键词。您需要算出能够拼写关键词中所有字符的最少步数

最初，ring 的第一个字符与 12:00 方向对齐。您需要顺时针或逆时针旋转 ring 以使 key 的一个字符在 12:00 方向对齐，然后按下中心按钮，以此逐个拼写完 key 中的所有字符

旋转 ring 拼出 key 字符 key[i] 的阶段中：

1 您可以将 ring 顺时针或逆时针旋转 一个位置 ，计为1步。旋转的最终目的是将字符串 ring 的一个字符与 12:00 方向对齐，并且这个字符必须等于字符 key[i]
2 如果字符 key[i] 已经对齐到12:00方向，您需要按下中心按钮进行拼写，这也将算作 1 步。按完之后，您可以开始拼写 key 的下一个字符（下一阶段），直至完成所有拼写


示例 1：
输入: ring = "godding", key = "gd"
输出: 4
解释:
对于 key 的第一个字符 'g'，已经在正确的位置, 我们只需要1步来拼写这个字符
对于 key 的第二个字符 'd'，我们需要逆时针旋转 ring "godding" 2步使它变成 "ddinggo"
当然, 我们还需要1步进行拼写
因此最终的输出是 4

示例 2:
输入: ring = "godding", key = "godding"
输出: 13

提示：
1 <= ring.length, key.length <= 100
ring 和 key 只包含小写英文字母
保证 字符串 key 一定可以由字符串 ring 旋转拼出

*/

// DFS + 记忆化剪枝
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


// 记忆化搜索
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

// 修改为动态规划
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
	// 注意重载为常量成员函数
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
// 补充内容：关于无穷大0x3f3f3f的一些知识

