#include "header.h"

/*

488. 祖玛游戏

你正在参与祖玛游戏的一个变种。
在这个祖玛游戏变体中，桌面上有 一排 彩球，每个球的颜色可能是：红色 'R'、黄色 'Y'、蓝色 'B'、绿色 'G' 或白色 'W' 。你的手中也有一些彩球。

你的目标是 清空 桌面上所有的球。每一回合：

1 从你手上的彩球中选出 任意一颗 ，然后将其插入桌面上那一排球中：两球之间或这一排球的任一端。

2 接着，如果有出现 三个或者三个以上 且 颜色相同 的球相连的话，就把它们移除掉。
  如果这种移除操作同样导致出现三个或者三个以上且颜色相同的球相连，则可以继续移除这些球，直到不再满足移除条件。

3 如果桌面上所有球都被移除，则认为你赢得本场游戏。

4 重复这个过程，直到你赢了游戏或者手中没有更多的球。

给你一个字符串 board ，表示桌面上最开始的那排球。另给你一个字符串 hand ，表示手里的彩球。请你按上述操作步骤移除掉桌上所有球，计算并返回所需的 最少 球数。如果不能移除桌上所有的球，返回 -1

示例 1：
输入：board = "WRRBBW", hand = "RB"
输出：-1
解释：无法移除桌面上的所有球。可以得到的最好局面是：
- 插入一个 'R' ，使桌面变为 WRRRBBW 。WRRRBBW -> WBBW
- 插入一个 'B' ，使桌面变为 WBBBW 。WBBBW -> WW
桌面上还剩着球，没有其他球可以插入。

示例 2：
输入：board = "WWRRBBWW", hand = "WRBRW"
输出：2
解释：要想清空桌面上的球，可以按下述步骤：
- 插入一个 'R' ，使桌面变为 WWRRRBBWW 。WWRRRBBWW -> WWBBWW
- 插入一个 'B' ，使桌面变为 WWBBBWW 。WWBBBWW -> WWWW -> empty
只需从手中出 2 个球就可以清空桌面。

示例 3：
输入：board = "G", hand = "GGGGG"
输出：2
解释：要想清空桌面上的球，可以按下述步骤：
- 插入一个 'G' ，使桌面变为 GG 。
- 插入一个 'G' ，使桌面变为 GGG 。GGG -> empty
只需从手中出 2 个球就可以清空桌面。

示例 4：
输入：board = "RBYYBBRRB", hand = "YRBGB"
输出：3
解释：要想清空桌面上的球，可以按下述步骤：
- 插入一个 'Y' ，使桌面变为 RBYYYBBRRB 。RBYYYBBRRB -> RBBBRRB -> RRRB -> B
- 插入一个 'B' ，使桌面变为 BB 。
- 插入一个 'B' ，使桌面变为 BBB 。BBB -> empty
只需从手中出 3 个球就可以清空桌面。

提示：
1 <= board.length <= 16
1 <= hand.length <= 5
board 和 hand 由字符 'R'、'Y'、'B'、'G' 和 'W' 组成
桌面上一开始的球中，不会有三个及三个以上颜色相同且连着的球

*/

// BFS + 剪枝
class Solution1 {
public:
	int findMinStep(string board, string hand) {
		queue<pair<string, string>> q;
		unordered_set<string> visited;
		sort(hand.begin(), hand.end());
		q.push({ board, hand });
		visited.insert(board + "#" + hand);
		int step = 1;
		while (!q.empty()) {
			int len = q.size();
			while (len--) {
				auto p = q.front();
				q.pop();
				string b = p.first, h = p.second;
				int bLen = b.size(), hLen = h.size();
				for (int j = 0; j < hLen; ++j) {
					if (j > 0 && h[j - 1] == h[j]) continue;
					for (int i = 0; i < bLen; ++i) {
						if (i > 0 && b[i - 1] == b[i] && h[j] == b[i]) continue;
						if (!(h[j] == b[i] || (i > 0 && b[i - 1] == b[i]))) continue;
						string b_orig = b.substr(0, i) + h[j] + b.substr(i);
						string b_new = convert(b_orig, i, i);
						if (b_new.empty()) return step;
						string h_new = h.substr(0, j) + h.substr(j + 1);
						string key = b_new + "#" + h_new;
						if (!visited.count(key)) {
							q.push({ b_new, h_new });
							visited.insert(key);
						}
					}
				}
			}
			++step;
		}
		return -1;
	}

private:
	string convert(const string &s, int l, int r) {
		int len = s.size();
		if (len < 3 || s[l] != s[r]) return s;
		char c = s[l];
		while (l >= 0 && s[l] == c) --l;
		while (r < len && s[r] == c) ++r;
		// 注意l和r的位置已经多移动了一位
		if (r - l > 3) {
			string s_new = s.substr(0, l + 1) + s.substr(r);
			return convert(s_new, l + 1, l + 1);
		} else {
			return s;
		}
	}
};

// DFS + 剪枝
class Solution2 {
private:
	unordered_map<string, int> memo;

public:
	int findMinStep(string board, string hand) {
		sort(hand.begin(), hand.end());
		int res = dfs(board, hand);
		return res <= 5 ? res : -1;
	}

private:
	int dfs(const string &board, const string &hand) {
		if (board.empty()) return 0;
		string key = board + "#" + hand;
		if (memo.count(key)) return memo[key];
		int res = 6;
		for (int j = 0; j < hand.size(); ++j) {
			if (j > 0 && hand[j - 1] == hand[j]) continue;
			for (int i = 0; i < board.size(); ++i) {
				if (!(hand[j] == board[i] ||
					(i > 0 && board[i - 1] == board[i]))) {
					continue;
				}
				string b_orig = board.substr(0, i) + hand[j] + board.substr(i);
				string b_new = convert(b_orig, i, i);
				string h_new = hand.substr(0, j) + hand.substr(j + 1);
				res = min(res, dfs(b_new, h_new) + 1);
			}
		}
		memo[key] = res;
		return res;
	}
	string convert(const string &s, int l, int r) {
		int len = s.size();
		if (len < 3 || s[l] != s[r]) return s;
		char c = s[l];
		while (l >= 0 && s[l] == c) --l;
		while (r < len && s[r] == c) ++r;
		if (r - l > 3) {
			string s_new = s.substr(0, l + 1) + s.substr(r);
			return convert(s_new, l + 1, l + 1);
		} else {
			return s;
		}
	}
};
// https://leetcode.cn/problems/zuma-game/solutions/1092466/zu-ma-you-xi-by-leetcode-solution-lrp4/
// @author 力扣官方题解
