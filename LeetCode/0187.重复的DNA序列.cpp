#include "header.h"

/*

187. 重复的DNA序列

所有 DNA 都由一系列缩写为 'A'，'C'，'G' 和 'T' 的核苷酸组成，例如："ACGAATTCCG"。在研究 DNA 时，识别 DNA 中的重复序列有时会对研究非常有帮助。

编写一个函数来找出所有目标子串，目标子串的长度为 10，且在 DNA 字符串 s 中出现次数超过一次。

示例 1：
输入：s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
输出：["AAAAACCCCC","CCCCCAAAAA"]

示例 2：
输入：s = "AAAAAAAAAAAAA"
输出：["AAAAAAAAAA"]

提示：
0 <= s.length <= 10^5
s[i] 为 'A'、'C'、'G' 或 'T'

*/

// 哈希表
class Solution1 {
public:
	vector<string> findRepeatedDnaSequences(string s) {
		const int C = 10;
		vector<string> res;
		int len = s.size();
		unordered_map<string, int> m;
		for (int i = 0; i + C - 1 < len; ++i) {
			string cur = s.substr(i, C);
			if (m[cur] == 1) res.push_back(cur);
			m[cur] += 1;
		}
		return res;
	}
};

// 滑动窗口 + 哈希 + 位运算
class Solution2 {
public:
	vector<string> findRepeatedDnaSequences(string s) {
		const int C = 10;
		unordered_map<char, int> bin = { { 'A', 0 },{ 'C', 1 },{ 'G', 2 },{ 'T', 3 } };
		vector<string> res;
		int len = s.size();
		if (len <= C) return res;
		int x = 0;
		for (int i = 0; i < C - 1; ++i) x = (x << 2) | bin[s[i]];
		unordered_map<int, int> m;
		for (int i = 0; i + C - 1 < len; ++i) {
			x = ((x << 2) | bin[s[i + C - 1]]) & ((1 << (C * 2)) - 1);
			if (m[x] == 1) res.push_back(s.substr(i, C));
			m[x] += 1;
		}
		return res;
	}
};
// https://leetcode-cn.com/problems/repeated-dna-sequences/solution/zhong-fu-de-dnaxu-lie-by-leetcode-soluti-z8zn/


// Rabin-Karp 字符串编码
class Solution3 {
public:
	vector<string> findRepeatedDnaSequences(string s) {
		const int C = 10;
		const int len = s.size();
		if (len < C) return{};
		vector<int> nums;
		unordered_map<long long, vector<int>> m;
		for (int i = 0; i < len; ++i) nums.push_back(s[i] - 'A');
		setCL(C);
		unordered_set<long long> selectRK;
		for (int i = 0; i < C; ++i) RK = (RK * cnt + nums[i]) % prime;
		m[RK] = vector<int>(1, 0);
		for (int i = 1; i + C - 1 < len; ++i) {
			RK = hashRK(C, nums, i);
			if (m.count(RK)) {
				m[RK].push_back(i);
				selectRK.insert(RK);
			}
			else {
				m[RK] = vector<int>(1, i);
			}
		}
		return check(selectRK, m, s, C);
	}

private:
	const int prime = pow(10, 9) + 7;
	const int cnt = 26;
	long long RK = 0;
	long long cL = 1;
	void setCL(const int subLen) {
		for (int i = 0; i < subLen; ++i) {
			cL = (cL * cnt) % prime;
		}
	}
	long long hashRK(const int subLen, vector<int> &nums, int idx) {
		RK = (RK * cnt - nums[idx - 1] * cL % prime + prime) % prime;
		RK = (RK + nums[idx + subLen - 1]) % prime;
		return RK;
	}
	vector<string> check(unordered_set<long long> &selectRK, unordered_map<long long, vector<int>> &m, const string &s, const int C) {
		vector<string> res;
		unordered_map<string, int> nums;
		for (auto it = selectRK.cbegin(); it != selectRK.cend(); ++it) {
			for (int i : m[*it]) ++nums[s.substr(i, C)];
		}
		for (auto it = nums.cbegin(); it != nums.cend(); ++it) {
			if (it->second > 1) res.push_back(it->first);
		}
		return res;
	}
};