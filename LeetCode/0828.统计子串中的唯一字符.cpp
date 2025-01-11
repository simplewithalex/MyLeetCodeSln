#include "header.h"

/*

828. 统计子串中的唯一字符

我们定义了一个函数 countUniqueChars(s) 来统计字符串 s 中的唯一字符，并返回唯一字符的个数

例如：s = "LEETCODE" ，则其中 "L", "T","C","O","D" 都是唯一字符，因为它们只出现一次，所以 countUniqueChars(s) = 5

本题将会给你一个字符串 s ，我们需要返回 countUniqueChars(t) 的总和，其中 t 是 s 的子字符串

输入用例保证返回值为 32 位整数

注意，某些子字符串可能是重复的，但你统计时也必须算上这些重复的子字符串（也就是说，你必须统计 s 的所有子字符串中的唯一字符）

示例 1：
输入: s = "ABC"
输出: 10
解释: 所有可能的子串为："A","B","C","AB","BC" 和 "ABC"。
其中，每一个子串都由独特字符构成。
所以其长度总和为：1 + 1 + 1 + 2 + 2 + 3 = 10

示例 2：
输入: s = "ABA"
输出: 8
解释: 除了 countUniqueChars("ABA") = 1 之外，其余与示例 1 相同

示例 3：
输入：s = "LEETCODE"
输出：92

提示：
1 <= s.length <= 10^5
s 只包含大写英文字符

*/


// 记忆化回溯
class Solution1 {
public:
	vector<int> last0;
	vector<int> last1;
	vector<int> memo;
	int uniqueLetterString(string s) {
		int len = s.size();
		memo.resize(len, -1);
		last0.resize(26, -1);
		last1.resize(26, -1);
		int ans = 0;
		for (int i = 0; i < len; ++i) {
			ans += helper(s, i);
		}
		return ans;
	}
	int helper(const string &s, int idx) {
		if (idx < 0) return 0;
		if (memo[idx] != -1) return memo[idx];
		char c = s[idx] - 'A';
		memo[idx] = helper(s, idx - 1) + idx - 2 * last0[c] + last1[c];
		last1[c] = last0[c];
		last0[c] = idx;
		return memo[idx];
	}
};

// 自底而上动态规划
class Solution2 {
public:
	int uniqueLetterString(string s) {
		vector<int> last0(26, -1);
		vector<int> last1(26, -1);
		int len = s.size();
		int ans = 0, cur = 0;
		for (int i = 0; i < len; ++i) {
			char c = s[i] - 'A';
			cur += i - 2 * last0[c] + last1[c];
			ans += cur;
			last1[c] = last0[c];
			last0[c] = i;
		}
		return ans;
	}
};

// https://leetcode.cn/problems/count-unique-characters-of-all-substrings-of-a-given-string/solutions/1804144/by-endlesscheng-ko4z/
// @author https://leetcode.cn/u/endlesscheng/

