#include "header.h"

/*

给定一个只包含 '(' 和 ')' 的字符串，找出最长的包含有效括号的子串的长度。

示例 1:
输入: "(()"
输出: 2
解释: 最长有效括号子串为 "()"

示例 2:
输入: ")()())"
输出: 4
解释: 最长有效括号子串为 "()()"

*/

//使用栈
class Solution1 {
public:
	int longestValidParentheses(string s)
	{
		int len = s.size(), maxNum = 0;
		stack<int> sta;
		for (int i = 0; i < len; ++i)
		{
			if (s[i] == '(') sta.push(i);
			else
			{
				if (!sta.empty())
				{
					if (s[sta.top()] == '(') sta.pop();
					else sta.push(i);
				}
				else
				{
					sta.push(i);
				}
			}
		}
		if (sta.empty())
			maxNum = len;
		else
		{
			int ahead = 0, behind = len;
			while (!sta.empty())
			{
				ahead = sta.top();
				sta.pop();
				maxNum = max(maxNum, behind - ahead - 1);
				behind = ahead;
			}
			maxNum = max(maxNum, ahead);
		}
		return maxNum;
	}
};
//https://leetcode.com/problems/longest-valid-parentheses/discuss/14126/My-O(n)-solution-using-a-stack

//常数空间复杂度
class Solution2 {
public:
	int longestValidParentheses(string s)
	{
		return helper(s, '(', ')');
	}
	int helper(string &s, char openParen, char closeParen)
	{
		int left = 0, right = 0, maxLength = 0;
		int len = s.size();
		for (int i = 0; i < len; ++i)
		{
			if (s[i] == openParen) ++left;
			else ++right;
			if (left == right) maxLength = max(maxLength, right * 2);
			else if (right > left) left = right = 0;
		}
		//从右到左的情况
		reverse(s.begin(), s.end());
		if (openParen == '(') maxLength = max(maxLength, helper(s, ')', '('));
		return maxLength;
	}
};
