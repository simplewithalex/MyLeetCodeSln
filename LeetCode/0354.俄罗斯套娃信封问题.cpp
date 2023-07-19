#include "header.h"

/*

354. 俄罗斯套娃信封问题

给你一个二维整数数组 envelopes，其中 envelopes[i] = [wi, hi] ，表示第 i 个信封的宽度和高度

当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封里，如同俄罗斯套娃一样

请计算最多能有多少个信封能组成一组“俄罗斯套娃”信封（即可以把一个信封放到另一个信封里面）

注意：不允许旋转信封

示例 1：
输入：envelopes = [[5,4],[6,4],[6,7],[2,3]]
输出：3
解释：最多信封的个数为 3, 组合为: [2,3] => [5,4] => [6,7]。

示例 2：
输入：envelopes = [[1,1],[1,1],[1,1]]
输出：1

提示：
1 <= envelopes.length <= 10^5
envelopes[i].length == 2
1 <= wi, hi <= 10^5

*/



class Solution {
public:
	int maxEnvelopes(vector<vector<int>> &envelopes) {
		sort(envelopes.begin(), envelopes.end(),
			[](const vector<int> &a, const vector<int> &b) {
			return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
		});

		// 0300题模板
		int len = envelopes.size();
		vector<int> dp(len, 0);
		int res = 0;
		for (const auto &v : envelopes) {
			int lo = 0, hi = res;
			lo = biSearch(dp, lo, hi, v[1]);
			if (lo == 0 || dp[lo - 1] < v[1]) {
				dp[lo] = v[1];
				if (res == lo) ++res;
			}
		}
		return res;
	}

private:
	// 二分查找第一个大于等于target的位置
	int biSearch(vector<int> &nums, int lo, int hi, int target) {
		while (lo < hi) {
			int mi = lo + ((hi - lo) >> 1);
			(target < nums[mi]) ? hi = mi : lo = mi + 1;
		}
		return lo;
	}
};
// https://leetcode.cn/problems/russian-doll-envelopes/solutions/19681/zui-chang-di-zeng-zi-xu-lie-kuo-zhan-dao-er-wei-er/
// @author https://leetcode.cn/u/labuladong/