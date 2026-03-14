#include "header.h"

/*

2426. 满足不等式的数对数目

给你两个下标从 0 开始的整数数组 nums1 和 nums2 ，两个数组的大小都为 n ，同时给你一个整数 diff ，统计满足以下条件的 数对 (i, j) ：
0 <= i < j <= n - 1 且
nums1[i] - nums1[j] <= nums2[i] - nums2[j] + diff
请你返回满足条件的 数对数目

示例 1：
输入：nums1 = [3,2,5], nums2 = [2,2,1], diff = 1
输出：3
解释：
总共有 3 个满足条件的数对：
1. i = 0, j = 1：3 - 2 <= 2 - 2 + 1 。因为 i < j 且 1 <= 1 ，这个数对满足条件
2. i = 0, j = 2：3 - 5 <= 2 - 1 + 1 。因为 i < j 且 -2 <= 2 ，这个数对满足条件
3. i = 1, j = 2：2 - 5 <= 2 - 1 + 1 。因为 i < j 且 -3 <= 2 ，这个数对满足条件
所以，我们返回 3

示例 2：
输入：nums1 = [3,-1], nums2 = [-2,2], diff = -1
输出：0
解释：
没有满足条件的任何数对，所以我们返回 0

提示：
n == nums1.length == nums2.length
2 <= n <= 10^5
-10^4 <= nums1[i], nums2[i] <= 10^4
-10^4 <= diff <= 10^4

*/

// 二分查找
class Solution1 {
public:
	long long numberOfPairs(vector<int> &nums1, vector<int> &nums2, int diff) {
		int len = nums1.size();
		vector<int> df(len);
		for (int i = 0; i < len; ++i) df[i] = nums1[i] - nums2[i];
		long long ans = 0;
		vector<int> sortarr;
		for (int i = 0; i < len; ++i) {
			int tar = df[i];
			int lo = 0, hi = sortarr.size() - 1;
			while (lo < hi) {
				int mi = lo + (hi - lo) / 2;
				sortarr[mi] <= tar ? lo = mi + 1 : hi = mi;
			}
			ans += (lo < sortarr.size() && sortarr[lo] <= tar) ? lo + 1 : lo;
			tar = df[i] - diff;
			lo = 0, hi = sortarr.size() - 1;
			while (lo < hi) {
				int mi = lo + (hi - lo) / 2;
				sortarr[mi] <= tar ? lo = mi + 1 : hi = mi;
			}
			sortarr.insert((lo < sortarr.size() && sortarr[lo] <= tar)
				? sortarr.begin() + lo + 1
				: sortarr.begin() + lo, tar);
		}
		return ans;
	}
};

// 翻转对 + 归并排序
class Solution2 {
public:
	vector<int> temp;
	long long ans = 0;
	int diff = 0;
	long long numberOfPairs(vector<int> &nums1, vector<int> &nums2, int diff) {
		int len = nums1.size();
		temp.resize(len);
		vector<int> df(len);
		for (int i = 0; i < len; ++i) df[i] = nums1[i] - nums2[i];
		this->diff = diff;
		sort(df, 0, len - 1);
		return ans;
	}
	void sort(vector<int> &nums, int lo, int hi) {
		if (lo == hi) return;
		int mi = lo + (hi - lo) / 2;
		sort(nums, lo, mi);
		sort(nums, mi + 1, hi);
		merge(nums, lo, mi, hi);
	}
	void merge(vector<int> &nums, int lo, int mi, int hi) {
		for (int i = lo; i <= hi; ++i) temp[i] = nums[i];
		int end = lo;
		for (int i = mi + 1; i <= hi; ++i) {
			while (end <= mi && temp[end] - diff <= temp[i]) ++end;
			ans += end - lo;
		}
		int i = lo, j = mi + 1, idx = lo;
		while (i <= mi && j <= hi) {
			if (temp[i] <= temp[j]) nums[idx++] = temp[i++];
			else nums[idx++] = temp[j++];
		}
		while (i <= mi) nums[idx++] = temp[i++];
	}
};

// 线段树单点更新
struct Node {
	Node *left;
	Node *right;
	int val;
	Node() : left(nullptr), right(nullptr), val(0) {}
};
class Solution3 {
public:
	int N = 1E9;
	Node *root = new Node();
	void update(Node *node, int start, int end, int idx, int val) {
		if (start == end) {
			node->val += val;
			return;
		}
		int mi = start + (end - start) / 2;
		if (!node->left) node->left = new Node();
		if (!node->right) node->right = new Node();
		if (idx <= mi) update(node->left, start, mi, idx, val);
		else update(node->right, mi + 1, end, idx, val);
		node->val = node->left->val + node->right->val;
	}
	int query(Node *node, int start, int end, int l, int r) {
		if (!node) return 0;
		if (l <= start && end <= r) return node->val;
		int mi = start + (end - start) / 2, ans = 0;
		if (l <= mi) ans += query(node->left, start, mi, l, r);
		if (r > mi) ans += query(node->right, mi + 1, end, l, r);
		return ans;
	}
	long long numberOfPairs(vector<int> &nums1, vector<int> &nums2, int diff) {
		int len = nums1.size();
		int move = 3 * 1E4;
		long long ans = 0;
		for (int i = 0; i < len; ++i) {
			int d = nums1[i] - nums2[i];
			int target = d + diff;
			ans += query(root, 0, N, 0, target + move);
			update(root, 0, N, d + move, 1);
		}
		return ans;
	}
};

