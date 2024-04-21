#include "header.h"

/*

420. 强密码检验器

满足以下条件的密码被认为是强密码：

由至少 6 个，至多 20 个字符组成
包含至少一个小写字母，至少一个大写字母，和至少一个数字
不包含连续三个重复字符(比如 "Baaabb0" 是弱密码, 但是 "Baaba0" 是强密码)
给你一个字符串password，返回将password修改到满足强密码条件需要的最少修改步数。如果 password 已经是强密码，则返回 0

在一步修改操作中，你可以：
插入一个字符到 password，从 password 中删除一个字符，或用另一个字符来替换 password 中的某个字符

示例 1：
输入：password = "a"
输出：5

示例 2：
输入：password = "aA1"
输出：3

示例 3：
输入：password = "1337C0d3"
输出：0

提示：
1 <= password.length <= 50
password 由字母、数字、点 '.' 或者感叹号 '!' 组成

*/

class Solution {
public:
	int strongPasswordChecker(string password) {
		int A = 0, B = 0, C = 0;
		for (char c : password) {
			if (c >= 'a' && c <= 'z') A = 1;
			else if (c >= '0' && c <= '9') B = 1;
			else if (c >= 'A' && c <= 'Z') C = 1;
		}
		int m = A + B + C;
		int len = password.size();
		if (len < 6) {
			return max(6 - len, 3 - m);
		} else if (len <= 20) {
			int rep = 0;
			int i = 0;
			while (i < len) {
				int j = i;
				while (j < len && password[j] == password[i]) ++j;
				int cnt = j - i;
				if (cnt >= 3) rep += cnt / 3;
				i = j;
			}
			return max(rep, 3 - m);
		} else {
			int rep = 0;
			vector<int> remainders(3);
			int i = 0;
			while (i < len) {
				int j = i;
				while (j < len && password[j] == password[i]) ++j;
				int cnt = j - i;
				if (cnt >= 3) {
					rep += cnt / 3;
					++remainders[cnt % 3];
				}
				i = j;
			}
			int base = len - 20, cur = base;
			for (int i = 0; i < 3; ++i) {
				if (i == 2) remainders[i] = rep;
				if (remainders[i] && cur) {
					int del = min(remainders[i] * (i + 1), cur);
					cur -= del;
					rep -= del / (i + 1);
				}
			}
			return base + max(rep, 3 - m);
		}
	}
};
// https://leetcode.cn/problems/strong-password-checker/solutions/1387891/by-ac_oier-unp5/comments/2272696
// @author https://leetcode.cn/u/nice-pike0sm/

