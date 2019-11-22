#include "header.h"

/*

给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。
请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。
你可以假设 nums1 和 nums2 不会同时为空。

示例 1:
nums1 = [1, 3]
nums2 = [2]
则中位数是 2.0

示例 2:
nums1 = [1, 2]
nums2 = [3, 4]
则中位数是 (2 + 3)/2 = 2.5

*/

class Solution {
public:
	double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
	{
		int len1 = nums1.size(), len2 = nums2.size();
		if (len1 > len2) return findMedianSortedArrays(nums2, nums1);
		int i = 0, j = 0;
		int lo = 0, hi = len1;
		//i + j == len1 - i + len2 - j(len1 + len2为偶数) 或 len1 - i + len2 - j + 1(len1 + len2为奇数)
		//2(i + j) == len1 + len2 或 len1 + len2 + 1，所以 i + j == (len1 + len2 + 1) >> 1
		int half = (len1 + len2 + 1) >> 1;
		while (lo <= hi)
		{
			i = lo + ((hi - lo) >> 1);
			j = half - i;
			if (i > 0 && j < len2 && nums1[i - 1] > nums2[j])
				lo = i - 1;
			else if (j > 0 && i < len1 && nums2[j - 1] > nums1[i])
				hi = i + 1;
			else
			{
				int left = 0, right = 0;
				if (i == 0)
					left = nums2[j - 1];
				else if (j == 0)
					left = nums1[i - 1];
				else
					left = max(nums1[i - 1], nums2[j - 1]);

				//如果长度为奇数，则不用考虑右半部分。
				if ((len1 + len2) & 1) return left;
				//如果长度为偶数，需要考虑右边部分。
				if (i == len1)
					right = nums2[j];
				else if (j == len2)
					right = nums1[i];
				else
					right = min(nums1[i], nums2[j]);
				return (left + right) / 2.0;
			}
		}
		return 0.0;
	}
};

//https://leetcode-cn.com/problems/median-of-two-sorted-arrays/solution/xun-zhao-liang-ge-you-xu-shu-zu-de-zhong-wei-shu-b/
//https://leetcode-cn.com/problems/median-of-two-sorted-arrays/solution/he-bing-yi-hou-zhao-gui-bing-guo-cheng-zhong-zhao-/