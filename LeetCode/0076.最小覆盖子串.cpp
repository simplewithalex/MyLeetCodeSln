#include "header.h"

/*

给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字母的最小子串。

示例：
输入: S = "ADOBECODEBANC", T = "ABC"
输出: "BANC"

说明：
如果 S 中不存这样的子串，则返回空字符串 ""。
如果 S 中存在这样的子串，我们保证它是唯一的答案。

*/

//003,076,438属于同一类型的题目
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
