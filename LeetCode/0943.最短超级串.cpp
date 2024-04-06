#include "header.h"

/*

943. ��̳�����


����һ���ַ������� words���ҵ��� words ��ÿ���ַ�����Ϊ���ַ���������ַ���
����ж����Ч����ַ���������Ŀ�������������� ����һ�� ����
���ǿ��Լ��� words ��û���ַ����� words ����һ���ַ��������ַ���

ʾ�� 1��
���룺words = ["alex","loves","leetcode"]
�����"alexlovesleetcode"
���ͣ�"alex"��"loves"��"leetcode" ���������ж��ᱻ����

ʾ�� 2��
���룺words = ["catg","ctaagt","gcta","ttca","atgcatc"]
�����"gctaagttcatgcatc"

��ʾ��
1 <= words.length <= 12
1 <= words[i].length <= 20
words[i] ��СдӢ����ĸ���
words �е������ַ��� ������ͬ

*/

// ����¼
class Solution1 {
private:
	vector<vector<int>> memo;
	vector<vector<int>> prev;
	vector<vector<int>> overlaps;

public:
	string shortestSuperstring(vector<string> &words) {
		int len = words.size();
		int total = 1 << len;
		memo.resize(total, vector<int>(len, -1));
		prev.resize(total, vector<int>(len, -1));
		overlaps.resize(len, vector<int>(len, 0));
		for (int i = 0; i < len; ++i) {
			string word1 = words[i];
			for (int j = 0; j < len; ++j) {
				string word2 = words[j];
				if (i == j) overlaps[i][j] = word1.size();
				else overlaps[i][j] = getOverlap(word1, word2);
			}
		}
		int endStatus = total - 1;
		int minSuperLen = INT_MAX;
		int minIdx = 0;
		for (int i = 0; i < len; ++i) {
			int tempLen = helper(words, endStatus, i);
			if (tempLen < minSuperLen) {
				minSuperLen = tempLen;
				minIdx = i;
			}
		}
		vector<int> permutation(len);
		for (int status = endStatus, i = minIdx, j = len - 1; j >= 0; --j) {
			permutation[j] = i;
			int preIdx = prev[status][i];
			status -= (1 << i);
			i = preIdx;
		}
		string res = words[permutation[0]];
		for (int i = 1; i < len; ++i) {
			int overlap = overlaps[permutation[i - 1]][permutation[i]];
			res.append(words[permutation[i]].substr(overlap));
		}
		return res;
	}

private:
	int helper(const vector<string> &words, int status, int idx) {
		if (memo[status][idx] != -1) return memo[status][idx];
		int wordLen = words[idx].size();
		int preStatus = status - (1 << idx);
		if (preStatus == 0) return wordLen;
		int minSuperLen = INT_MAX;
		for (int j = 0; j < words.size(); ++j) {
			if ((preStatus & (1 << j)) != 0) {
				int tempLen =
					helper(words, preStatus, j) + wordLen - overlaps[j][idx];
				if (tempLen < minSuperLen) {
					minSuperLen = tempLen;
					prev[status][idx] = j;
				}
			}
		}
		return memo[status][idx] = minSuperLen;
	}
	int getOverlap(const string &word1, const string &word2) {
		int maxLen = min(word1.size(), word2.size());
		for (int i = maxLen; i >= 1; --i) {
			if (word1.substr(word1.size() - i) == word2.substr(0, i)) {
				return i;
			}
		}
		return 0;
	}
};
// https://leetcode.cn/problems/find-the-shortest-superstring/solutions/2278271/943-zui-duan-chao-ji-chuan-by-stormsunsh-w594/
// @author https://leetcode.cn/u/stormsunshine/



// �Ե׶��ϵĶ�̬�滮
class Solution2 {
public:
	string shortestSuperstring(vector<string> &words) {
		int len = words.size();
		vector<vector<int>> overlaps(len, vector<int>(len, 0));
		for (int i = 0; i < len; ++i) {
			string word1 = words[i];
			for (int j = 0; j < len; ++j) {
				string word2 = words[j];
				if (i == j) overlaps[i][j] = word1.size();
				else overlaps[i][j] = getOverlap(word1, word2);
			}
		}
		int total = 1 << len;
		vector<vector<int>> dp(total, vector<int>(len, INT_MAX));
		vector<vector<int>> prev(total, vector<int>(len, -1));
		for (int i = 1; i < total; ++i) {
			for (int j = 0; j < len; ++j) {
				if (i & (1 << j)) {
					int wordLen = words[j].size();
					int preState = i - (1 << j);
					if (preState == 0) {
						dp[i][j] = wordLen;
					} else {
						for (int k = 0; k < len; ++k) {
							if (preState & (1 << k)) {
								int curLen =
									dp[preState][k] + wordLen - overlaps[k][j];
								if (curLen < dp[i][j]) {
									dp[i][j] = curLen;
									prev[i][j] = k;
								}
							}
						}
					}
				}
			}
		}
		int minLen = dp[total - 1][0];
		int minIdx = 0;
		for (int j = 1; j < len; ++j) {
			if (dp[total - 1][j] < minLen) {
				minLen = dp[total - 1][j];
				minIdx = j;
			}
		}

		vector<int> permutation(len);
		for (int state = total - 1, i = minIdx, j = len - 1; j >= 0; --j) {
			permutation[j] = i;
			int preIdx = prev[state][i];
			state -= (1 << i);
			i = preIdx;
		}

		string res = words[permutation[0]];
		for (int i = 1; i < len; ++i) {
			int overlap = overlaps[permutation[i - 1]][permutation[i]];
			res.append(words[permutation[i]].substr(overlap));
		}
		return res;
	}

private:
	int getOverlap(const string &word1, const string &word2) {
		int maxLen = min(word1.size(), word2.size());
		for (int i = maxLen; i >= 1; --i) {
			if (word1.substr(word1.size() - i) == word2.substr(0, i)) {
				return i;
			}
		}
		return 0;
	}
};

