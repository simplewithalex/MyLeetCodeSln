#include "header.h"

/*

741. 摘樱桃

给你一个 n x n 的网格 grid，代表一块樱桃地，每个格子由以下三种数字的一种来表示：
0 表示这个格子是空的，所以你可以穿过它
1 表示这个格子里装着一个樱桃，你可以摘到樱桃然后穿过它
-1 表示这个格子里有荆棘，挡着你的路

请你统计并返回：在遵守下列规则的情况下，能摘到的最多樱桃数：
从位置 (0, 0) 出发，最后到达 (n - 1, n - 1) ，只能向下或向右走，并且只能穿越有效的格子（即只可以穿过值为 0 或者 1 的格子）
当到达 (n - 1, n - 1) 后，你要继续走，直到返回到 (0, 0) ，只能向上或向左走，并且只能穿越有效的格子
当你经过一个格子且这个格子包含一个樱桃时，你将摘到樱桃并且这个格子会变成空的（值变为 0）
如果在 (0, 0) 和 (n - 1, n - 1) 之间不存在一条可经过的路径，则无法摘到任何一个樱桃

示例 1：
输入：grid = [[0,1,-1],[1,0,-1],[1,1,1]]
输出：5
解释：玩家从 (0, 0) 出发：向下、向下、向右、向右移动至 (2, 2)
在这一次行程中捡到 4 个樱桃，矩阵变成 [[0,1,-1],[0,0,-1],[0,0,0]]
然后，玩家向左、向上、向上、向左返回起点，再捡到 1 个樱桃
总共捡到 5 个樱桃，这是最大可能值

示例 2：
输入：grid = [[1,1,-1],[1,-1,1],[-1,1,1]]
输出：0

提示：
n == grid.length
n == grid[i].length
1 <= n <= 50
grid[i][j] 为 -1、0 或 1
grid[0][0] != -1
grid[n - 1][n - 1] != -1

*/


// 记忆化，同时 j 与 k 区分上下轮廓
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


// 自底而上的动态规划
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


// 优化空间复杂度
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

