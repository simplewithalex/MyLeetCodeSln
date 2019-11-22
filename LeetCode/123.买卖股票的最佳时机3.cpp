#include "header.h"

/*

给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。
设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。
注意: 你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

示例 1:

输入: [3,3,5,0,0,3,1,4]
输出: 6
解释: 在第 4 天（股票价格 = 0）的时候买入，在第 6 天（股票价格 = 3）的时候卖出，这笔交易所能获得利润 = 3-0 = 3 。
随后，在第 7 天（股票价格 = 1）的时候买入，在第 8 天 （股票价格 = 4）的时候卖出，这笔交易所能获得利润 = 4-1 = 3 。
	 
示例 2:

输入: [1,2,3,4,5]
输出: 4
解释: 在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。  
注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。  
因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。
			   
示例 3:

输入: [7,6,4,3,1]
输出: 0
解释: 在这个情况下, 没有交易完成, 所以最大利润为 0。

*/

//动态规划
class Solution1
{
public:
	int maxProfit(vector<int> &prices)
	{
		if (prices.empty()) return 0;
		int k = 2;
		vector<vector<int>> dp(prices.size(), vector<int>(k + 1, 0));
		for (int i = 1; i <= k; ++i)
		{
			int minNum = prices[0];
			for (int j = 1; j < prices.size(); ++j)
			{
				minNum = min(prices[j] - dp[j][i - 1], minNum);
				dp[j][i] = max(dp[j - 1][i], prices[j] - minNum);
			}
		}
		return dp[prices.size() - 1][k];
	}
};

//有限状态机
class Solution2 
{
public:
	int maxProfit(vector<int> &prices)
	{
		if (prices.empty()) return 0;
		int s1 = -prices[0], s2 = INT_MIN, s3 = INT_MIN, s4 = INT_MIN;
		for (int i = 1; i<prices.size(); ++i)
		{
			s1 = max(s1, -prices[i]);
			s2 = max(s2, s1 + prices[i]);
			s3 = max(s3, s2 - prices[i]);
			s4 = max(s4, s3 + prices[i]);
		}
		return max(0, s4);
	}
};
//https://leetcode.wang/leetcode-123-Best-Time-to-Buy-and-Sell-StockIII.html

//状态机解法
class Solution3 {
public:
	int maxProfit(vector<int> &prices)
	{
		int len = prices.size();
		if (len == 0) return 0;
		int maxK = 2;
		vector<vector<vector<int>>> dp(len, vector<vector<int>>(maxK + 1, vector<int>(2, 0)));
		for (int i = 0; i < len; ++i)
		{
			for (int k = maxK; k >= 1; --k)
			{
				if (i - 1 == -1)
				{
					dp[i][k][0] = 0;
					dp[i][k][1] = -prices[i];
					continue;
				}
				dp[i][k][0] = max(dp[i - 1][k][0], dp[i - 1][k][1] + prices[i]);
				dp[i][k][1] = max(dp[i - 1][k][1], dp[i - 1][k - 1][0] - prices[i]);
			}
		}
		return dp[len - 1][maxK][0];
	}
};
//https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/solution/yi-ge-fang-fa-tuan-mie-6-dao-gu-piao-wen-ti-by-l-3/