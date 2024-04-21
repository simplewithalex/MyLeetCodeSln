#include "header.h"

/*

1388. 3n 块披萨

给你一个披萨，它由 3n 块不同大小的部分组成，现在你和你的朋友们需要按照如下规则来分披萨：

你挑选 任意 一块披萨
Alice 将会挑选你所选择的披萨逆时针方向的下一块披萨
Bob 将会挑选你所选择的披萨顺时针方向的下一块披萨
重复上述过程直到没有披萨剩下

每一块披萨的大小按顺时针方向由循环数组 slices 表示
请你返回你可以获得的披萨大小总和的最大值

示例 1：
输入：slices = [1,2,3,4,5,6]
输出：10
解释：选择大小为 4 的披萨，Alice 和 Bob 分别挑选大小为 3 和 5 的披萨。
然后你选择大小为 6 的披萨，Alice 和 Bob 分别挑选大小为 2 和 1 的披萨。
你获得的披萨总大小为 4 + 6 = 10


示例 2：
输入：slices = [8,9,8,6,1,1]
输出：16
解释：两轮都选大小为 8 的披萨。
如果你选择大小为 9 的披萨，你的朋友们就会选择大小为 8 的披萨，
这种情况下你的总和不是最大的。


提示：
1 <= slices.length <= 500
slices.length % 3 == 0
1 <= slices[i] <= 1000

*/


// 打家劫舍拓展题
// 备忘录
class Solution1 {
private:
	vector<vector<int>> memo;

public:
	int maxSizeSlices(vector<int> &slices) {
		int m = slices.size();
		int n = m / 3;
		memo.resize(m + 1, vector<int>(n + 1, -1));
		int res1 = helper(slices, 1, m - 1, n);
		// 注意两次计算输入不同，memo数组要清空
		memo.clear();
		memo.resize(m + 1, vector<int>(n + 1, -1));
		int res2 = helper(slices, 2, m, n);
		return max(res1, res2);
	}

private:
	int helper(vector<int> &slices, int start, int idx, int c) {
		if (c == 0 || idx < start) return 0;
		if (memo[idx][c] != -1) return memo[idx][c];
		return memo[idx][c] =
			max(helper(slices, start, idx - 2, c - 1) + slices[idx - 1],
				helper(slices, start, idx - 1, c));
	}
};

// 自底而上的动态规划
class Solution2 {
public:
	int maxSizeSlices(vector<int> &slices) {
		int len = slices.size();
		int res1 = calculate(slices, 1, len - 1);
		int res2 = calculate(slices, 2, len);
		return max(res1, res2);
	}

private:
	int calculate(vector<int> &slices, int start, int end) {
		int m = slices.size(), n = m / 3;
		vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
		dp[start - 1][0] = 0, dp[start][0] = 0;
		dp[start - 1][1] = 0, dp[start][1] = slices[start - 1];
		for (int i = start + 1; i <= end; ++i) {
			dp[i][0] = 0;
			for (int j = 1; j <= n; ++j) {
				dp[i][j] = max(dp[i - 1][j], dp[i - 2][j - 1] + slices[i - 1]);
			}
		}
		return dp[end][n];
	}
};

// https://leetcode.cn/problems/pizza-with-3n-slices/solutions/177086/3n-kuai-pi-sa-by-leetcode-solution/
// @author LeetCode官方题解


