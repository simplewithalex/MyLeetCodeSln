#include "header.h"

/*

给出集合 [1,2,3,…,n]，其所有元素共有 n! 种排列。
按大小顺序列出所有排列情况，并一一标记，当 n = 3 时, 所有排列如下：
"123"
"132"
"213"
"231"
"312"
"321"
给定 n 和 k，返回第 k 个排列。

说明：
给定 n 的范围是 [1, 9]。
给定 k 的范围是 [1,n!]。

示例 1:
输入: n = 3, k = 3
输出: "213"

示例 2:
输入: n = 4, k = 9
输出: "2314"

*/

class Solution1 {
public:
	string getPermutation(int n, int k) 
	{
		vector<bool> used(n, false);
		string res;
		dfs(n, k, 0, used, res);
		return res;
	}
	void dfs(int n, int k, int count, vector<bool> &used, string &res)
	{
		if (count == n)
		{
			return;
		}
		int fc = factorial(n - count - 1);
		for (int i = 0; i < n; ++i)
		{
			if (used[i]) continue;
			if (fc < k)
			{
				k -= fc;
				continue;
			}
			res += to_string(i + 1);
			used[i] = true;
			dfs(n, k, count + 1, used, res);
		}

	}
	int factorial(int n)
	{
		int res = 1;
		while (n > 0)
		{
			res *= n;
			--n;
		}
		return res;
	}
};
//https://leetcode-cn.com/problems/permutation-sequence/solution/hui-su-jian-zhi-python-dai-ma-java-dai-ma-by-liwei/

class Solution2 {
public:
	string getPermutation(int n, int k)
	{
		vector<int> v;
		string res;
		int base = 1;
		for (int i = 1; i <= n; ++i)
		{
			v.push_back(i);
			base *= i;
		}
		for (int i = 0, j = k - 1; i < n; ++i)
		{
			base /= n - i;
			int index = j / base;
			res += to_string(v[index]);
			v.erase(v.begin() + index);
			j -= base*index;
		}
		return res;
	}
};
//https://leetcode.com/problems/permutation-sequence/discuss/22507/%22Explain-like-I'm-five%22-Java-Solution-in-O(n)