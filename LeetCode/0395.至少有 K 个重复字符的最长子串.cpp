#include "header.h"

/*

395. ������ K ���ظ��ַ�����Ӵ�

����һ���ַ��� s ��һ������ k�������ҳ� s �е���Ӵ��� Ҫ����Ӵ��е�ÿһ�ַ����ִ����������� k
������һ�Ӵ��ĳ���
������������������ַ������򷵻� 0

ʾ�� 1��
���룺s = "aaabb", k = 3
�����3
���ͣ���Ӵ�Ϊ "aaa" ������ 'a' �ظ��� 3 ��

ʾ�� 2��
���룺s = "ababbc", k = 2
�����5
���ͣ���Ӵ�Ϊ "ababb" ������ 'a' �ظ��� 2 �Σ� 'b' �ظ��� 3 ��

��ʾ��
1 <= s.length <= 10^4
s ����СдӢ����ĸ���
1 <= k <= 10^5

*/


// ʹ�� LeetCode 438 ����ģ��
class Solution1 {
public:
	int longestSubstring(string s, int k) {
		int res = 0;
		for (int uniqueNum = 1; uniqueNum <= 26; ++uniqueNum) {
			res = max(res, helper(s, k, uniqueNum));
		}
		return res;
	}

private:
	int helper(const string &s, int k, int uniqueNum) {
		int m[26] = {};
		int start = 0, end = 0;
		int len = s.size();
		int res = INT_MIN;
		// ��ͬ��ĸ������
		int counter = 0;
		// ���� k �Ĳ�ͬ��ĸ����
		int sumK = 0;
		while (end < len) {
			char c = s[end];
			++m[c - 'a'];
			if (m[c - 'a'] == 1) ++counter;
			if (m[c - 'a'] == k) ++sumK;
			++end;
			while (counter > uniqueNum) {
				c = s[start];
				--m[c - 'a'];
				if (m[c - 'a'] == 0) --counter;
				if (m[c - 'a'] == k - 1) --sumK;
				++start;
			}
			if (counter == sumK) res = max(res, end - start);
		}
		return res;
	}
};
// https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/solutions/170010/java-o-n-solution-with-detailed-explanation-sliding-window/
// @author https://leetcode.com/u/seanmsha/

class Solution2 {
public:
	int longestSubstring(string s, int k) {
		if (s.size() < k) return 0;
		unordered_set<char> chars(s.begin(), s.end());
		int counter[26] = {};
		for (char c : s) ++counter[c - 'a'];
		for (char c : chars) {
			vector<string> strs;
			if (counter[c - 'a'] < k) {
				split(s, strs, c);
				int res = 0;
				for (string str : strs) {
					res = max(res, longestSubstring(str, k));
				}
				return res;
			}
		}
		return s.size();
	}

private:
	void split(const string &s, vector<string> &strs, const char delim = ' ') {
		strs.clear();
		istringstream is(s);
		string temp;
		while (getline(is, temp, delim)) {
			strs.push_back(temp);
		}
	}
};

