#include "header.h"

/*

给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。

示例:

输入: n = 4, k = 2
输出:

[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

*/

//通用的递归回溯的方法
class Solution1 {
public:
	vector<vector<int>> combine(int n, int k)
	{
		if (n <= 0) return{};
		vector<vector<int>> res;
		vector<int> vec;
		backTrack(res, vec, 1, n, k);
		return res;
	}
	void backTrack(vector<vector<int>> &res, vector<int> &vec, int index, int n, int k)
	{
		if (k == 0)
		{
			res.push_back(vec);
			return;
		}
		for (int i = index; i <= n; ++i)
		{
			vec.push_back(i);
			backTrack(res, vec, i + 1, n, k - 1);
			vec.pop_back();
		}
	}
};

//一种迭代的方法
class Solution2 {
public:
	vector<vector<int>> combine(int n, int k)
	{
		if (n <= 0) return{};
		vector<vector<int>> res;
		vector<int> com(k, 0);
		int i = 0;
		while (i >= 0)
		{
			++com[i];
			if (com[i] > n)
			{
				--i;
			}
			else if (k - 1 == i)
			{
				res.push_back(com);
			}
			else
			{
				++i;
				com[i] = com[i - 1];
			}
		}
		return res;
	}
};