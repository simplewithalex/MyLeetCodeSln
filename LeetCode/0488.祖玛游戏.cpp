#include "header.h"

/*

488. ������Ϸ

�����ڲ���������Ϸ��һ�����֡�
�����������Ϸ�����У��������� һ�� ����ÿ�������ɫ�����ǣ���ɫ 'R'����ɫ 'Y'����ɫ 'B'����ɫ 'G' ���ɫ 'W' ���������Ҳ��һЩ����

���Ŀ���� ��� ���������е���ÿһ�غϣ�

1 �������ϵĲ�����ѡ�� ����һ�� ��Ȼ���������������һ�����У�����֮�����һ�������һ�ˡ�

2 ���ţ�����г��� ���������������� �� ��ɫ��ͬ ���������Ļ����Ͱ������Ƴ�����
  ��������Ƴ�����ͬ�����³�����������������������ɫ��ͬ��������������Լ����Ƴ���Щ��ֱ�����������Ƴ�������

3 ��������������򶼱��Ƴ�������Ϊ��Ӯ�ñ�����Ϸ��

4 �ظ�������̣�ֱ����Ӯ����Ϸ��������û�и������

����һ���ַ��� board ����ʾ�������ʼ�������������һ���ַ��� hand ����ʾ����Ĳ������㰴�������������Ƴ������������򣬼��㲢��������� ���� ��������������Ƴ��������е��򣬷��� -1

ʾ�� 1��
���룺board = "WRRBBW", hand = "RB"
�����-1
���ͣ��޷��Ƴ������ϵ������򡣿��Եõ�����þ����ǣ�
- ����һ�� 'R' ��ʹ�����Ϊ WRRRBBW ��WRRRBBW -> WBBW
- ����һ�� 'B' ��ʹ�����Ϊ WBBBW ��WBBBW -> WW
�����ϻ�ʣ����û����������Բ��롣

ʾ�� 2��
���룺board = "WWRRBBWW", hand = "WRBRW"
�����2
���ͣ�Ҫ����������ϵ��򣬿��԰��������裺
- ����һ�� 'R' ��ʹ�����Ϊ WWRRRBBWW ��WWRRRBBWW -> WWBBWW
- ����һ�� 'B' ��ʹ�����Ϊ WWBBBWW ��WWBBBWW -> WWWW -> empty
ֻ������г� 2 ����Ϳ���������档

ʾ�� 3��
���룺board = "G", hand = "GGGGG"
�����2
���ͣ�Ҫ����������ϵ��򣬿��԰��������裺
- ����һ�� 'G' ��ʹ�����Ϊ GG ��
- ����һ�� 'G' ��ʹ�����Ϊ GGG ��GGG -> empty
ֻ������г� 2 ����Ϳ���������档

ʾ�� 4��
���룺board = "RBYYBBRRB", hand = "YRBGB"
�����3
���ͣ�Ҫ����������ϵ��򣬿��԰��������裺
- ����һ�� 'Y' ��ʹ�����Ϊ RBYYYBBRRB ��RBYYYBBRRB -> RBBBRRB -> RRRB -> B
- ����һ�� 'B' ��ʹ�����Ϊ BB ��
- ����һ�� 'B' ��ʹ�����Ϊ BBB ��BBB -> empty
ֻ������г� 3 ����Ϳ���������档

��ʾ��
1 <= board.length <= 16
1 <= hand.length <= 5
board �� hand ���ַ� 'R'��'Y'��'B'��'G' �� 'W' ���
������һ��ʼ�����У�����������������������ɫ��ͬ�����ŵ���

*/

// BFS + ��֦
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
		// ע��l��r��λ���Ѿ����ƶ���һλ
		if (r - l > 3) {
			string s_new = s.substr(0, l + 1) + s.substr(r);
			return convert(s_new, l + 1, l + 1);
		} else {
			return s;
		}
	}
};

// DFS + ��֦
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
// @author ���۹ٷ����
