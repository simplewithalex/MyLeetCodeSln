#include "header.h"

/*

943. 最短超级串


给定一个字符串数组 words，找到以 words 中每个字符串作为子字符串的最短字符串
如果有多个有效最短字符串满足题目条件，返回其中 任意一个 即可
我们可以假设 words 中没有字符串是 words 中另一个字符串的子字符串

示例 1：
输入：words = ["alex","loves","leetcode"]
输出："alexlovesleetcode"
解释："alex"，"loves"，"leetcode" 的所有排列都会被接受

示例 2：
输入：words = ["catg","ctaagt","gcta","ttca","atgcatc"]
输出："gctaagttcatgcatc"

提示：
1 <= words.length <= 12
1 <= words[i].length <= 20
words[i] 由小写英文字母组成
words 中的所有字符串 互不相同

*/

// 备忘录
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



// 自底而上的动态规划
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

