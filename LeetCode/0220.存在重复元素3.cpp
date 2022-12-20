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
/*
 * 题目的实际含义为：两个不同元素的下标距离不大于k，元素值大小之差不大于t
 * 题目转换为：我们设元素下标 j 为标识点，查找 j 之前距离为k之内的元素下标 i，大小是否在[Vj - t, Vj + t]区间 
 * 实际上，当我们考虑 i 在 j 之后这种情况时，如果 Vi 在[Vj - t, Vj + t]区间，那么 Vj 也在[Vi - t, Vi + t]区间，此时可以互换 i、j， 
 * 因此只考虑一个方向即可，遍历完成后，也就包括了所有情况了。
 */

// 桶排序
class Solution2 {
public:
	bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t) {
		unordered_map<int, int> mp;
		int len = nums.size();
		for (int i = 0; i < len; ++i) {
			long long n = nums[i];
			int id = getID(n, t + 1LL);
			if (mp.count(id)) return true;
			if (mp.count(id - 1) && abs(n - mp[id - 1]) <= t) return true;
			if (mp.count(id + 1) && abs(n - mp[id + 1]) <= t) return true;
			mp[id] = n;
			if (mp.size() == k + 1) mp.erase(getID(nums[i - k], t + 1LL));
		}
		return false;
	}

private:
	int getID(long long n, long long m) { return n < 0 ? ((n + 1) / m) - 1 : n / m; }
};
// 1. 一个桶内至多只会有一个元素；2. 注意元素值正负数的分组
// https://leetcode-cn.com/problems/contains-duplicate-iii/solution/cun-zai-zhong-fu-yuan-su-iii-by-leetcode-bbkt/