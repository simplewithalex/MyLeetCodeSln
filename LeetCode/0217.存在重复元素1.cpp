#include "header.h"

/*

217. 存在重复元素

给你一个整数数组 nums 。如果任一值在数组中出现 至少两次 ，返回 true ；如果数组中每个元素互不相同，返回 false 。

示例 1：
输入：nums = [1,2,3,1]
输出：true

示例 2：
输入：nums = [1,2,3,4]
输出：false

示例 3：
输入：nums = [1,1,1,3,3,4,3,2,4,2]
输出：true

提示：
1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9

*/

// 排序
class Solution1 {
public:
	bool containsDuplicate(vector<int> &nums) {
		sort(nums.begin(), nums.end());
		int len = nums.size();
		for (int i = 0; i < len - 1; ++i) {
			if (nums[i] == nums[i + 1]) return true;
		}
		return false;
	}
};

// 哈希表
class Solution2 {
public:
	bool containsDuplicate(vector<int> &nums) {
		unordered_set<int> s;
		for (auto n : nums) {
			if (s.count(n)) return true;
			s.insert(n);
		}
		return false;
	}
};