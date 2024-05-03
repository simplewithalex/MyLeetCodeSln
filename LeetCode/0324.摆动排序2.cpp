#include "header.h"

/*

324. 摆动排序 II

给你一个整数数组nums，将它重新排列成 nums[0] < nums[1] > nums[2] < nums[3]... 的顺序

你可以假设所有输入数组都可以得到满足题目要求的结果

示例 1：
输入：nums = [1,5,1,1,6,4]
输出：[1,6,1,5,1,4]
解释：[1,4,1,5,1,6] 同样是符合题目要求的结果，可以被判题程序接受。

示例 2：
输入：nums = [1,3,2,2,3,1]
输出：[2,3,1,3,1,2]

提示：
1 <= nums.length <= 5 * 10^4
0 <= nums[i] <= 5000
题目数据保证，对于给定的输入nums ，总能产生满足题目要求的结果

进阶：你能用 O(n) 时间复杂度和 / 或原地 O(1) 额外空间来实现吗？

*/

// O(nlogn)
class Solution1 {
public:
	void wiggleSort(vector<int> &nums) {
		vector<int> tmp(nums);
		sort(tmp.begin(), tmp.end());
		int len = nums.size();
		int lo = (len - 1) / 2, hi = len - 1;
		for (int i = 0; i < len; ++i) {
			nums[i] = i & 1 ? tmp[hi--] : tmp[lo--];
		}
	}
};

// O(n)
class Solution2 {
public:
	void wiggleSort(vector<int> &nums) {
		vector<int> buckets(5001);
		for (const int n : nums) ++buckets[n];
		int hi = 5000;
		for (int i = 1; i < nums.size(); i += 2) {
			while (!buckets[hi]) --hi;
			nums[i] = hi;
			--buckets[hi];
		}
		for (int i = 0; i < nums.size(); i += 2) {
			while (!buckets[hi]) --hi;
			nums[i] = hi;
			--buckets[hi];
		}
	}
};


// O(n) + 空间优化
// 快速划分 + 三向切分
class Solution3 {
private:
	int len;
	int mid;

public:
	void wiggleSort(vector<int> &nums) {
		len = nums.size();
		mid = len / 2;
		quickSelect(nums, 0, len - 1, mid);
		int midNum = nums[mid];
		// 添加地索引转换的三向切分算法
		// 仍然按照原始索引从小到大排列，但最终结果相当于
		// 把大的数放在1 3 5 7，小的数放在2 4 6 8
		int lo = 0, hi = len - 1, k = 0;
		while (k <= hi) {
			if (nums[getIdx(k)] > midNum) {
				swap(nums[getIdx(k++)], nums[getIdx(lo++)]);
			} else if (nums[getIdx(k)] < midNum) {
				swap(nums[getIdx(k)], nums[getIdx(hi--)]);
			} else {
				++k;
			}
		}
	}

private:
	void quickSelect(vector<int> &nums, int lo, int hi, int mi) {
		int index = partition(nums, lo, hi);
		while (index != mi) {
			if (index > mi) {
				hi = index - 1;
				index = partition(nums, lo, hi);
			}
			else {
				lo = index + 1;
				index = partition(nums, lo, hi);
			}
		}
	}
	int partition(vector<int> &nums, int lo, int hi) {
		swap(nums[lo], nums[lo + rand() % (hi - lo + 1)]);
		int pivot = nums[lo];
		while (lo < hi) {
			while (lo < hi) {
				if (pivot < nums[hi]) --hi;
				else {
					nums[lo++] = nums[hi];
					break;
				}
			}
			while (lo < hi) {
				if (pivot > nums[lo]) ++lo;
				else {
					nums[hi--] = nums[lo];
					break;
				}
			}
		}
		nums[lo] = pivot;
		return lo;
	}
	int getIdx(int x) { return (2 * x + 1) % (len | 1); }
};
