#include "header.h"

/*

220. 存在重复元素 III

给你一个整数数组 nums 和两个整数 k 和 t 。请你判断是否存在 两个不同下标 i 和 j，使得 abs(nums[i] - nums[j]) <= t ，同时又满足 abs(i - j) <= k 。
如果存在则返回 true，不存在返回 false。

示例 1：
输入：nums = [1,2,3,1], k = 3, t = 0
输出：true

示例 2：
输入：nums = [1,0,1,1], k = 1, t = 2
输出：true

示例 3：
输入：nums = [1,5,9,1,5,9], k = 2, t = 3
输出：false

提示：
0 <= nums.length <= 2 * 10^4
-2^31 <= nums[i] <= 2^31 - 1
0 <= k <= 10^4
0 <= t <= 2^31 - 1

*/

// 滑动窗口 + 有序集合
class Solution1 {
public:
	bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t) {
		int len = nums.size();
		set<int> s;
		for (int i = 0; i < len; ++i) {
			auto it = s.lower_bound(max(nums[i], INT_MIN + t) - t);
			if (it != s.end() && *it <= (min(nums[i], INT_MAX - t) + t)) return true;
			s.insert(nums[i]);
			if (s.size() == k + 1) s.erase(nums[i - k]);
		}
		return false;
	}
};

// 桶排序
class Solution2 {
public:
	bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t) {
		unordered_map<int, int> bucket;
		int len = nums.size();
		for (int i = 0; i < len; ++i) {
			long long n = nums[i];
			int id = getID(n, t + 1LL);
			if (bucket.count(id)) return true;
			if (bucket.count(id - 1) && abs(n - bucket[id - 1]) <= t) return true;
			if (bucket.count(id + 1) && abs(n - bucket[id + 1]) <= t) return true;
			bucket[id] = n;
			if (bucket.size() == k + 1) bucket.erase(getID(nums[i - k], t + 1LL));
		}
		return false;
	}

private:
	int getID(long long n, long long m) { return n < 0 ? ((n + 1) / m) - 1 : n / m; }
};
// 1. 一个桶内至多只会有一个元素；2. 注意元素值正负数的分组
// https://leetcode-cn.com/problems/contains-duplicate-iii/solution/cun-zai-zhong-fu-yuan-su-iii-by-leetcode-bbkt/