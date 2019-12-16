#include "header.h"

/*

有 n 个气球，编号为0 到 n-1，每个气球上都标有一个数字，这些数字存在数组 nums 中。

现在要求你戳破所有的气球。每当你戳破一个气球 i 时，你可以获得 nums[left] * nums[i] * nums[right] 个硬币。 

这里的 left 和 right 代表和 i 相邻的两个气球的序号。注意当你戳破了气球 i 后，气球 left 和气球 right 就变成了相邻的气球。

求所能获得硬币的最大数量。

说明:

你可以假设 nums[-1] = nums[n] = 1，但注意它们不是真实存在的所以并不能被戳破。
0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100

示例:
输入: [3,1,5,8]
输出: 167
解释: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
     coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167

*/

//备忘录方法
class Solution1 {
public:
	int maxCoins(vector<int> &nums)
	{
		nums.insert(nums.begin(), 1);
		nums.push_back(1);
		int len = nums.size();
		vector<vector<int>> memo(len, vector<int>(len, 0));
		return burst(nums, memo, 0, len - 1);
	}
	int burst(vector<int> &nums, vector<vector<int>> &memo, int left, int right)
	{
		if (left + 1 == right) return 0;
		if (memo[left][right] > 0) return memo[left][right];
		int res = 0;
		for (int i = left + 1; i < right; ++i)
		{
			//这里是从剩下的最后一个气球作为分割开始，依此递归，即剩下的最后一个数为分界点，它的得分为1 * 1 * nums[i]
			res = max(res, nums[left] * nums[right] * nums[i] + burst(nums, memo, left, i) + burst(nums, memo, i, right));
		}
		memo[left][right] = res;
		return res;
	}
};
//https://leetcode.com/problems/burst-balloons/discuss/76228/Share-some-analysis-and-explanations

//由备忘录方法改写为动态规划
class Solution2 {
public:
	int maxCoins(vector<int> &nums)
	{
		nums.insert(nums.begin(), 1);
		nums.push_back(1);
		int len = nums.size();
		//dp[left][right] 表示戳破 [left+1 ... right-1] 号气球的最大收益
		vector<vector<int>> dp(len, vector<int>(len, 0));
		for (int gap = 2; gap < len; ++gap)
		{
			for (int left = 0; left < len - gap; ++left)
			{
				int right = left + gap;
				for (int i = left + 1; i < right; ++i)
				{
					//假设i号气球（left+1 <= i <= right-1）是[left+1 ... right-1] 中最后一个被戳破的
					dp[left][right] = max(dp[left][right], nums[left] * nums[i] * nums[right] + dp[left][i] + dp[i][right]);
				}
			}
		}
		return dp[0][len - 1];
	}
};
//https://leetcode.com/problems/burst-balloons/discuss/76228/Share-some-analysis-and-explanations
//https://leetcode-cn.com/problems/burst-balloons/solution/dong-tai-gui-hua-by-ivan_allen-2/