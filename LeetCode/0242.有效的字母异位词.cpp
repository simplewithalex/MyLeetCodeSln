#include "header.h"

/*

给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。
注意：若 s 和 t 中每个字符出现的次数都相同，则称 s 和 t 互为字母异位词。

示例 1:
输入: s = "anagram", t = "nagaram"
输出: true

示例 2:
输入: s = "rat", t = "car"
输出: false

提示:
1 <= s.length, t.length <= 5 * 10^4
s 和 t 仅包含小写字母

进阶: 如果输入字符串包含 unicode 字符怎么办？你能否调整你的解法来应对这种情况？

*/

class Solution {
public:
	bool isAnagram(string s, string t) {
		if (s.size() != t.size()) return false;
		unordered_map<char, int> m;
		for (int i = 0; i < s.size(); ++i) ++m[s[i]];
		for (int i = 0; i < t.size(); ++i) {
			--m[t[i]];
			if (m[t[i]] < 0) return false;
		}
		return true;
	}
};

// Unicode中可能存在一个字符对应多个字节的问题
// 为了让计算机知道多少字节表示一个字符，采用面向传输的编码方式UTF-8、UTF−16等
// 问题核心在于字符的表示是离散未知的，因此用哈希表维护对应字符的频次

