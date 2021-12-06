#include "header.h"

/*

一些恶魔抓住了公主（P）并将她关在了地下城的右下角。地下城是由 M x N 个房间组成的二维网格。我们英勇的骑士（K）最初被安置在左上角的房间里，他必须穿过地下城并通过对抗恶魔来拯救公主。

骑士的初始健康点数为一个正整数。如果他的健康点数在某一时刻降至 0 或以下，他会立即死亡。

有些房间由恶魔守卫，因此骑士在进入这些房间时会失去健康点数（若房间里的值为负整数，则表示骑士将损失健康点数）；
其他房间要么是空的（房间里的值为 0），要么包含增加骑士健康点数的魔法球（若房间里的值为正整数，则表示骑士将增加健康点数）。

为了尽快到达公主，骑士决定每次只向右或向下移动一步。

 
编写一个函数来计算确保骑士能够拯救到公主所需的最低初始健康点数。

例如，考虑到如下布局的地下城，如果骑士遵循最佳路径 右 -> 右 -> 下 -> 下，则骑士的初始健康点数至少为 7。

-2 (K)	 -3	  3
-5	    -10	  1
10	     30	 -5 (P)
  
说明:
骑士的健康点数没有上限。
任何房间都可能对骑士的健康点数造成威胁，也可能增加骑士的健康点数，包括骑士进入的左上角房间以及公主被监禁的右下角房间。

*/


// 备忘录
class Solution1 {
public:
	int calculateMinimumHP(vector<vector<int>> &dungeon) {
		int len1 = dungeon.size(), len2 = dungeon[0].size();
		vector<vector<int>> m(len1, vector<int>(len2, -1));
		return helper(dungeon, 0, 0, m);
	}

	int helper(vector<vector<int>> &dungeon, int i, int j, vector<vector<int>> &m) {
		if (i == dungeon.size() - 1 && j == dungeon[0].size() - 1) {
			if (dungeon[i][j] > 0) return 1;
			else return -dungeon[i][j] + 1;
		}
		if (m[i][j] != -1) return m[i][j];
		int right = j < dungeon[0].size() - 1 ? helper(dungeon, i, j + 1, m) : INT_MAX;
		int down = i < dungeon.size() - 1 ? helper(dungeon, i + 1, j, m) : INT_MAX;
		int need = right < down ? right - dungeon[i][j] : down - dungeon[i][j];
		if (need <= 0) return m[i][j] = 1;
		else return m[i][j] = need;
	}
};
/*

如果从右下到左上分解子问题，即从左上到右下做动态规划

此时f(i,j)需要根据f(i-1,j)和f(i,j-1)来判断，但考虑如下情况

-2     -5    -10
-5    -100   -40
-100  1000    x

判断x的取值时，一定会考虑左边的值还是上边的值，但是左边的值有极大的加成，无法得到在此之前实际消耗的数值，所以无法判断
该问题只能逆向判断实际需要的数值, 以避免这种加成的影响

*/


// 自底而上动态规划
class Solution2 {
public:
	int calculateMinimumHP(vector<vector<int>> &dungeon) {
		int row = dungeon.size(), col = dungeon[0].size();
		vector<vector<int>> dp(row + 1, vector<int>(col + 1, INT_MAX));
		for (int i = row - 1; i >= 0; --i) {
			for (int j = col - 1; j >= 0; --j) {
				if (i == row - 1 && j == col - 1) {
					dp[i][j] = dungeon[i][j] > 0 ? 1 : -dungeon[i][j] + 1;
				}
				else {
					dp[i][j] = min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j];
					if (dp[i][j] <= 0)
						dp[i][j] = 1;
				}
			}
		}
		return dp[0][0];
	}
};

// 优化为一维dp
class Solution3 {
public:
	int calculateMinimumHP(vector<vector<int>> &dungeon) {
		int row = dungeon.size(), col = dungeon[0].size();
		vector<int> dp(col + 1, INT_MAX);
		for (int i = row - 1; i >= 0; --i) {
			for (int j = col - 1; j >= 0; --j) {
				if (i == row - 1 && j == col - 1) {
					dp[j] = dungeon[i][j] > 0 ? 1 : -dungeon[i][j] + 1;
				}
				else {
					dp[j] = min(dp[j], dp[j + 1]) - dungeon[i][j];
					if (dp[j] <= 0) dp[j] = 1;
				}
			}
		}
		return dp[0];
	}
};