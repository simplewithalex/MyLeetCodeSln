#include "header.h"

/*

给定一个仅包含 0 和 1 的二维二进制矩阵，找出只包含 1 的最大矩形，并返回其面积。

示例:
输入:
[
 ["1","0","1","0","0"],
 ["1","0","1","1","1"],
 ["1","1","1","1","1"],
 ["1","0","0","1","0"]
]
输出: 6

*/

class Solution {
public:
	int maximalRectangle(vector<vector<char>> &matrix)
	{
		if (matrix.empty() || matrix[0].empty()) return 0;
		int rows = matrix.size(), cols = matrix[0].size();
		vector<int> heights(cols, 0);
		int maxRes = 0;
		for (int i = 0; i < rows; ++i)
		{
			stack<int> s;
			int lastCol = -1;
			for (int j = 0; j <= cols;)
			{
				if (lastCol < j&&j < cols)
				{
					if (matrix[i][j] == '1') heights[j] += 1;
					else heights[j] = 0;
					lastCol = j;
				}
				int h = (j == cols) ? 0 : heights[j];
				if (s.empty() || h >= heights[s.top()])
				{
					s.push(j);
					++j;
				}
				else
				{
					int tempH = s.top();
					s.pop();
					maxRes = max(maxRes, heights[tempH] * (s.empty() ? j : j - 1 - s.top()));
				}
			}
		}
		return maxRes;
	}
};
//基于https://www.nowcoder.com/profile/3529440/codeBookDetail?submissionId=47584047这个题目的解法，分别更新每一行所代表的直方图高度。
//相关解法：https://leetcode.com/problems/maximal-rectangle/discuss/29064/A-O(n2)-solution-based-on-Largest-Rectangle-in-Histogram
