#include "header.h"

/*

����һ���ַ��� S��һ���ַ��� T�������ַ��� S �����ҳ������� T ������ĸ����С�Ӵ���

ʾ����
����: S = "ADOBECODEBANC", T = "ABC"
���: "BANC"

˵����
��� S �в����������Ӵ����򷵻ؿ��ַ��� ""��
��� S �д����������Ӵ������Ǳ�֤����Ψһ�Ĵ𰸡�

*/

//003,076,438����ͬһ���͵���Ŀ
class Solution {
public:
	string minWindow(string S, string T)
	{
		vector<int> m(128, 0);
		for (auto c : T)
			++m[c];
		int count = T.size(), start = 0, end = 0;
		int minLen = INT_MAX, minStart = 0;
		while (end < S.size())
		{
			if (m[S[end]]>0) --count;
			--m[S[end]], ++end;
			while (count == 0)
			{
				if (minLen > end - start)
				{
					minLen = end - start;
					minStart = start;
				}
				if (m[S[start]] == 0) ++count;
				++m[S[start]];
				++start;
			}
		}
		return minLen == INT_MAX ? "" : S.substr(minStart, minLen);
	}
};
//https://leetcode.com/problems/minimum-window-substring/discuss/26808/Here-is-a-10-line-template-that-can-solve-most-'substring'-problems/25816
