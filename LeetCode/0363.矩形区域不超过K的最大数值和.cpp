#include "header.h"

/*

363. 矩形区域不超过 K 的最大数值和

给你一个 m x n 的矩阵 matrix 和一个整数 k，找出并返回矩阵内部矩形区域的不超过 k 的最大数值和

题目数据保证总会存在一个数值和不超过 k 的矩形区域

示例 1：
输入：matrix = [[1,0,1],[0,-2,3]], k = 2
输出：2
解释：蓝色边框圈出来的矩形区域 [[0, 1], [-2, 3]] 的数值和是 2，且 2 是不超过 k 的最大数字（k = 2）

示例 2：
输入：matrix = [[2,2,-1]], k = 3
输出：3

提示：
m == matrix.length
n == matrix[i].length
1 <= m, n <= 100
-100 <= matrix[i][j] <= 100
-10^5 <= k <= 10^5

进阶：如果行数远大于列数，该如何设计解决方案？

*/


// 朴素二维前缀和(TLE)
class Solution1 {
private:
	vector<vector<int>> preSum;

public:
	int maxSumSubmatrix(vector<vector<int>> &matrix, int k) {
		if (matrix.empty() || matrix[0].empty()) return 0;
		int rows = matrix.size(), cols = matrix[0].size();
		preSum.resize(rows + 1);
		for (int i = 0; i <= rows; ++i) preSum[i].resize(cols + 1, 0);
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				preSum[i + 1][j + 1] = preSum[i][j + 1] + preSum[i + 1][j] -
					preSum[i][j] + matrix[i][j];
			}
		}
		int ans = INT_MIN;
		for (int row1 = 0; row1 < rows; ++row1) {
			for (int col1 = 0; col1 < cols; ++col1) {
				for (int row2 = row1; row2 < rows; ++row2) {
					for (int col2 = col1; col2 < cols; ++col2) {
						int cur = preSum[row2 + 1][col2 + 1] -
							preSum[row2 + 1][col1] -
							preSum[row1][col2 + 1] + preSum[row1][col1];
						if (cur <= k) ans = max(ans, cur);
					}
				}
			}
		}
		return ans;
	}
};

// 二维前缀和 + 二分
class Solution2 {
private:
	vector<vector<int>> preSum;

public:
	int maxSumSubmatrix(vector<vector<int>> &matrix, int k) {
		if (matrix.empty() || matrix[0].empty()) return 0;
		int rows = matrix.size(), cols = matrix[0].size();
		preSum.resize(rows + 1);
		for (int i = 0; i <= rows; ++i) preSum[i].resize(cols + 1, 0);
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				preSum[i + 1][j + 1] = preSum[i][j + 1] + preSum[i + 1][j] -
					preSum[i][j] + matrix[i][j];
			}
		}
		int ans = INT_MIN;
		for (int top = 0; top < rows; ++top) {
			for (int bottom = top; bottom < rows; ++bottom) {
				set<int> s;
				// area_left可以不存在
				s.insert(0);
				for (int right = 0; right < cols; ++right) {
					int area_right = preSum[bottom + 1][right + 1] - preSum[top][right + 1];
					// 找到大于或等于area_right - k的最小值
					auto area_left_iter = s.lower_bound(area_right - k);
					if (area_left_iter != s.end()) {
						int cur = area_right - *area_left_iter;
						ans = max(ans, cur);
					}
					s.insert(area_right);
				}
			}
		}
		return ans;
	}
};
// https://leetcode.cn/problems/max-sum-of-rectangle-no-larger-than-k/solutions/734547/gong-shui-san-xie-you-hua-mei-ju-de-ji-b-dh8s/
// @author https://leetcode.cn/u/ac_oier/


// 二分优化，根据行或列的大小确定二分查找方向
class Solution3 {
private:
	vector<vector<int>> preSum;

public:
	int maxSumSubmatrix(vector<vector<int>> &matrix, int k) {
		if (matrix.empty() || matrix[0].empty()) return 0;
		int rows = matrix.size(), cols = matrix[0].size();
		preSum.resize(rows + 1);
		for (int i = 0; i <= rows; ++i) preSum[i].resize(cols + 1, 0);
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				preSum[i + 1][j + 1] = preSum[i][j + 1] + preSum[i + 1][j] -
					preSum[i][j] + matrix[i][j];
			}
		}
		int ans = INT_MIN;
		bool isRow = cols > rows;
		// 注意条件运算符优先级
		for (int i = 0; i < (isRow ? rows : cols); ++i) {
			for (int j = i; j < (isRow ? rows : cols); ++j) {
				set<int> s;
				s.insert(0);
				for (int fixed = 0; fixed < (isRow ? cols : rows); ++fixed) {
					int area_fixed =
						isRow ? preSum[j + 1][fixed + 1] - preSum[i][fixed + 1]
						: preSum[fixed + 1][j + 1] - preSum[fixed + 1][i];
					auto area_var_iter = s.lower_bound(area_fixed - k);
					if (area_var_iter != s.end()) {
						int cur = area_fixed - *area_var_iter;
						ans = max(ans, cur);
					}
					s.insert(area_fixed);
				}
			}
		}
		return ans;
	}
};

// 空间优化
class Solution4 {
private:
	vector<vector<int>> preSum;

public:
	int maxSumSubmatrix(vector<vector<int>> &matrix, int k) {
		if (matrix.empty() || matrix[0].empty()) return 0;
		int rows = matrix.size(), cols = matrix[0].size();
		bool isRow = cols > rows;
		int ans = INT_MIN;
		for (int i = 0; i < (isRow ? rows : cols); ++i) {
			vector<int> preSum(isRow ? cols + 1 : rows + 1, 0);
			for (int j = i; j < (isRow ? rows : cols); ++j) {
				set<int> s;
				s.insert(0);
				int area_fixed = 0;
				for (int fixed = 0; fixed < (isRow ? cols : rows); ++fixed) {
					preSum[fixed + 1] +=
						isRow ? matrix[j][fixed] : matrix[fixed][j];
					area_fixed += preSum[fixed + 1];
					auto area_var_iter = s.lower_bound(area_fixed - k);
					if (area_var_iter != s.end()) {
						int cur = area_fixed - *area_var_iter;
						ans = max(ans, cur);
					}
					s.insert(area_fixed);
				}
			}
		}
		return ans;
	}
};