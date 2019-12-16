#include "header.h"

/*

给定一个整数数组，其中第 i 个元素代表了第 i 天的股票价格 。​

设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:

你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。

示例:
输入: [1,2,3,0,2]
输出: 3
解释: 对应的交易状态为: [买入, 卖出, 冷冻期, 买入, 卖出]

*/

//状态机通用解法
class Solution {
public:
	int maxProfit(vector<int> &prices)
	{
		int len = prices.size();
		if (len == 0) return 0;
		vector<vector<int>> dp(len, vector<int>(2, 0));
		for (int i = 0; i < len; ++i)
		{
			if (i == 0)
			{
				dp[i][0] = 0;
				dp[i][1] = -prices[i];
				continue;
			}
			else if (i == 1)
			{
				dp[i][0] = max(0, -prices[i - 1] + prices[i]);
				dp[i][1] = max(-prices[i - 1], -prices[i]);
				continue;
			}
			dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
			dp[i][1] = max(dp[i - 1][1], dp[i - 2][0] - prices[i]);
		}
		return dp[len - 1][0];
	}
};
//https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/solution/yi-ge-fang-fa-tuan-mie-6-dao-gu-piao-wen-ti-by-l-3/

