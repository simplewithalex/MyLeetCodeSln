#include "header.h"


/*


567. 字符串的排列

给你两个字符串 s1 和 s2 ，写一个函数来判断 s2 是否包含 s1 的排列。如果是，返回 true；否则返回 false
换句话说，s1 的排列之一是 s2 的子串

示例 1：
输入：s1 = "ab" s2 = "eidbaooo"
输出：true
解释：s2 包含 s1 的排列之一 ("ba")

示例 2：
输入：s1= "ab" s2 = "eidboaoo"
输出：false

提示：
1 <= s1.length, s2.length <= 10^4
s1 和 s2 仅包含小写字母

*/

// 与LeetCode 438相同
class Solution {
public:
	bool checkInclusion(string s1, string s2) {
		int sLen = s2.size(), pLen = s1.size();
		if (sLen < pLen) return false;
		vector<int> res;
		vector<int> m(26, 0);
		for (auto c : s1) ++m[c - 'a'];
		int start = 0, end = 0, counter = pLen;
		while (end < sLen) {
			if (m[s2[end] - 'a'] >= 1) --counter;
			--m[s2[end] - 'a'];
			++end;
			while (counter == 0) {
				if (end - start == pLen) return true;
				if (m[s2[start] - 'a'] == 0) ++counter;
				++m[s2[start] - 'a'];
				++start;
			}
		}
		return false;
	}
};
// https://leetcode.com/problems/find-all-anagrams-in-a-string/solutions/92007/sliding-window-algorithm-template-to-solve-all-the-leetcode-substring-search-problem/
// @author https://leetcode.com/u/chaoyanghe/
