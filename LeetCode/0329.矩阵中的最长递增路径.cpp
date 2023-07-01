#include "header.h"

/*

����һ�� m x n �������� matrix���ҳ����������·���ĳ���
����ÿ����Ԫ����������ϣ��£������ĸ������ƶ����㲻���ڶԽ��߷������ƶ����ƶ����߽��⣨���������ƣ�

ʾ�� 1��
���룺matrix = [[9,9,4],[6,6,8],[2,1,1]]
�����4
���ͣ������·��Ϊ [1, 2, 6, 9]

ʾ�� 2��
���룺matrix = [[3,4,5],[3,2,6],[2,2,1]]
�����4
���ͣ������·���� [3, 4, 5, 6]��ע�ⲻ�����ڶԽ��߷������ƶ�

ʾ�� 3��
���룺matrix = [[1]]
�����1

��ʾ��
m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
0 <= matrix[i][j] <= 2^31 - 1

*/

// DFS
class Solution1 {
private:
	static constexpr int dirs[4][2] = { { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } };
	int rows;
	int cols;

public:
	int longestIncreasingPath(vector<vector<int>> &matrix) {
		if (matrix.empty() || matrix[0].empty()) return 0;
		rows = matrix.size(), cols = matrix[0].size();
		vector<vector<int>> memo(rows, vector<int>(cols, 0));
		int ans = 0;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (!memo[i][j]) ans = max(ans, dfs(matrix, i, j, memo));
			}
		}
		return ans;
	}

private:
	int dfs(vector<vector<int>> &matrix, int row, int col,
		vector<vector<int>> &memo) {
		if (memo[row][col]) return memo[row][col];
		int ans = 1;
		for (auto dir : dirs) {
			int newRow = row + dir[0];
			int newCol = col + dir[1];
			if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
				matrix[newRow][newCol] > matrix[row][col]) {
				ans = max(ans, dfs(matrix, newRow, newCol, memo) + 1);
			}
		}
		return memo[row][col] = ans;
	}
};

// ��DFS��Ϊ��̬�滮
class Solution2 {
private:
	static constexpr int dirs[4][2] = { { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } };
	int rows;
	int cols;

public:
	int longestIncreasingPath(vector<vector<int>> &matrix) {
		if (matrix.empty() || matrix[0].empty()) return 0;
		int rows = matrix.size(), cols = matrix[0].size();
		// ����ڵ�ֵ������
		vector<vector<int>> points;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				points.push_back({ matrix[i][j], i, j });
			}
		}
		sort(points.begin(), points.end(),
			[](const vector<int> &a, const vector<int> &b) {
			return a[0] > b[0];
		});

		int ans = 0;
		vector<vector<int>> dp(rows, vector<int>(cols, 1));
		for (auto p : points) {
			int val = p[0];
			int row = p[1], col = p[2];
			for (auto dir : dirs) {
				int newRow = row + dir[0], newCol = col + dir[1];
				if (newRow >= 0 && newRow < rows && newCol >= 0 &&
					newCol < cols && matrix[newRow][newCol] > matrix[row][col]) {
					dp[row][col] = max(dp[row][col], dp[newRow][newCol] + 1);
				}
			}
			ans = max(ans, dp[row][col]);
		}
		return ans;
	}
};
