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

提示：
m == matrix.length
n == matrix[i].length
1 <= m, n <= 300
matrix[i][j] 为 '0' 或 '1'

*/

// 暴力搜索
// C++ TLE, Java AC
class Solution1 {
public:
	int maximalSquare(vector<vector<char>> &matrix) {
		if (matrix.empty() || matrix[0].empty()) return 0;
		int rows = matrix.size(), cols = matrix[0].size();
		int maxEdgeLen = 0;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (matrix[i][j] == '1') {
					int tempLen = 1;
					bool flag = true;
					while (i + tempLen < rows && j + tempLen < cols && flag) {
						for (int k = 0; k <= tempLen; ++k) {
							if (matrix[i + tempLen][j + k] == '0' || matrix[i + k][j + tempLen] == '0') {
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
		return maxEdgeLen * maxEdgeLen;
	}
};
/**
* 遍历矩阵中的每个元素，每次遇到1，则将该元素作为正方形的左上角；
*
* 确定正方形的左上角后，根据左上角所在的行和列计算可能的最大正方形的边长（正方形的范围不能超出矩阵的行数和列数），
* 每次在下方新增一行以及在右方新增一列，判断新增的行和列是否满足所有元素都是 1；
*
*/


// 动态规划
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

// 优化为一维动态规划数组
// 行方向数组复用
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