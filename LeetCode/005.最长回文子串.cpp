#include "header.h"

/*

给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。

示例 1：
输入: "babad"
输出: "bab"
注意: "aba" 也是一个有效答案。

示例 2：
输入: "cbbd"
输出: "bb"

*/

//中心扩展法
class Solution1 {
public:
	string longestPalindrome(string s)
	{
		int maxNum = 0, idx = 0;
		for (int i = 0; i < s.size(); ++i)
		{
			int len1 = extend(s, i, i), len2 = extend(s, i, i + 1);
			if (maxNum < max(len1, len2))
			{
				idx = (len1>len2) ? (i - len1 / 2) : (i - len2 / 2 + 1);
				maxNum = max(len1, len2);
			}
		}
		return s.substr(idx, maxNum);
	}
	int extend(const string &s, int i, int j)
	{
		for (; i >= 0 && j < s.size(); --i, ++j)
			if (s[i] != s[j])
				break;
		return j - i - 1;
	}
};

//Manacher算法（技巧性）
class Solution2 {
public:
	string longestPalindrome(string s)
	{
		int len = s.size();
		if (len < 2) return s;
		string str = preProcess(s);
		len = str.size();
		//pal以记录每个下标为中心的回文串单侧长度
		vector<int> pal(len);
		//双指针分别记录回文子串中心点和右侧最远下标
		int center = 0, maxRight = 0;
		//记录最长字符串起始位置
		int start = 0;
		//记录最长长度
		int maxLen = 1;
		for (int i = 0; i < len; ++i)
		{
			if (i < maxRight)
			{
				int mirror = 2 * center - i;
				pal[i] = min(maxRight - i, pal[mirror]);
			}
			//下一次扩散的左右起点
			int left = i - (1 + pal[i]);
			int right = i + (1 + pal[i]);
			while (left >= 0 && right < len&&str[left] == str[right])
			{
				++pal[i];
				--left;
				++right;
			}
			if ((i + pal[i])>maxRight)
			{
				maxRight = i + pal[i];
				center = i;
			}
			if (pal[i] > maxLen)
			{
				maxLen = pal[i];
				start = (i - maxLen) / 2;
			}
		}
		return s.substr(start, maxLen);
	}
	string preProcess(const string &s)
	{
		int len = s.size();
		string res;
		for (int i = 0; i < len; ++i) res.append({ '#', s[i] });
		res += "#";
		return res;
	}
};
//https://zhuanlan.zhihu.com/p/88299272