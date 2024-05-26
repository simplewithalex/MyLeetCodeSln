#include "header.h"

/*

446. 等差数列划分 II - 子序列

给你一个整数数组nums，返回nums中所有等差子序列的数目
如果一个序列中 至少有三个元素，并且任意两个相邻元素之差相同，则称该序列为等差序列

例如，[1, 3, 5, 7, 9]、[7, 7, 7, 7] 和 [3, -1, -5, -9] 都是等差序列
再例如，[1, 1, 2, 5, 7] 不是等差序列

数组中的子序列是从数组中删除一些元素（也可能不删除）得到的一个序列
例如，[2,5,10] 是 [1,2,1,2,4,1,5,10] 的一个子序列
题目数据保证答案是一个 32-bit 整数

示例 1：
输入：nums = [2,4,6,8,10]
输出：7
解释：所有的等差子序列为：
[2,4,6]
[4,6,8]
[6,8,10]
[2,4,6,8]
[4,6,8,10]
[2,4,6,8,10]
[2,6,10]

示例 2：
输入：nums = [7,7,7,7,7]
输出：16
解释：数组中的任意子序列都是等差子序列

提示：
1  <= nums.length <= 1000
-2^31 <= nums[i] <= 2^31 - 1

*/

// 备忘录算法，超时
class Solution1 {
private:
	vector<unordered_map<long long, int>> memo;
	vector<unordered_map<long long, vector<int>>> dict;

public:
	int numberOfArithmeticSlices(vector<int>& nums) {
		int len = nums.size();
		int res = 0;
		dict.resize(len);
		memo.resize(len);

		for (int i = 0; i < len; ++i) {
			for (int j = i - 1; j >= 0; --j) {
				long long diff = (long long)nums[i] - nums[j];
				dict[i][diff].push_back(j);
			}
		}
		for (int i = 0; i < len; ++i) {
			for (auto p : dict[i]) res += helper(nums, i, p.first);
		}
		res -= len * (len - 1) / 2;
		return res;
	}

private:
	int helper(vector<int>& nums, int idx, long long d) {
		if (memo[idx].count(d)) return memo[idx][d];
		int cnt = 0;
		for (int j : dict[idx][d]) {
			cnt += helper(nums, j, d) + 1;
		}
		return memo[idx][d] = cnt;
	}
};


// 自底而上的的动态规划
class Solution2 {
public:
	int numberOfArithmeticSlices(vector<int> &nums) {
		int len = nums.size();
		vector<unordered_map<long long, int>> dp(len);
		for (int i = 0; i < len; ++i) {
			for (int j = i - 1; j >= 0; --j) {
				long long diff = (long long)nums[i] - nums[j];
				int cnt = 0;
				if (dp[j].count(diff)) cnt = dp[j][diff];
				dp[i][diff] += cnt + 1;
			}
		}
		int ans = 0;
		for (auto m : dp) {
			for (auto p : m) ans += p.second;
		}
		ans -= len * (len - 1) / 2;
		return ans;
	}
};
