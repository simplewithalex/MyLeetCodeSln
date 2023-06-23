#include "header.h"

/*

327. 区间和的个数

给你一个整数数组 nums 以及两个整数 lower 和 upper
求数组中，值位于范围 [lower, upper] （包含 lower 和 upper）之内的区间和的个数
区间和 S(i, j) 表示在 nums 中，位置从 i 到 j 的元素之和，包含 i 和 j (i ≤ j)

示例 1：
输入：nums = [-2,5,-1], lower = -2, upper = 2
输出：3
解释：存在三个区间：[0,0]、[2,2] 和 [0,2]，对应的区间和分别是：-2、-1、2

示例 2：
输入：nums = [0], lower = 0, upper = 0
输出：1

提示：
1 <= nums.length <= 10^5
-2^31 <= nums[i] <= 2^31 - 1
-10^5 <= lower <= upper <= 10^5
题目数据保证答案是一个 32 位 的整数

*/

// 归并排序
class Solution1 {
private:
	int lower;
	int upper;
	int ans;

public:
	int countRangeSum(vector<int> &nums, int lower, int upper) {
		int len = nums.size();
		this->lower = lower;
		this->upper = upper;
		this->ans = 0;
		vector<long long> preSum(len + 1);
		for (int i = 1; i <= len; ++i)
			preSum[i] = preSum[i - 1] + nums[i - 1];
		mergeSort(preSum, 0, len);
		return this->ans;
	}

private:
	void mergeSort(vector<long long> &preSum, int lo, int hi) {
		if (lo == hi)
			return;
		int mi = lo + (hi - lo) / 2;
		mergeSort(preSum, lo, mi);
		mergeSort(preSum, mi + 1, hi);
		merge(preSum, lo, mi, hi);
	}
	void merge(vector<long long> &preSum, int lo, int mi, int hi) {
		int start = mi + 1, end = mi + 1;
		for (int i = lo; i <= mi; ++i) {
			while (start <= hi && preSum[start] - preSum[i] < lower)
				++start;
			while (end <= hi && preSum[end] - preSum[i] <= upper)
				++end;
			ans += end - start;
		}

		int leftLen = mi - lo + 1;
		vector<long long> tmp(leftLen);
		for (int idx1 = 0, idx2 = lo; idx1 < leftLen; ++idx1, ++idx2) {
			tmp[idx1] = preSum[idx2];
		}
		int i = 0, j = mi + 1, k = lo;
		while (i < leftLen && j <= hi) {
			if (tmp[i] <= preSum[j])
				preSum[k++] = tmp[i++];
			else
				preSum[k++] = preSum[j++];
		}
		while (i < leftLen)
			preSum[k++] = tmp[i++];
		while (j <= hi)
			preSum[k++] = preSum[j++];
	}
};

// https://lfool.github.io/LFool-Notes/algorithm/%E8%AF%A6%E8%A7%A3%E5%BD%92%E5%B9%B6%E6%8E%92%E5%BA%8F%E5%8F%8A%E5%85%B6%E5%BA%94%E7%94%A8.html

// https://leetcode.cn/problems/count-of-range-sum/solutions/476071/shuo-ming-yi-xia-guan-fang-gui-bing-pai-xu-by-sing/
// @author https://leetcode.cn/u/gebi-giyibiai/

// 构造线段树
struct Node {
	Node *left;
	Node *right;
	int val;
	int add;
	Node() : left(nullptr), right(nullptr), val(0), add(0) {}
};

class Solution2 {
public:
	int countRangeSum(vector<int> &nums, int lower, int upper) {
		int len = nums.size();
		int ans = 0;
		long long sum = 0;
		// 将前缀和作为线段树问题区间，确定问题总区间，起始前缀和为0
		// 前缀和有增减，每个元素依次判断确认最终的区间范围
		long long start = 0, end = 0;
		for (int n : nums) {
			sum += n;
			start = min(min(start, sum), min(sum - lower, sum - upper));
			end = max(max(end, sum), max(sum - lower, sum - upper));
		}

		sum = 0;
		Node *root = new Node();
		// 前缀和为0的情况作为首个区间
		update(root, start, end, 0, 0, 1);
		for (int n : nums) {
			sum += n;
			ans += query(root, start, end, sum - upper, sum - lower);
			update(root, start, end, sum, sum, 1);
		}
		return ans;
	}

private:
	// start与end表示node节点代表的区间, l与r代表需要操作的节点区间
	void update(Node *node, long long start, long long end, long long l,
		long long r, int val) {
		// 点更新优化
		node->val += val;
		if (l <= start && r >= end) return;
		long long mi = start + (end - start) / 2;
		// 针对该问题，主要是点更新操作
		// 这里不执行pushDown，优化时间复杂度
		// pushDown(node, mi - start + 1, end - mi);
		if (l <= mi) {
			if (!node->left) node->left = new Node();
			update(node->left, start, mi, l, r, val);
		}
		if (r > mi) {
			if (!node->right) node->right = new Node();
			update(node->right, mi + 1, end, l, r, val);
		}
		// 点更新可以不使用pushUp的方式
		// pushUp(node);
	}
	int query(Node *node, long long start, long long end, long long l,
		long long r) {
		if (!node) return 0;
		if (l <= start && r >= end) return node->val;
		long long mi = start + (end - start) / 2;
		int ans = 0;
		// 针对该问题，主要是点更新操作
		// 这里不执行pushDown，优化时间复杂度
		// pushDown(node, mi - start + 1, end - mi);
		if (l <= mi) ans += query(node->left, start, mi, l, r);
		if (r > mi) ans += query(node->right, mi + 1, end, l, r);
		return ans;
	}
	// 这里相当于求区间和并在更新时进行加减操作的情况
	void pushDown(Node *node, long long leftNum, long long rightNum) {
		if (!node->left) node->left = new Node();
		if (!node->right) node->right = new Node();
		if (node->add == 0) return;
		// 该问题主要是点更新操作，以下代码一般不会执行
		node->left->val += node->add * leftNum;
		node->right->val += node->add * rightNum;
		node->left->add += node->val;
		node->right->add += node->val;
		node->add = 0;
	}
	void pushUp(Node *node) { node->val = node->left->val + node->right->val; }
};

// https://leetcode.cn/problems/count-of-range-sum/solutions/1500565/by-ac_oier-b36o/
// @author https://leetcode.cn/u/ac_oier/

// https://leetcode.cn/problems/count-of-range-sum/solutions/476205/xian-ren-zhi-lu-ru-he-xue-xi-ke-yi-jie-jue-ben-ti-/
// @author https://leetcode.cn/u/zerotrac2/
