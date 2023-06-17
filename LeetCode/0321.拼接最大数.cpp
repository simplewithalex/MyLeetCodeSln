#include "header.h"

/*

�������ȷֱ�Ϊ m �� n ���������飬��Ԫ���� 0-9 ���ɣ���ʾ������Ȼ����λ�ϵ����֡�

���ڴ�������������ѡ�� k (k <= m + n) ������ƴ�ӳ�һ���µ�����Ҫ���ͬһ��������ȡ�������ֱ�������ԭ�����е����˳��

���������������������������һ����ʾ��������ĳ���Ϊ k �����顣

˵��: �뾡���ܵ��Ż����㷨��ʱ��Ϳռ临�Ӷȡ�

ʾ�� 1:
����:
nums1 = [3, 4, 6, 5]
nums2 = [9, 1, 2, 5, 8, 3]
k = 5
���:
[9, 8, 6, 5, 3]

ʾ�� 2:
����:
nums1 = [6, 7]
nums2 = [6, 0, 4]
k = 5
���:
[6, 7, 6, 0, 4]

ʾ�� 3:
����:
nums1 = [3, 9]
nums2 = [8, 9]
k = 3
���:
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
	// ����ջ
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
