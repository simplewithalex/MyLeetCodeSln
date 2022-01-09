#include "header.h"

/*

给定两个字符串 s 和 t，判断它们是否是同构的。

如果 s 中的字符可以按某种映射关系替换得到 t ，那么这两个字符串是同构的。
每个出现的字符都应当映射到另一个字符，同时不改变字符的顺序。
不同字符不能映射到同一个字符上，相同字符只能映射到同一个字符上，字符可以映射到自己本身。

示例 1:
输入：s = "egg", t = "add"
输出：true

示例 2：
输入：s = "foo", t = "bar"
输出：false

示例 3：
输入：s = "paper", t = "title"
输出：true
  
提示：可以假设 s 和 t 长度相同。

*/

class Solution1 {
public:
	bool isIsomorphic(string s, string t) {
		return helper(s, t) && helper(t, s);
	}

private:
	bool helper(const string &s, const string &t) {
		int len = s.size();
		vector<char> bkt(128, -1);
		for (int i = 0; i < len; ++i) {
			if (bkt[s[i]] != -1) {
				if (bkt[s[i]] != t[i]) return false;
			}
			else {
				bkt[s[i]] = t[i];
			}
		}
		return true;
	}
};


class Solution2 {
public:
	bool isIsomorphic(string s, string t) {
		vector<char> bkt_s(128, -1);
		vector<char> bkt_t(128, -1);
		int len = s.size();
		for (int i = 0; i < len; ++i) {
			if (bkt_s[s[i]] != bkt_t[t[i]]) {
				return false;
			}
			else {
				if (bkt_s[s[i]] == -1) {
					bkt_s[s[i]] = i;
					bkt_t[t[i]] = i;
				}
			}
		}
		return true;
	}
};
// https://leetcode-cn.com/problems/isomorphic-strings/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-42/