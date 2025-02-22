#include "header.h"

/*

398. 随机数索引

给你一个可能含有 重复元素 的整数数组 nums ，请你随机输出给定的目标数字 target 的索引
你可以假设给定的数字一定存在于数组中

实现 Solution 类：
Solution(int[] nums) 用数组 nums 初始化对象
int pick(int target) 从 nums 中选出一个满足 nums[i] == target 的随机索引 i
如果存在多个有效的索引，则每个索引的返回概率应当相等

示例：
输入
["Solution", "pick", "pick", "pick"]
[[[1, 2, 3, 3, 3]], [3], [1], [3]]
输出
[null, 4, 0, 2]
解释
Solution solution = new Solution([1, 2, 3, 3, 3]);
solution.pick(3); // 随机返回索引 2, 3 或者 4 之一。每个索引的返回概率应该相等
solution.pick(1); // 返回 0 。因为只有 nums[0] 等于 1
solution.pick(3); // 随机返回索引 2, 3 或者 4 之一。每个索引的返回概率应该相等

提示：
1 <= nums.length <= 2 * 10^4
-2^31 <= nums[i] <= 2^31 - 1
target 是 nums 中的一个整数
最多调用 pick 函数 10^4 次

*/


class Solution1 {
public:
	unordered_map<int, vector<int>> pos;
	Solution1(vector<int> &nums) {
		for (int i = 0; i < nums.size(); ++i) {
			pos[nums[i]].push_back(i);
		}
	}

	int pick(int target) {
		const auto &indices = pos[target];
		return indices[rand() % indices.size()];
	}
};

// 水塘抽样（TLE）
// 如果数组以文件形式存储（读者可假设构造函数传入的是个文件路径），且文件大小远超内存大小
// 我们是无法通过读文件的方式，将所有下标保存在内存中的，因此需要找到一种空间复杂度更低的算法
class Solution2 {
public:
	vector<int> &nums;
	Solution2(vector<int> &nums) : nums(nums) {}

	int pick(int target) {
		int ans = 0;
		for (int i = 0, cnt = 0; i < nums.size(); ++i) {
			if (nums[i] == target) {
				++cnt;
				if (rand() % cnt == 0) ans = i;
			}
		}
		return ans;
	}
};

/**
* Your Solution object will be instantiated and called as such:
* Solution* obj = new Solution(nums);
* int param_1 = obj->pick(target);
*/


