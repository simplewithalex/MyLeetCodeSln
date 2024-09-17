#include "header.h"

/*

395. 至少有 K 个重复字符的最长子串

给你一个字符串 s 和一个整数 k，请你找出 s 中的最长子串， 要求该子串中的每一字符出现次数都不少于 k
返回这一子串的长度
如果不存在这样的子字符串，则返回 0

示例 1：
输入：s = "aaabb", k = 3
输出：3
解释：最长子串为 "aaa" ，其中 'a' 重复了 3 次

示例 2：
输入：s = "ababbc", k = 2
输出：5
解释：最长子串为 "ababb" ，其中 'a' 重复了 2 次， 'b' 重复了 3 次

提示：
1 <= s.length <= 10^4
s 仅由小写英文字母组成
1 <= k <= 10^5

*/


// 使用 LeetCode 438 滑窗模板
class Solution1 {
public:
	int longestSubstring(string s, int k) {
		int res = 0;
		for (int uniqueNum = 1; uniqueNum <= 26; ++uniqueNum) {
			res = max(res, helper(s, k, uniqueNum));
		}
		return res;
	}

private:
	int helper(const string &s, int k, int uniqueNum) {
		int m[26] = {};
		int start = 0, end = 0;
		int len = s.size();
		int res = INT_MIN;
		// 不同字母的数量
		int counter = 0;
		// 满足 k 的不同字母数量
		int sumK = 0;
		while (end < len) {
			char c = s[end];
			++m[c - 'a'];
			if (m[c - 'a'] == 1) ++counter;
			if (m[c - 'a'] == k) ++sumK;
			++end;
			while (counter > uniqueNum) {
				c = s[start];
				--m[c - 'a'];
				if (m[c - 'a'] == 0) --counter;
				if (m[c - 'a'] == k - 1) --sumK;
				++start;
			}
			if (counter == sumK) res = max(res, end - start);
		}
		return res;
	}
};
// https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/solutions/170010/java-o-n-solution-with-detailed-explanation-sliding-window/
// @author https://leetcode.com/u/seanmsha/

class Solution2 {
public:
	int longestSubstring(string s, int k) {
		if (s.size() < k) return 0;
		unordered_set<char> chars(s.begin(), s.end());
		int counter[26] = {};
		for (char c : s) ++counter[c - 'a'];
		for (char c : chars) {
			vector<string> strs;
			if (counter[c - 'a'] < k) {
				split(s, strs, c);
				int res = 0;
				for (string str : strs) {
					res = max(res, longestSubstring(str, k));
				}
				return res;
			}
		}
		return s.size();
	}

private:
	void split(const string &s, vector<string> &strs, const char delim = ' ') {
		strs.clear();
		istringstream is(s);
		string temp;
		while (getline(is, temp, delim)) {
			strs.push_back(temp);
		}
	}
};

