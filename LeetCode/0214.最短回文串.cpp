#include "header.h"

/*

给定一个字符串 s，你可以通过在字符串前面添加字符将其转换为回文串。
找到并返回可以用这种方式转换的最短回文串。

示例 1：
输入：s = "aacecaaa"
输出："aaacecaaa"

示例 2：
输入：s = "abcd"
输出："dcbabcd"
  
提示：
0 <= s.length <= 5 * 10^4
s 仅由小写英文字母组成

*/

// 使用KMP方法，参考0028题

// 基于DFA
class Solution1 {
public:
	string shortestPalindrome(string s) {
		int len = s.size();
		if (len == 0) return "";
		vector<vector<int>> dp(len, vector<int>(26, 0));
		kmp(s, dp);
		int j = 0;
		for (int i = len - 1; i >= 0; --i) {
			j = dp[j][s[i] - 'a'];
		}
		string add = s.substr(j);
		reverse(add.begin(), add.end());
		return add + s;
	}

private:
	void kmp(const string &pat, vector<vector<int>> &dp) {
		int len = pat.size();
		dp[0][pat[0] - 'a'] = 1;
		int flag = 0;
		for (int i = 1; i < len; ++i) {
			for (int ch = 0; ch < 26; ++ch) {
				dp[i][ch] = dp[flag][ch];
			}
			dp[i][pat[i] - 'a'] = i + 1;
			flag = dp[flag][pat[i] - 'a'];
		}
	}
};

// 基于PMT构造next表
class Solution2 {
public:
	string shortestPalindrome(string s) {
		int len = s.size();
		if (len == 0) return "";
		vector<int> next(len, 0);
		buildNext(s, next);
		int i = len - 1, j = 0;
		while (i >= 0) {
			if (j < 0 || s[i] == s[j]) {
				--i;
				++j;
			}
			else {
				j = next[j];
			}
		}
		string add = s.substr(j);
		reverse(add.begin(), add.end());
		return add + s;
	}
private:
	void buildNext(const string &pat, vector<int> &next) {
		int len = pat.size();
		next[0] = -1;
		int i = 0, j = -1;
		while (i < len - 1) {
			if (j < 0 || pat[i] == pat[j]) {
				++i;
				++j;
				next[i] = pat[i] != pat[j] ? j : next[j];
			}
			else {
				j = next[j];
			}
		}
	}
};