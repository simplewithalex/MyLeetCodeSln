#include "header.h"

/*

给定一个包含 m x n 个元素的矩阵（m 行, n 列），请按照顺时针螺旋顺序，返回矩阵中的所有元素。

示例 1:
输入:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
输出: [1,2,3,6,9,8,7,4,5]

示例 2:
输入:
[
 [1, 2, 3, 4],
 [5, 6, 7, 8],
 [9,10,11,12]
]
输出: [1,2,3,4,8,12,11,10,9,5,6,7]


*/

class Solution {
public:
	vector<int> spiralOrder(vector<vector<int>> &matrix)
	{
		if (matrix.empty() || matrix[0].empty()) return{};
		vector<int> res;
		int rows = matrix.size(), cols = matrix[0].size();
		int startRow = 0, endRow = rows - 1, startCol = 0, endCol = cols - 1;
		while (startRow <= endRow&&startCol <= endCol)
		{
			for (int i = startCol; i <= endCol; ++i)
			{
				res.push_back(matrix[startRow][i]);
			}
			++startRow;
			for (int i = startRow; i <= endRow; ++i)
			{
				res.push_back(matrix[i][endCol]);
			}
			--endCol;

			if (startRow > endRow || startCol > endCol) break;

			for (int i = endCol; i >= startCol; --i)
			{
				res.push_back(matrix[endRow][i]);
			}
			--endRow;
			for (int i = endRow; i >= startRow; --i)
			{
				res.push_back(matrix[i][startCol]);
			}
			++startCol;
		}
		return res;
	}
};