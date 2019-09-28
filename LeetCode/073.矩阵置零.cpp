#include "header.h"

/*

给定一个 m x n 的矩阵，如果一个元素为 0，则将其所在行和列的所有元素都设为 0。
请使用原地算法。

示例 1:
输入:
[
  [1,1,1],
  [1,0,1],
  [1,1,1]
]
输出:
[
   [1,0,1],
   [0,0,0],
   [1,0,1]
]

*/

class Solution {
public:
	void setZeroes(vector<vector<int>> &matrix)
	{
		if (matrix.empty() || matrix[0].empty()) return;
		int rows = matrix.size(), cols = matrix[0].size();
		bool col0 = false;
		for (int i = 0; i < rows; ++i)
		{
			if (matrix[i][0] == 0)
				col0 = true;
			for (int j = 1; j < cols; ++j)
			{
				if (matrix[i][j] == 0)
					matrix[i][0] = matrix[0][j] = 0;
			}
		}
		for (int i = rows - 1; i >= 0; --i)
		{
			for (int j = cols - 1; j>0; --j)
			{
				if (matrix[0][j] == 0 || matrix[i][0] == 0)
					matrix[i][j] = 0;
			}
			if (col0) matrix[i][0] = 0;
		}
	}
};
//每一行的第一个元素记录此行是否应该为0，每一列的第一个元素记录此列是否应该为0
//由于matrix[0][0]同时包含了第一行和第一列的信息，所以增加一个变量col0来记录第一列是否该为0
//因为使用了左上的元素记录信息，所以从右下开始依次判断每个元素