#include "header.h"

/*

828. ͳ���Ӵ��е�Ψһ�ַ�

���Ƕ�����һ������ countUniqueChars(s) ��ͳ���ַ��� s �е�Ψһ�ַ���������Ψһ�ַ��ĸ���

���磺s = "LEETCODE" �������� "L", "T","C","O","D" ����Ψһ�ַ�����Ϊ����ֻ����һ�Σ����� countUniqueChars(s) = 5

���⽫�����һ���ַ��� s ��������Ҫ���� countUniqueChars(t) ���ܺͣ����� t �� s �����ַ���

����������֤����ֵΪ 32 λ����

ע�⣬ĳЩ���ַ����������ظ��ģ�����ͳ��ʱҲ����������Щ�ظ������ַ�����Ҳ����˵�������ͳ�� s ���������ַ����е�Ψһ�ַ���

ʾ�� 1��
����: s = "ABC"
���: 10
����: ���п��ܵ��Ӵ�Ϊ��"A","B","C","AB","BC" �� "ABC"��
���У�ÿһ���Ӵ����ɶ����ַ����ɡ�
�����䳤���ܺ�Ϊ��1 + 1 + 1 + 2 + 2 + 3 = 10

ʾ�� 2��
����: s = "ABA"
���: 8
����: ���� countUniqueChars("ABA") = 1 ֮�⣬������ʾ�� 1 ��ͬ

ʾ�� 3��
���룺s = "LEETCODE"
�����92

��ʾ��
1 <= s.length <= 10^5
s ֻ������дӢ���ַ�

*/


// ���仯����
class Solution1 {
public:
	vector<int> last0;
	vector<int> last1;
	vector<int> memo;
	int uniqueLetterString(string s) {
		int len = s.size();
		memo.resize(len, -1);
		last0.resize(26, -1);
		last1.resize(26, -1);
		int ans = 0;
		for (int i = 0; i < len; ++i) {
			ans += helper(s, i);
		}
		return ans;
	}
	int helper(const string &s, int idx) {
		if (idx < 0) return 0;
		if (memo[idx] != -1) return memo[idx];
		char c = s[idx] - 'A';
		memo[idx] = helper(s, idx - 1) + idx - 2 * last0[c] + last1[c];
		last1[c] = last0[c];
		last0[c] = idx;
		return memo[idx];
	}
};

// �Ե׶��϶�̬�滮
class Solution2 {
public:
	int uniqueLetterString(string s) {
		vector<int> last0(26, -1);
		vector<int> last1(26, -1);
		int len = s.size();
		int ans = 0, cur = 0;
		for (int i = 0; i < len; ++i) {
			char c = s[i] - 'A';
			cur += i - 2 * last0[c] + last1[c];
			ans += cur;
			last1[c] = last0[c];
			last0[c] = i;
		}
		return ans;
	}
};

// https://leetcode.cn/problems/count-unique-characters-of-all-substrings-of-a-given-string/solutions/1804144/by-endlesscheng-ko4z/
// @author https://leetcode.cn/u/endlesscheng/

