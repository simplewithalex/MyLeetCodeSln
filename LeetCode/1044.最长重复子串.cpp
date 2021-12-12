#include "header.h"

/*

给出一个字符串 S，考虑其所有重复子串（S 的连续子串，出现两次或多次，可能会有重叠）。

返回任何具有最长可能长度的重复子串。（如果 S 不含重复子串，那么答案为 ""）

示例 1：
输入："banana"
输出："ana"

示例 2：
输入："abcd"
输出：""

提示：
2 <= S.length <= 10^5
S 由小写英文字母组成。

*/


// 后缀法(easy but TLE)
class Solution1 {
public:
	string longestDupSubstring(string s) {
		string res;
		vector<string> strs;
		int len = s.size();
		for (int i = 0; i < len; ++i) strs.push_back(s.substr(i));
		sort(strs.begin(), strs.end());
		for (int i = 0; i < len - 1; ++i) {
			getCommon(strs[i], strs[i + 1], res);
		}
		return res;
	}

private:
	void getCommon(const string &s1, const string &s2, string &res) {
		int idx = 0;
		while (idx < s1.size() && idx < s2.size()) {
			if (s1[idx] != s2[idx]) break;
			++idx;
		}
		string tmp = s1.substr(0, idx);
		if (tmp.size() > res.size()) res = tmp;
	}
};

// Rabin-Karp 字符串编码
class Solution2 {
public:
	string longestDupSubstring(string s) {
		int len = s.size();
		vector<int> nums;
		for (int i = 0; i < len; ++i) nums.push_back(s[i] - 'a');
		const int cnt = 26;
		// 假设重复字符串最短是1, 最长是len - 1, 二分查找
		int lo = 1, hi = len - 1;
		while (lo < hi) {
			int subLen = lo + (hi - lo + 1) / 2;
			if (searchCommon(subLen, cnt, len, nums, s) != -1) {
				lo = subLen;
			}
			else {
				hi = subLen - 1;
			}
		}
		int start = searchCommon(lo, cnt, len, nums, s);
		return start != -1 ? s.substr(start, lo) : "";
	}

private:
	int searchCommon(int subLen, int cnt, int len, vector<int> &nums, const string &s) {
		const int prime = pow(10, 9) + 7;
		long long RK = 0;
		for (int i = 0; i < subLen; ++i) RK = (RK * cnt + nums[i]) % prime;
		unordered_map<long long, vector<int>> m;
		m[RK] = vector<int>(1, 0);
		long long aL = 1;
		for (int i = 0; i < subLen; ++i) aL = (aL * cnt) % prime;
		for (int start = 1; start < len - subLen + 1; ++start) {
			RK = (RK * cnt - nums[start - 1] * aL % prime + prime) % prime;
			RK = (RK + nums[start + subLen - 1]) % prime;
			if (m.count(RK)) {
				for (auto it : m[RK]) {
					if (s.substr(it, subLen) == s.substr(start, subLen)) {
						return start;
					}
				}
				m[RK].push_back(start);
			}
			else {
				m[RK] = vector<int>(1, start);
			}
		}
		return -1;
	}
};