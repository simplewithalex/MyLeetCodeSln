#include "header.h"

/*

639. 解码方法 II

一条包含字母 A-Z 的消息通过以下的方式进行了 编码 ：

'A' -> "1"
'B' -> "2"
...
'Z' -> "26"

要解码一条已编码的消息，所有的数字都必须分组，然后按原来的编码方案反向映射回字母（可能存在多种方式）

例如，"11106" 可以映射为：
"AAJF" 对应分组 (1 1 10 6)
"KJF" 对应分组 (11 10 6)

注意，像 (1 11 06) 这样的分组是无效的，因为 "06" 不可以映射为 'F' ，因为 "6" 与 "06" 不同

除了 上面描述的数字字母映射方案，编码消息中可能包含 '*' 字符，可以表示从 '1' 到 '9' 的任一数字（不包括 '0'）
例如，编码字符串 "1*" 可以表示 "11"、"12"、"13"、"14"、"15"、"16"、"17"、"18" 或 "19" 中的任意一条消息
对 "1*" 进行解码，相当于解码该字符串可以表示的任何编码消息

给你一个字符串 s ，由数字和 '*' 字符组成，返回 解码 该字符串的方法 数目
由于答案数目可能非常大，返回 10^9 + 7 的 模

示例 1：
输入：s = "*"
输出：9
解释：这一条编码消息可以表示 "1"、"2"、"3"、"4"、"5"、"6"、"7"、"8" 或 "9" 中的任意一条
可以分别解码成字符串 "A"、"B"、"C"、"D"、"E"、"F"、"G"、"H" 和 "I"
因此，"*" 总共有 9 种解码方法

示例 2：
输入：s = "1*"
输出：18
解释：这一条编码消息可以表示 "11"、"12"、"13"、"14"、"15"、"16"、"17"、"18" 或 "19" 中的任意一条
每种消息都可以由 2 种方法解码（例如，"11" 可以解码成 "AA" 或 "K"）
因此，"1*" 共有 9 * 2 = 18 种解码方法

示例 3：
输入：s = "2*"
输出：15
解释：这一条编码消息可以表示 "21"、"22"、"23"、"24"、"25"、"26"、"27"、"28" 或 "29" 中的任意一条
"21"、"22"、"23"、"24"、"25" 和 "26" 由 2 种解码方法，但 "27"、"28" 和 "29" 仅有 1 种解码方法
因此，"2*" 共有 (6 * 2) + (3 * 1) = 12 + 3 = 15 种解码方法

提示：
1 <= s.length <= 10^5
s[i] 是 0 - 9 中的一位数字或字符 '*'

*/


// 记忆化搜索
class Solution1 {
public:
	const int MOD = 1E9 + 7;
	vector<int> memo;
	int numDecodings(string s) {
		int len = s.size();
		memo.resize(len + 1, -1);
		return helper(s, len);
	}
	long long helper(const string &s, int idx) {
		if (idx == 0) return 1;
		if (idx == 1) {
			if (s[idx - 1] == '*') return 9;
			if (s[idx - 1] == '0') return 0;
			return 1;
		}
		if (memo[idx] != -1) return memo[idx];
		long long ans = 0;

		// 选择 1 个数字作编码
		if (s[idx - 1] == '0') ans += 0;
		else if (s[idx - 1] == '*') ans += 9 * helper(s, idx - 1);
		else ans += helper(s, idx - 1);
		// 选择 2 个数字作编码，讨论情况时注意编码是 1 - 26，舍去无效值
		// 另外注意题目中 '*' 可以表示的数字不包括 0
		if (s[idx - 2] == '0') {
			ans += 0;
		} else if (s[idx - 2] == '*' && s[idx - 1] == '*') {
			ans += 15 * helper(s, idx - 2);
		} else if (s[idx - 2] == '*') {
			if (s[idx - 1] >= '0' && s[idx - 1] <= '6') ans += 2 * helper(s, idx - 2);
			if (s[idx - 1] >= '7' && s[idx - 1] <= '9') ans += helper(s, idx - 2);
		} else if (s[idx - 1] == '*') {
			if (s[idx - 2] == '1') ans += 9 * helper(s, idx - 2);
			if (s[idx - 2] == '2') ans += 6 * helper(s, idx - 2);
		} else {
			int num = (s[idx - 2] - '0') * 10 + (s[idx - 1] - '0');
			if (num >= 10 && num <= 26) ans += helper(s, idx - 2);
		}
		return memo[idx] = ans % MOD;
	}
};

// 自底而上动态规划
class Solution2 {
public:
	const int MOD = 1E9 + 7;
	int numDecodings(string s) {
		int len = s.size();
		vector<long long> dp(len + 1, 1);
		if (s[0] == '*') dp[1] = 9;
		else if (s[0] == '0') dp[1] = 0;
		else dp[1] = 1;
		for (int i = 2; i <= len; ++i) {
			long long ans = 0;
			if (s[i - 1] == '0') ans += 0;
			else if (s[i - 1] == '*') ans += 9 * dp[i - 1];
			else ans += dp[i - 1];
			if (s[i - 2] == '0') {
				ans += 0;
			} else if (s[i - 2] == '*' && s[i - 1] == '*') {
				ans += 15 * dp[i - 2];
			} else if (s[i - 2] == '*') {
				if (s[i - 1] >= '0' && s[i - 1] <= '6') ans += 2 * dp[i - 2];
				if (s[i - 1] >= '7' && s[i - 1] <= '9') ans += dp[i - 2];
			} else if (s[i - 1] == '*') {
				if (s[i - 2] == '1') ans += 9 * dp[i - 2];
				else if (s[i - 2] == '2') ans += 6 * dp[i - 2];
			} else {
				int num = (s[i - 2] - '0') * 10 + (s[i - 1] - '0');
				if (num >= 10 && num <= 26) ans += dp[i - 2];
			}
			dp[i] = ans % MOD;
		}
		return dp[len];
	}
};

// 还可以再优化空间复杂度，取消数组

