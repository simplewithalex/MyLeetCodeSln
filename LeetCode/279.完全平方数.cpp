#include "header.h"

/*

给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。
你需要让组成和的完全平方数的个数最少。

示例 1:
输入: n = 12
输出: 3
解释: 12 = 4 + 4 + 4.

示例 2:
输入: n = 13
输出: 2
解释: 13 = 4 + 9.

*/

//备忘录算法
class Solution1 {
public:
	int numSquares(int n)
	{
		if (n <= 1) return 1;
		vector<int> m(n + 1, 0);
		return dfs(n, m);
	}
	int dfs(int n, vector<int> &m)
	{
		if (m[n]) return m[n];
		int i = sqrt(n);
		if (i*i == n)
		{
			m[n] = 1;
			return 1;
		}
		int res = INT_MAX;
		for (i = 1; i*i < n; ++i)
		{
			res = min(res, dfs(n - i*i, m) + 1);
		}
		m[n] = res;
		return res;
	}
};
//https://leetcode-cn.com/problems/perfect-squares/solution/bu-zhi-shi-da-an-er-shi-dong-tai-gui-hua-lei-ti-de/

//自底而上动态规划算法
class Solution2 {
public:
	int numSquares(int n)
	{
		vector<int> dp(n + 1);
		//最坏的情况，每个数都由1构成
		for (int i = 0; i <= n; ++i)
		{
			dp[i] = i;
		}
		for (int i = 2; i <= n; ++i)
		{
			for (int j = 1; j*j <= i; ++j)
			{
				dp[i] = min(dp[i], dp[i - j*j] + 1);
			}
		}
		return dp[n];
	}
};
//https://leetcode-cn.com/problems/perfect-squares/solution/bu-zhi-shi-da-an-er-shi-dong-tai-gui-hua-lei-ti-de/

//BFS
class Solution3 {
public:
	int numSquares(int n)
	{
		if (n <= 1) return 1;
		queue<int> q;
		vector<char> m(n + 1, 0);
		q.push(0);
		int res = 0;
		m[0] = 1;
		while (!q.empty())
		{
			int len = q.size();
			for (int i = 0; i < len; ++i)
			{
				int cur = q.front();
				q.pop();
				for (int j = 1; cur + j*j <= n; ++j)
				{
					int temp = cur + j*j;
					if (temp == n) return res + 1;
					//防止数据重复出现
					if (!m[temp])
					{
						q.push(temp);
						m[temp] = 1;
					}
				}
			}
			++res;
		}
		return res;
	}
};
//https://leetcode-cn.com/problems/perfect-squares/solution/java-jie-fa-jiang-wen-ti-zhuan-hua-wei-tu-lun-by-b/

