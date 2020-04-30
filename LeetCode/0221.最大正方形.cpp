#include "header.h"

/*

在一个由 0 和 1 组成的二维矩阵内，找到只包含 1 的最大正方形，并返回其面积。

示例:

输入:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

输出: 4

*/

//暴力搜索法
//首先向下移动，找到下一行是否都为一，再向右移动，找到下一列是否都为一，逐步构建最大正方形
class Solution1 {
public:
	int maximalSquare(vector<vector<char>> &matrix) 
	{
		if (matrix.empty() || matrix[0].empty()) return 0;
		int rows = matrix.size(), cols = matrix[0].size();
		int maxEdgeLen = 0;
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if (matrix[i][j] == '1')
				{
					int tempLen = 1;
					bool flag = true;
					while (i + tempLen < rows&&j + tempLen < cols&&flag)
					{
						for (int k = j; k <= j + tempLen; ++k)
						{
							if (matrix[i + tempLen][k] == '0')
							{
								flag = false;
								break;
							}
						}
						for (int k = i; k <= i + tempLen; ++k)
						{
							if (matrix[k][j + tempLen] == '0')
							{
								flag = false;
								break;
							}
						}
						if (flag) ++tempLen;
					}
					maxEdgeLen = max(maxEdgeLen, tempLen);
				}
			}
		}
		return maxEdgeLen*maxEdgeLen;
	}
};


//动态规划
class Solution2 {
public:
	int maximalSquare(vector<vector<char>> &matrix)
	{
		if (matrix.empty() || matrix[0].empty()) return 0;
		int rows = matrix.size(), cols = matrix[0].size();
		vector<vector<int>> dp(rows + 1, vector<int>(cols + 1, 0));
		int maxEdgeLen = 0;
		for (int i = 1; i <= rows; ++i)
		{
			for (int j = 1; j <= cols; ++j)
			{
				if (matrix[i - 1][j - 1] == '1')
				{
					dp[i][j] = min(min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]) + 1;
					maxEdgeLen = max(maxEdgeLen, dp[i][j]);
				}
			}
		}
		return maxEdgeLen*maxEdgeLen;
	}
};

//优化为一维动态规划数组
class Solution3 {
public:
	int maximalSquare(vector<vector<char>> &matrix)
	{
		if (matrix.empty() || matrix[0].empty()) return 0;
		int rows = matrix.size(), cols = matrix[0].size();
		vector<int> dp(cols + 1);
		int maxEdgeLen = 0;
		int prev = 0;
		for (int i = 1; i <= rows; ++i)
		{
			for (int j = 1; j <= cols; ++j)
			{
				int temp = dp[j];
				if (matrix[i - 1][j - 1] == '1')
				{
					dp[j] = min(min(dp[j - 1], dp[j]), prev) + 1;
					maxEdgeLen = max(maxEdgeLen, dp[j]);
				}
				else
				{
					dp[j] = 0;
				}
				prev = temp;
			}
		}
		return maxEdgeLen*maxEdgeLen;
	}
};

//https://leetcode-cn.com/problems/maximal-square/solution/zui-da-zheng-fang-xing-by-leetcode/
//注意这个题解中dp的图有错误，我们创建的dp矩阵的行列是rows+1与cols+1，而不是rows和cols，这个解答辅助理解就好