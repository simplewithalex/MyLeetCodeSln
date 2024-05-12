#include "header.h"


/*


567. �ַ���������

���������ַ��� s1 �� s2 ��дһ���������ж� s2 �Ƿ���� s1 �����С�����ǣ����� true�����򷵻� false
���仰˵��s1 ������֮һ�� s2 ���Ӵ�

ʾ�� 1��
���룺s1 = "ab" s2 = "eidbaooo"
�����true
���ͣ�s2 ���� s1 ������֮һ ("ba")

ʾ�� 2��
���룺s1= "ab" s2 = "eidboaoo"
�����false

��ʾ��
1 <= s1.length, s2.length <= 10^4
s1 �� s2 ������Сд��ĸ

*/

// ��LeetCode 438��ͬ
class Solution {
public:
	bool checkInclusion(string s1, string s2) {
		int sLen = s2.size(), pLen = s1.size();
		if (sLen < pLen) return false;
		vector<int> res;
		vector<int> m(26, 0);
		for (auto c : s1) ++m[c - 'a'];
		int start = 0, end = 0, counter = pLen;
		while (end < sLen) {
			if (m[s2[end] - 'a'] >= 1) --counter;
			--m[s2[end] - 'a'];
			++end;
			while (counter == 0) {
				if (end - start == pLen) return true;
				if (m[s2[start] - 'a'] == 0) ++counter;
				++m[s2[start] - 'a'];
				++start;
			}
		}
		return false;
	}
};
// https://leetcode.com/problems/find-all-anagrams-in-a-string/solutions/92007/sliding-window-algorithm-template-to-solve-all-the-leetcode-substring-search-problem/
// @author https://leetcode.com/u/chaoyanghe/
