#include "header.h"

/*

给定两个单词 word1 和 word2，计算出将 word1 转换成 word2 所使用的最少操作数 。
你可以对一个单词进行如下三种操作：

插入一个字符
删除一个字符
替换一个字符

示例 1:
输入: word1 = "horse", word2 = "ros"
输出: 3
解释:
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')

示例 2:
输入: word1 = "intention", word2 = "execution"
输出: 5
解释:
intention -> inention (删除 't')
inention -> enention (将 'i' 替换为 'e')
enention -> exention (将 'n' 替换为 'x')
exention -> exection (将 'n' 替换为 'c')
exection -> execution (插入 'u')

*/


//解题思路：
//https://leetcode-cn.com/problems/edit-distance/solution/zi-di-xiang-shang-he-zi-ding-xiang-xia-by-powcai-3/

//普通的递归，会超时
class Solution1 {
public:
	int minDistance(string word1, string word2)
	{
		int len1 = word1.size(), len2 = word2.size();
		if (len1 == 0)
			return len2;
		if (len2 == 0)
			return len1;
		int x = minDistance(word1, word2.substr(0, len2 - 1)) + 1;
		int y = minDistance(word1.substr(0, len1 - 1), word2) + 1;
		int z = minDistance(word1.substr(0, len1 - 1), word2.substr(0, len2 - 1));
		if (word1[len1 - 1] != word2[len2 - 1]) ++z;
		return min(min(x, y), z);
	}
};

//动态规划解法
class Solution {
public:
	int minDistance(string word1, string word2)
	{
		int len1 = word1.size(), len2 = word2.size();
		vector<int> dp(len1 + 1, 0);
		for (int i = 1; i <= len1; ++i)
		{
			dp[i] = i;
		}
		for (int j = 1; j <= len2; ++j)
		{
			int pre = dp[0];
			dp[0] = j;
			for (int i = 1; i <= len1; ++i)
			{
				int temp = dp[i];
				if (word2[j - 1] == word1[i - 1])
				{
					dp[i] = pre;
				}
				else
				{
					dp[i] = min(dp[i], min(dp[i - 1], pre)) + 1;
				}
				pre = temp;
			}
		}
		return dp[len1];
	}
};