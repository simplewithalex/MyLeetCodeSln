#include "header.h"

/*

编写一个高效的算法来判断 m x n 矩阵中，是否存在一个目标值。该矩阵具有如下特性：
每行中的整数从左到右按升序排列。
每行的第一个整数大于前一行的最后一个整数。

示例 1:
输入:
matrix = [
[1,   3,  5,  7],
[10, 11, 16, 20],
[23, 30, 34, 50]
]
target = 3
输出: true

示例 2:
输入:
matrix = [
[1,   3,  5,  7],
[10, 11, 16, 20],
[23, 30, 34, 50]
]
target = 13
输出: false

*/

class Solution {
public:
	bool searchMatrix(vector<vector<int>> &matrix, int target)
	{
		if (matrix.empty()) return false;
		int rows = matrix.size();
		int cols = matrix[0].size();
		int lo = 0, hi = rows*cols;
		while (lo < hi)
		{
			int mi = (lo + hi) >> 1;
			(target < matrix[mi/cols][mi%cols]) ? hi = mi : lo = mi + 1;
		}
		lo -= 1;
		return lo < 0 ? false : matrix[lo/cols][lo%cols] == target;
	}
};