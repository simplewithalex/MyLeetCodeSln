#include "header.h"

/*

给定一个字符串，你的任务是计算这个字符串中有多少个回文子串。
具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被计为是不同的子串。

示例 1:
输入: "abc"
输出: 3
解释: 三个回文子串: "a", "b", "c".

示例 2:
输入: "aaa"
输出: 6
解释: 6个回文子串: "a", "a", "a", "aa", "aa", "aaa".

注意:
输入的字符串长度不会超过1000。

*/

//中心扩展法
class Solution1 {
public:
	int countSubstrings(string s)
	{
		int res = 0;
		int len = s.size();
		for (int i = 0; i < len; ++i)
		{
			res += extend(s, i, i + 1) + extend(s, i, i);
		}
		return res;

	}
	int extend(const string &s, int i, int j)
	{
		int count = 0;
		for (; i >= 0 && j < s.size(); --i, ++j)
		{
			if (s[i] != s[j])
				break;
			++count;
		}
		return count;
	}
};

//动态规划
class Solution2 {
public:
	int countSubstrings(string s)
	{
		if (s.empty()) return 0;
		int len = s.size();
		vector<vector<char>> isPal(len, vector<char>(len, false));
		int res = 0;
		for (int palLen = 1; palLen <= len; ++palLen)
		{
			for (int i = 0; i <= len - palLen; ++i)
			{
				int j = i + palLen - 1;
				isPal[i][j] = (s[i] == s[j]) && (palLen < 3 || isPal[i + 1][j - 1]);
				if (isPal[i][j]) ++res;
			}
		}
		return res;
	}
};

//Manacher算法
class Solution3 {
public:
	int countSubstrings(string s)
	{
		int len = s.size();
		if (len < 2) return len;
		string str = preProcess(s);
		len = str.size();
		//pal以记录每个下标为中心的回文串单侧长度
		vector<int> pal(len);
		//双指针分别记录回文子串中心点和右侧最远下标
		int center = 0, maxRight = 0;
		//记录回文串的数量
		int res = 0;
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
			res += (pal[i] + 1) / 2;
		}
		return res;
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