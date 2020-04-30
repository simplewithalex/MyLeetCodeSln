#include "header.h"

/*

给定一个字符串 s1，我们可以把它递归地分割成两个非空子字符串，从而将其表示为二叉树。

下图是字符串 s1 = "great" 的一种可能的表示形式。
      great
     /    \
    gr    eat
   / \    /  \
  g   r  e   at
            / \
           a   t
在扰乱这个字符串的过程中，我们可以挑选任何一个非叶节点，然后交换它的两个子节点。

例如，如果我们挑选非叶节点 "gr" ，交换它的两个子节点，将会产生扰乱字符串 "rgeat" 。

      rgeat
     /    \
    rg    eat
   / \    /  \
  r   g  e   at
             / \
            a   t
我们将 "rgeat” 称作 "great" 的一个扰乱字符串。

同样地，如果我们继续交换节点 "eat" 和 "at" 的子节点，将会产生另一个新的扰乱字符串 "rgtae" 。

        rgtae
       /    \
      rg    tae
     / \    /  \
    r   g  ta   e
           / \
          t   a
我们将 "rgtae” 称作 "great" 的一个扰乱字符串。

给出两个长度相等的字符串 s1 和 s2，判断 s2 是否是 s1 的扰乱字符串。

示例 1:
输入: s1 = "great", s2 = "rgeat"
输出: true

示例 2:
输入: s1 = "abcde", s2 = "caebd"
输出: false

*/

class Solution {
public:
	bool isScramble(string s1, string s2)
	{
		unordered_map<string, bool> m;
		return isScrambleRecur(s1, s2, m);
	}
	bool isScrambleRecur(string s1, string s2, unordered_map<string, bool> &m)
	{
		if (m.count(s1 + '#' + s2))
		{
			if (m[s1 + '#' + s2])
				return true;
			else
				return false;
		}
		if (s1 == s2)
		{
			m[s1 + '#' + s2] = true;
			return true;
		}
		vector<int> count(26, 0);
		int len = s1.size();
		for (int i = 0; i < len; ++i)
		{
			++count[s1[i] - 'a'];
			--count[s2[i] - 'a'];
		}
		for (int i = 0; i < 26; ++i)
		{
			if (count[i] != 0)
			{
				m[s1 + '#' + s2] = false;
				return false;
			}
		}
		for (int i = 1; i < len; ++i)
		{
			if (isScrambleRecur(s1.substr(0, i), s2.substr(0, i), m) && isScrambleRecur(s1.substr(i), s2.substr(i), m))
			{
				m[s1 + '#' + s2] = true;
				return true;
			}
			if (isScrambleRecur(s1.substr(0, i), s2.substr(len - i), m) && isScrambleRecur(s1.substr(i), s2.substr(0, len - i), m))
			{
				m[s1 + '#' + s2] = true;
				return true;
			}
		}
		m[s1 + '#' + s2] = false;
		return false;
	}
};
//https://leetcode.wang/leetCode-87-Scramble-String.html