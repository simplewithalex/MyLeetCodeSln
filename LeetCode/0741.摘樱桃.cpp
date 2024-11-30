#include "header.h"

/*

741. ժӣ��

����һ�� n x n ������ grid������һ��ӣ�ҵأ�ÿ�������������������ֵ�һ������ʾ��
0 ��ʾ��������ǿյģ���������Դ�����
1 ��ʾ���������װ��һ��ӣ�ң������ժ��ӣ��Ȼ�󴩹���
-1 ��ʾ����������о������������·

����ͳ�Ʋ����أ����������й��������£���ժ�������ӣ������
��λ�� (0, 0) ��������󵽴� (n - 1, n - 1) ��ֻ�����»������ߣ�����ֻ�ܴ�Խ��Ч�ĸ��ӣ���ֻ���Դ���ֵΪ 0 ���� 1 �ĸ��ӣ�
������ (n - 1, n - 1) ����Ҫ�����ߣ�ֱ�����ص� (0, 0) ��ֻ�����ϻ������ߣ�����ֻ�ܴ�Խ��Ч�ĸ���
���㾭��һ��������������Ӱ���һ��ӣ��ʱ���㽫ժ��ӣ�Ҳ���������ӻ��ɿյģ�ֵ��Ϊ 0��
����� (0, 0) �� (n - 1, n - 1) ֮�䲻����һ���ɾ�����·�������޷�ժ���κ�һ��ӣ��

ʾ�� 1��
���룺grid = [[0,1,-1],[1,0,-1],[1,1,1]]
�����5
���ͣ���Ҵ� (0, 0) ���������¡����¡����ҡ������ƶ��� (2, 2)
����һ���г��м� 4 ��ӣ�ң������� [[0,1,-1],[0,0,-1],[0,0,0]]
Ȼ������������ϡ����ϡ����󷵻���㣬�ټ� 1 ��ӣ��
�ܹ��� 5 ��ӣ�ң�����������ֵ

ʾ�� 2��
���룺grid = [[1,1,-1],[1,-1,1],[-1,1,1]]
�����0

��ʾ��
n == grid.length
n == grid[i].length
1 <= n <= 50
grid[i][j] Ϊ -1��0 �� 1
grid[0][0] != -1
grid[n - 1][n - 1] != -1

*/


// ���仯��ͬʱ j �� k ������������
class Solution1 {
public:
	vector<vector<vector<int>>> memo;
	int cherryPickup(vector<vector<int>>& grid) {
		int len = grid.size();
		memo.resize(len * 2, vector<vector<int>>(len, vector<int>(len, -1)));
		return max(helper(grid, len * 2 - 2, len - 1, len - 1), 0);
	}
	int helper(vector<vector<int>>& grid, int t, int j, int k) {
		if (j < 0 || k < 0 || t < j || t < k || grid[t - j][j] < 0 ||
			grid[t - k][k] < 0 || k < j) {
			return INT_MIN;
		}
		if (t == 0) return grid[0][0];
		if (memo[t][j][k] != -1) return memo[t][j][k];
		return memo[t][j][k] = max({ helper(grid, t - 1, j, k),
			helper(grid, t - 1, j, k - 1),
			helper(grid, t - 1, j - 1, k),
			helper(grid, t - 1, j - 1, k - 1) }) +
			grid[t - j][j] + (k != j ? grid[t - k][k] : 0);
	}
};
// https://leetcode.cn/problems/cherry-pickup/solutions/2766975/jiao-ni-yi-bu-bu-si-kao-dpcong-ji-yi-hua-ruue/
// @author https://leetcode.cn/u/endlesscheng/


// �Ե׶��ϵĶ�̬�滮
class Solution2 {
public:
	int cherryPickup(vector<vector<int>>& grid) {
		int len = grid.size();
		vector<vector<vector<int>>> dp(2 * len - 1,
			vector<vector<int>>(len + 1, vector<int>(len + 1, INT_MIN)));
		dp[0][1][1] = grid[0][0];
		for (int t = 1; t < len * 2 - 1; ++t) {
			for (int j = max(t - len + 1, 0); j <= min(t, len - 1); ++j) {
				if (grid[t - j][j] < 0) continue;
				for (int k = j; k <= min(t, len - 1); ++k) {
					if (grid[t - k][k] < 0) continue;
					dp[t][j + 1][k + 1] =
						max({ dp[t - 1][j + 1][k + 1], dp[t - 1][j + 1][k],
							dp[t - 1][j][k + 1], dp[t - 1][j][k] }) +
						grid[t - j][j] + (k != j ? grid[t - k][k] : 0);
				}
			}
		}
		return max(dp[len * 2 - 2][len][len], 0);
	}
};
// https://leetcode.cn/problems/cherry-pickup/solutions/2766975/jiao-ni-yi-bu-bu-si-kao-dpcong-ji-yi-hua-ruue/
// @author https://leetcode.cn/u/endlesscheng/


// �Ż��ռ临�Ӷ�
class Solution3 {
public:
	int cherryPickup(vector<vector<int>>& grid) {
		int len = grid.size();
		vector<vector<int>> dp(len + 1, vector<int>(len + 1, INT_MIN));
		dp[1][1] = grid[0][0];
		for (int t = 1; t < len * 2 - 1; ++t) {
			for (int j = min(t, len - 1); j >= max(t - len + 1, 0); --j) {
				for (int k = min(t, len - 1); k >= j; --k) {
					if (grid[t - j][j] < 0 || grid[t - k][k] < 0) {
						dp[j + 1][k + 1] = INT_MIN;
					} else {
						dp[j + 1][k + 1] = max({ dp[j + 1][k + 1], dp[j + 1][k],
							dp[j][k + 1], dp[j][k] }) +
							grid[t - j][j] +
							(k != j ? grid[t - k][k] : 0);
					}
				}
			}
		}
		return max(dp[len][len], 0);
	}
};
// https://leetcode.cn/problems/cherry-pickup/solutions/2766975/jiao-ni-yi-bu-bu-si-kao-dpcong-ji-yi-hua-ruue/
// @author https://leetcode.cn/u/endlesscheng/

