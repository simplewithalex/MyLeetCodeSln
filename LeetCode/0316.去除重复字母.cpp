#include "header.h"

/*

316. 去除重复字母

给你一个字符串s，请你去除字符串中重复的字母，使得每个字母只出现一次
需保证 返回结果的字典序最小（要求不能打乱其他字符的相对位置）

示例 1：
输入：s = "bcabc"
输出："abc"

示例 2：
输入：s = "cbacdcbc"
输出："acdb"

提示：
1 <= s.length <= 104
s 由小写英文字母组成

注意：该题与 1081 https://leetcode-cn.com/problems/smallest-subsequence-of-distinct-characters 相同

*/

// 单调栈
class Solution {
public:
	string removeDuplicateLetters(string s) {
		vector<char> stk;
		vector<char> inStk(26, false);
		vector<int> count(26, 0);
		for (char c : s) ++count[c - 'a'];
		for (char c : s) {
			--count[c - 'a'];
			if (inStk[c - 'a']) continue;
			while (!stk.empty() && stk.back() > c) {
				if (!count[stk.back() - 'a']) break;
				inStk[stk.back() - 'a'] = false;
				stk.pop_back();
			}
			stk.push_back(c);
			inStk[c - 'a'] = true;
		}
		return string(stk.begin(), stk.end());
	}
};

// https://leetcode.cn/problems/remove-duplicate-letters/solutions/417758/you-qian-ru-shen-dan-diao-zhan-si-lu-qu-chu-zhong-/
// https://leetcode.cn/u/labuladong/
