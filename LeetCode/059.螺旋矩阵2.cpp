#include "header.h"

/*

����һ��������n������һ������ 1 �� n^2 ����Ԫ�أ���Ԫ�ذ�˳ʱ��˳���������е������ξ���

ʾ��:
����: 3
���:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]

*/

class Solution {
public:
	vector<vector<int>> generateMatrix(int n)
	{
		vector<vector<int>> res(n, vector<int>(n));
		int cur = 1;
		int rowBegin = 0, rowEnd = n - 1;
		int colBegin = 0, colEnd = n - 1;
		while (cur <= n*n)
		{
			int i = rowBegin;
			int j = colBegin;
			for (j = colBegin; j <= colEnd; ++j)
			{
				res[rowBegin][j] = cur++;
			}
			++rowBegin;
			for (i = rowBegin; i <= rowEnd; ++i)
			{
				res[i][colEnd] = cur++;
			}
			--colEnd;
			for (j = colEnd; j >= colBegin; --j)
			{
				res[rowEnd][j] = cur++;
			}
			--rowEnd;
			for (i = rowEnd; i >= rowBegin; --i)
			{
				res[i][colBegin] = cur++;
			}
			++colBegin;
		}
		return res;
	}
};