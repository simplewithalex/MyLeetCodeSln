#include "header.h"

/*

424. �滻�����ظ��ַ�

����һ���ַ��� s ��һ������ k �������ѡ���ַ����е���һ�ַ������������Ϊ�κ�������дӢ���ַ����ò�������ִ�� k ��
��ִ�����������󣬷��� ������ͬ��ĸ������ַ����ĳ���

ʾ�� 1��
���룺s = "ABAB", k = 2
�����4
���ͣ�������'A'�滻Ϊ����'B',��֮��Ȼ

ʾ�� 2��
���룺s = "AABABBA", k = 1
�����4
���ͣ�
���м��һ��'A'�滻Ϊ'B',�ַ�����Ϊ "AABBBBA"
�Ӵ� "BBBB" ����ظ���ĸ, ��Ϊ 4
���ܴ��������ķ������õ�ͬ���Ľ����

��ʾ��
1 <= s.length <= 10^5
s ���ɴ�дӢ����ĸ���
0 <= k <= s.length

*/

// ��������ģ����
class Solution {
public:
	int characterReplacement(string s, int k) {
		int len = s.size();
		int start = 0, end = 0, counter = 0;
		int res = 0;
		int freq[26] = {};
		while (end < len) {
			++freq[s[end] - 'A'];
			counter = max(counter, freq[s[end] - 'A']);
			++end;
			if (end - start > counter + k) {
				--freq[s[start] - 'A'];
				++start;
			}
			res = max(res, end - start);
		}
		return res;
	}
};

