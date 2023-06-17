#include "header.h"

/*

给定长度分别为 m 和 n 的两个数组，其元素由 0-9 构成，表示两个自然数各位上的数字。

现在从这两个数组中选出 k (k <= m + n) 个数字拼接成一个新的数，要求从同一个数组中取出的数字保持其在原数组中的相对顺序。

求满足该条件的最大数。结果返回一个表示该最大数的长度为 k 的数组。

说明: 请尽可能地优化你算法的时间和空间复杂度。

示例 1:
输入:
nums1 = [3, 4, 6, 5]
nums2 = [9, 1, 2, 5, 8, 3]
k = 5
输出:
[9, 8, 6, 5, 3]

示例 2:
输入:
nums1 = [6, 7]
nums2 = [6, 0, 4]
k = 5
输出:
[6, 7, 6, 0, 4]

示例 3:
输入:
nums1 = [3, 9]
nums2 = [8, 9]
k = 3
输出:
[9, 8, 9]

*/

class Solution {
public:
	vector<int> maxNumber(vector<int> &nums1, vector<int> &nums2, int k) {
		int len1 = nums1.size(), len2 = nums2.size();
		int start = max(0, k - len2), end = min(len1, k);
		vector<int> res(k, 0);
		for (int i = start; i <= end; ++i) {
			vector<int> s1(getMonoStack(nums1, i));
			vector<int> s2(getMonoStack(nums2, k - i));
			vector<int> tmp(merge(s1, s2));
			if (compare(tmp, 0, res, 0) > 0) swap(res, tmp);
		}
		return res;
	}

private:
	// 单调栈
	vector<int> getMonoStack(vector<int> nums, int k) {
		vector<int> s;
		int len = nums.size();
		int drop_num = len - k;
		for (int n : nums) {
			while (!s.empty() && s.back() < n && drop_num > 0) {
				s.pop_back();
				--drop_num;
			}
			if (s.size() < k) s.push_back(n);
			else --drop_num;
		}
		return s;
	}
	int compare(vector<int> &nums1, int idx1, vector<int> &nums2, int idx2) {
		int len1 = nums1.size(), len2 = nums2.size();
		while (idx1 < len1 && idx2 < len2) {
			int tag = nums1[idx1++] - nums2[idx2++];
			if (tag != 0) return tag;
		}
		return (len1 - idx1) - (len2 - idx2);
	}
	vector<int> merge(vector<int> &nums1, vector<int> &nums2) {
		int len1 = nums1.size(), len2 = nums2.size();
		if (!len1) return nums2;
		if (!len2) return nums1;
		int len = len1 + len2;
		int idx1 = 0, idx2 = 0, i = 0;
		vector<int> res(len, 0);
		while (i < len) {
			if (compare(nums1, idx1, nums2, idx2) > 0) res[i++] = nums1[idx1++];
			else res[i++] = nums2[idx2++];
		}
		return res;
	}
};
// https://leetcode.cn/problems/create-maximum-number/solutions/506465/tu-jie-suan-fa-zhe-ge-dan-diao-zhan-bu-yi-ban-by-t/
// @author https://leetcode.cn/u/treasure_/
