#include "header.h"

/*

给定一个非负索引 k，其中 k ≤ 33，返回杨辉三角的第 k 行。
在杨辉三角中，每个数是它左上方和右上方的数的和。

示例:

输入: 3
输出: [1,3,3,1]

你可以优化你的算法到 O(k) 空间复杂度吗？

*/

class Solution {
public:
	vector<int> getRow(int rowIndex)
	{
		if (rowIndex<0) return {};
		vector<int> res(rowIndex + 1);
		res[0] = 1;
		for (int i = 1; i <= rowIndex; ++i)
			for (int j = i; j >= 1; --j)
				res[j] += res[j - 1];
		return res;
	}
};