#include "header.h"
/*

给定一个大小为 n 的整数数组，找出其中所有出现超过 ⌊ n/3 ⌋ 次的元素。

示例 1：
输入：[3,2,3]
输出：[3]

示例 2：
输入：nums = [1]
输出：[1]

示例 3：
输入：[1,1,1,3,3,2,2,2]
输出：[1,2]

提示：
1 <= nums.length <= 5 * 10^4
-10^9 <= nums[i] <= 10^9

进阶：尝试设计时间复杂度为 O(n)、空间复杂度为 O(1)的算法解决此问题。

*/

class Solution {
public:
	vector<int> majorityElement(vector<int> &nums) {
		if (nums.empty()) return{};
		int len = nums.size();
		int cand1 = 0, cand2 = 0;
		int count1 = 0, count2 = 0;
		for (int n : nums) {
			if (cand1 == n) {
				++count1;
			} else if (cand2 == n) {
				++count2;
			} else if (count1 == 0) {
				cand1 = n;
				++count1;
			} else if (count2 == 0) {
				cand2 = n;
				++count2;
			} else {
				--count1;
				--count2;
			}
		}
		count1 = 0;
		count2 = 0;
		for (int n : nums) {
			if (cand1 == n) ++count1;
			else if (cand2 == n) ++count2;
		}
		vector<int> res;
		if (count1 > len / 3) res.push_back(cand1);
		if (count2 > len / 3) res.push_back(cand2);
		return res;
	}
};
// 该题目是 169. 多数元素 的扩展，使用摩尔投票法
// 宫水三叶：https://leetcode-cn.com/problems/majority-element-ii/solution/gong-shui-san-xie-noxiang-xin-ke-xue-xi-ws0rj/