#include "header.h"

/*

316. ȥ���ظ���ĸ

����һ���ַ���s������ȥ���ַ������ظ�����ĸ��ʹ��ÿ����ĸֻ����һ��
�豣֤ ���ؽ�����ֵ�����С��Ҫ���ܴ��������ַ������λ�ã�

ʾ�� 1��
���룺s = "bcabc"
�����"abc"

ʾ�� 2��
���룺s = "cbacdcbc"
�����"acdb"

��ʾ��
1 <= s.length <= 104
s ��СдӢ����ĸ���

ע�⣺������ 1081 https://leetcode-cn.com/problems/smallest-subsequence-of-distinct-characters ��ͬ

*/

// ����ջ
class Solution {
public:
	string removeDuplicateLetters(string s) {
		vector<char> stk;
		vector<char> inStk(26, false);
		vector<int> count(26, 0);
		for (char c : s) ++count[c - 'a'];
		for (char c : s) {
			--count[c - 'a'];
			if (inStk[c - 'a']) continue;
			while (!stk.empty() && stk.back() > c) {
				if (!count[stk.back() - 'a']) break;
				inStk[stk.back() - 'a'] = false;
				stk.pop_back();
			}
			stk.push_back(c);
			inStk[c - 'a'] = true;
		}
		return string(stk.begin(), stk.end());
	}
};

// https://leetcode.cn/problems/remove-duplicate-letters/solutions/417758/you-qian-ru-shen-dan-diao-zhan-si-lu-qu-chu-zhong-/
// https://leetcode.cn/u/labuladong/
