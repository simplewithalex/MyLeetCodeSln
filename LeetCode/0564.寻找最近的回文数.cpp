#include "header.h"

/*

564. 寻找最近的回文数

给定一个表示整数的字符串 n，返回与它最近的回文整数（不包括自身）。如果不止一个，返回较小的那个

“最近的”定义为两个整数差的绝对值最小

示例 1:
输入: n = "123"
输出: "121"

示例 2:
输入: n = "1"
输出: "0"
解释: 0 和 2 是最近的回文，但我们返回最小的，也就是 0

提示:
1 <= n.length <= 18
n 只由数字组成
n 不含前导 0
n 代表在 [1, 10^18 - 1] 范围内的整数

*/

class Solution {
public:
	string nearestPalindromic(string n) {
		unsigned long long num = stoll(n), ans = -1;
		const vector<unsigned long long> candidates = getCandidates(n);
		for (auto &candidate : candidates) {
			if (candidate != num) {
				if (ans == -1 || llabs(candidate - num) < llabs(ans - num) ||
					(llabs(candidate - num) == llabs(ans - num) &&
						candidate < ans)) {
					ans = candidate;
				}
			}
		}
		return to_string(ans);
	}
	vector<unsigned long long> getCandidates(const string &n) {
		int len = n.size();
		vector<unsigned long long> candidates = {
			(unsigned long long)pow(10, len - 1) - 1,
			(unsigned long long)pow(10, len) + 1 };
		unsigned long long prefix = stoull(n.substr(0, (len + 1) / 2));
		for (int num : {prefix - 1, prefix, prefix + 1}) {
			string p = to_string(num);
			string candidate = p + string(p.rbegin() + (len & 1), p.rend());
			candidates.push_back(stoll(candidate));
		}
		return candidates;
	}
};

