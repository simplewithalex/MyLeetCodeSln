#include "header.h"

/*

304. ��ά����ͼ��� - ���󲻿ɱ�

����һ����ά���� matrix���������͵Ķ������

�������Ӿ��η�Χ��Ԫ�ص��ܺͣ����Ӿ���� ���Ͻ� Ϊ (row1, col1) �����½� Ϊ (row2, col2)

ʵ�� NumMatrix �ࣺ
NumMatrix(int[][] matrix) ������������ matrix ���г�ʼ��
int sumRegion(int row1, int col1, int row2, int col2) ���� ���Ͻ� (row1, col1)�����½� (row2, col2) ���������Ӿ����Ԫ���ܺ�

ʾ�� 1��
����:
["NumMatrix","sumRegion","sumRegion","sumRegion"]
[[[[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]]],[2,1,4,3],[1,1,2,2],[1,2,2,4]]
���:
[null, 8, 11, 12]
����:
NumMatrix numMatrix = new NumMatrix([[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]]);
numMatrix.sumRegion(2, 1, 4, 3); // return 8 (��ɫ���ο��Ԫ���ܺ�)
numMatrix.sumRegion(1, 1, 2, 2); // return 11 (��ɫ���ο��Ԫ���ܺ�)
numMatrix.sumRegion(1, 2, 2, 4); // return 12 (��ɫ���ο��Ԫ���ܺ�)

��ʾ��
m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
-10^5 <= matrix[i][j] <= 10^5
0 <= row1 <= row2 < m
0 <= col1 <= col2 < n
������ 10^4 �� sumRegion ����

*/

// һάǰ׺��
class NumMatrix1 {
private:
	vector<vector<int>> preSum;

public:
	NumMatrix1(vector<vector<int>> &matrix) {
		if (matrix.empty() || matrix[0].empty()) return;
		int rows = matrix.size(), cols = matrix[0].size();
		preSum.resize(rows);
		for (int i = 0; i < rows; ++i) {
			preSum[i].resize(cols + 1, 0);
			for (int j = 0; j < cols; ++j) {
				preSum[i][j + 1] = matrix[i][j] + preSum[i][j];
			}
		}
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		int res = 0;
		for (int i = row1; i <= row2; ++i) {
			res += preSum[i][col2 + 1] - preSum[i][col1];
		}
		return res;
	}
};

/**
* Your NumMatrix object will be instantiated and called as such:
* NumMatrix* obj = new NumMatrix(matrix);
* int param_1 = obj->sumRegion(row1,col1,row2,col2);
*/

// ��άǰ׺��
class NumMatrix2 {
private:
	vector<vector<int>> preSum;

public:
	NumMatrix2(vector<vector<int>> &matrix) {
		if (matrix.empty() || matrix[0].empty()) return;
		int rows = matrix.size(), cols = matrix[0].size();
		preSum.resize(rows + 1);
		for (int i = 0; i < rows; ++i) preSum[i].resize(cols + 1, 0);
		for (int i = 0; i <= rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				preSum[i + 1][j + 1] = preSum[i][j + 1] + preSum[i + 1][j] -
					preSum[i][j] + matrix[i][j];
			}
		}
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		return preSum[row2 + 1][col2 + 1] - preSum[row2 + 1][col1] -
			preSum[row1][col2 + 1] + preSum[row1][col1];
	}
};

/**
* Your NumMatrix object will be instantiated and called as such:
* NumMatrix* obj = new NumMatrix(matrix);
* int param_1 = obj->sumRegion(row1,col1,row2,col2);
*/

// https://leetcode.cn/problems/range-sum-query-2d-immutable/solutions/629187/ru-he-qiu-er-wei-de-qian-zhui-he-yi-ji-y-6c21/
// @author https://leetcode.cn/u/fuxuemingzhu/