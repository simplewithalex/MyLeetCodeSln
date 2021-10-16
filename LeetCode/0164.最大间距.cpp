#include "header.h"

/*

给定一个无序的数组，找出数组在排序之后，相邻元素之间最大的差值。
如果数组元素个数小于 2，则返回 0

示例 1:
输入: [3,6,9,1]
输出: 3
解释: 排序后的数组是 [1,3,6,9], 其中相邻元素 (3,6) 和 (6,9) 之间都存在最大差值 3

示例 2:
输入: [10]
输出: 0
解释: 数组元素个数小于 2，因此返回 0

说明:
你可以假设数组中所有元素都是非负整数，且数值在 32 位有符号整数范围内。
请尝试在线性时间复杂度和空间复杂度的条件下解决此问题。

*/

// 基数排序
class Solution1 {
public:
	int maximumGap(vector<int> &nums) {
		int len = nums.size();
		if (len < 2) return 0;
		int exp = 1;
		int maxVal = *max_element(nums.begin(), nums.end());
		vector<int> buf(len);
		while (maxVal >= exp) {
			vector<int> cnt(10);
			for (int i = 0; i < len; ++i) {
				int digit = (nums[i] / exp) % 10;
				++cnt[digit];
			}
			for (int i = 1; i < 10; ++i) {
				cnt[i] += cnt[i - 1];
			}
			for (int i = len - 1; i >= 0; --i) {
				int digit = (nums[i] / exp) % 10;
				buf[cnt[digit] - 1] = nums[i];
				--cnt[digit];
			}
			copy(buf.begin(), buf.end(), nums.begin());
			exp *= 10;
		}
		int res = 0;
		for (int i = 1; i < len; ++i) {
			res = max(res, nums[i] - nums[i - 1]);
		}
		return res;
	}
};
// https://leetcode-cn.com/problems/maximum-gap/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by--39/

// 桶排序
class Solution2 {
public:
	int maximumGap(vector<int> &nums) {
		int len = nums.size();
		if (len < 2) return 0;
		int minVal = *min_element(nums.begin(), nums.end());
		int maxVal = *max_element(nums.begin(), nums.end());
		int cap = max(1, (maxVal - minVal) / (len - 1));
		int bucketNum = ((maxVal - minVal) / cap) + 1;
		vector<pair<int, int>> bucket(bucketNum, { -1,-1 });
		for (int i = 0; i < len; ++i) {
			int idx = (nums[i] - minVal) / cap;
			if (bucket[idx].first == -1) {
				bucket[idx] = { nums[i],nums[i] };
			}
			else {
				bucket[idx].first = min(bucket[idx].first, nums[i]);
				bucket[idx].second = max(bucket[idx].second, nums[i]);
			}
		}
		int res = 0, prev = -1;
		for (int i = 0; i < bucketNum; ++i) {
			if (bucket[i].first == -1) continue;
			if (prev != -1) res = max(res, bucket[i].first - bucket[prev].second);
			prev = i;
		}
		return res;
	}
};
// https://leetcode-cn.com/problems/maximum-gap/solution/zui-da-jian-ju-by-leetcode-solution/