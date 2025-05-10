#include "header.h"

/*

423. 从英文中重建数字

给你一个字符串 s ，其中包含字母顺序打乱的用英文单词表示的若干数字（0-9）
按 升序 返回原始的数字

示例 1：
输入：s = "owoztneoer"
输出："012"

示例 2：
输入：s = "fviefuro"
输出："45"

提示：
1 <= s.length <= 10^5
s[i] 为 ["e","g","f","i","h","o","n","s","r","u","t","w","v","x","z"] 这些字符之一
s 保证是一个符合题目要求的字符串

*/

class Solution {
public:
	vector<string> ss{ "zero", "one", "two",   "three", "four",
		"five", "six", "seven", "eight", "nine" };
	vector<int> priority{ 0, 8, 6, 3, 2, 7, 5, 9, 4, 1 };
	string originalDigits(string s) {
		int len = s.size();
		int cnts[26] = {};
		for (int i = 0; i < len; ++i) ++cnts[s[i] - 'a'];
		string ans;
		for (int p : priority) {
			int k = INT_MAX;
			for (char c : ss[p]) k = min(k, cnts[c - 'a']);
			for (char c : ss[p]) cnts[c - 'a'] -= k;
			while (k-- > 0) ans += (p + '0');
		}
		sort(ans.begin(), ans.end());
		return ans;
	}
};
// https://leetcode.cn/problems/reconstruct-original-digits-from-english/solutions/1118849/gong-shui-san-xie-nao-jin-ji-zhuan-wan-m-vg7a/
// @author https://leetcode.cn/u/ac_oier/


