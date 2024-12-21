#include "header.h"

/*

1463. ժӣ�� II

����һ�� rows x cols �ľ��� grid ����ʾһ��ӣ�ҵأ�grid ��ÿ�����ӵ����ֱ�ʾ���ܻ�õ�ӣ����Ŀ

�������������˰����ռ�ӣ�ң������� 1 �����ϽǸ��� (0,0) ������������ 2 �����ϽǸ��� (0, cols-1) ����

���㰴�����¹��򣬷����������������ռ������ӣ����Ŀ��
�Ӹ��� (i,j) �����������˿����ƶ������� (i+1, j-1)��(i+1, j) ���� (i+1, j+1)
��һ�������˾���ĳ������ʱ������Ѹø��������е�ӣ�Ҷ�ժ�ߣ�Ȼ�����λ�û��ɿո��ӣ���û��ӣ�ҵĸ���
������������ͬʱ����ͬһ������ʱ��������ֻ��һ������ժ��ӣ��
����������������ʱ�̶������ƶ��� grid ����
�������������Ҫ���� grid �����һ��

ʾ�� 1��
���룺grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
�����24
���ͣ������� 1 �ͻ����� 2 ��·������ͼ�зֱ�����ɫ����ɫ��ʾ
������ 1 ժ��ӣ����ĿΪ (3 + 2 + 5 + 2) = 12
������ 2 ժ��ӣ����ĿΪ (1 + 5 + 5 + 1) = 12
ӣ������Ϊ�� 12 + 12 = 24

ʾ�� 2��
���룺grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]
�����28
���ͣ������� 1 �ͻ����� 2 ��·������ͼ�зֱ�����ɫ����ɫ��ʾ
������ 1 ժ��ӣ����ĿΪ (1 + 9 + 5 + 2) = 17
������ 2 ժ��ӣ����ĿΪ (1 + 3 + 4 + 3) = 11
ӣ������Ϊ�� 17 + 11 = 28

ʾ�� 3��
���룺grid = [[1,0,0,3],[0,0,0,3],[0,0,3,3],[9,0,3,3]]
�����22

ʾ�� 4��
���룺grid = [[1,1],[1,1]]
�����4

��ʾ��
rows == grid.length
cols == grid[i].length
2 <= rows, cols <= 70
0 <= grid[i][j] <= 100

*/

// ���仯���ݣ�j �� k ������������
class Solution1 {
public:
	vector<vector<vector<int>>> memo;
	int cherryPickup(vector<vector<int>> &grid) {
		int rows = grid.size(), cols = grid[0].size();
		memo.resize(rows, vector<vector<int>>(cols, vector<int>(cols, -1)));
		return helper(grid, 0, 0, cols - 1);
	}
	int helper(vector<vector<int>> &grid, int i, int j, int k) {
		int rows = grid.size(), cols = grid[0].size();
		if (i == rows) return 0;
		if (j < 0 || j >= cols || k < 0 || k >= cols || k <= j) return INT_MIN;
		if (memo[i][j][k] != -1) return memo[i][j][k];
		int res = INT_MIN;
		for (int j2 = j - 1; j2 <= j + 1; ++j2) {
			for (int k2 = k - 1; k2 <= k + 1; ++k2) {
				res = max(res, helper(grid, i + 1, j2, k2));
			}
		}
		return memo[i][j][k] = res + grid[i][j] + grid[i][k];
	}
};

// �Ե׶��ϵĶ�̬�滮
class Solution2 {
public:
	int cherryPickup(vector<vector<int>> &grid) {
		int rows = grid.size(), cols = grid[0].size();
		vector<vector<vector<int>>> dp(rows + 1,
			vector<vector<int>>(cols + 2, vector<int>(cols + 2)));
		for (int i = rows - 1; i >= 0; --i) {
			for (int j = 0; j <= min(cols - 1, i); ++j) {
				for (int k = max(j + 1, cols - 1 - i); k <= cols - 1; ++k) {
					dp[i][j + 1][k + 1] =
						max({ dp[i + 1][j][k], dp[i + 1][j][k + 1],
							dp[i + 1][j][k + 2], dp[i + 1][j + 1][k],
							dp[i + 1][j + 1][k + 1], dp[i + 1][j + 1][k + 2],
							dp[i + 1][j + 2][k], dp[i + 1][j + 2][k + 1],
							dp[i + 1][j + 2][k + 2] }) +
						grid[i][j] + grid[i][k];
				}
			}
		}
		return dp[0][1][cols];
	}
};


// �ռ临�Ӷ��Ż�
class Solution3 {
public:
	int cherryPickup(vector<vector<int>> &grid) {
		int rows = grid.size(), cols = grid[0].size();
		vector<vector<int>> dp1(cols + 2, vector<int>(cols + 2));
		vector<vector<int>> dp2(cols + 2, vector<int>(cols + 2));
		for (int i = rows - 1; i >= 0; --i) {
			for (int j = 0; j <= min(cols - 1, i); ++j) {
				for (int k = max(j + 1, cols - 1 - i); k <= cols - 1; ++k) {
					dp1[j + 1][k + 1] =
						max({ dp2[j][k], dp2[j][k + 1], dp2[j][k + 2],
							dp2[j + 1][k], dp2[j + 1][k + 1],
							dp2[j + 1][k + 2], dp2[j + 2][k],
							dp2[j + 2][k + 1], dp2[j + 2][k + 2] }) +
						grid[i][j] + grid[i][k];
				}
			}
			swap(dp1, dp2);
		}
		return dp2[1][cols];
	}
};


