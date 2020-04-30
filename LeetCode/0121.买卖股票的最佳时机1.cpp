#include "header.h"

/*

给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
如果你最多只允许完成一笔交易（即买入和卖出一支股票），
设计一个算法来计算你所能获取的最大利润。
注意你不能在买入股票前卖出股票。

示例 1:
输入: [7,1,5,3,6,4]
输出: 5
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格。

示例 2:
输入: [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。

*/

class Solution1 {
public:
	int maxProfit(vector<int> &prices)
	{
		int len = prices.size();
		if (len <= 1)
			return 0;
		int minprice = INT_MAX;
		int maxsofar = 0;
		for (int i = 0; i<len; ++i)
		{
			if (prices[i] < minprice)
			{
				minprice = prices[i];
			}
			else
			{
				maxsofar = max(maxsofar, prices[i] - minprice);
			}
		}
		return maxsofar;
	}
};


//状态机解法
class Solution2 {
public:
	int maxProfit(vector<int> &prices)
	{
		int len = prices.size();
		if (len == 0) return 0;
		vector<vector<int>> dp(len, vector<int>(2, 0));
		for (int i = 0; i < len; ++i)
		{
			//好的习惯，其他股票问题可能会有对k状态的循环，需要这样写
			if (i - 1 == -1)
			{
				dp[i][0] = 0;
				dp[i][1] = -prices[i];
				continue;
			}
			dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
			dp[i][1] = max(dp[i - 1][1], -prices[i]);
		}
		return dp[len - 1][0];
	}
};
//https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/solution/yi-ge-fang-fa-tuan-mie-6-dao-gu-piao-wen-ti-by-l-3/
//关于buy-1还是sell-1的问题，参考下面的链接
//https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/discuss/108870/Most-consistent-ways-of-dealing-with-the-series-of-stock-problems/111002
//@tzzz117和@fun4LeetCode的评论中回答了这个问题，错误出现在初始化状态时，如果buy不用减一而sell减一的话，dp[i][0][1]此时是可能的，所以它的值不是INT_MIN

