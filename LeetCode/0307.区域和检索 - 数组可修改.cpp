#include "header.h"

/*

307. 区域和检索 - 数组可修改

给你一个数组nums，请你完成两类查询
其中一类查询要求 更新 数组 nums 下标对应的值
另一类查询要求返回数组 nums 中索引 left 和索引 right 之间（ 包含 ）的nums元素的 和 ，其中 left <= right

实现 NumArray 类：
NumArray(int[] nums) 用整数数组 nums 初始化对象
void update(int index, int val) 将 nums[index] 的值 更新 为 val
int sumRange(int left, int right) 返回数组 nums 中索引 left 和索引 right 之间（包含）的nums元素的 和 （即 nums[left] + nums[left + 1], ..., nums[right]）

示例 1：
输入：
["NumArray", "sumRange", "update", "sumRange"]
[[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
输出：
[null, 9, null, 8]
解释：
NumArray numArray = new NumArray([1, 3, 5]);
numArray.sumRange(0, 2); // 返回 1 + 3 + 5 = 9
numArray.update(1, 2);   // nums = [1,2,5]
numArray.sumRange(0, 2); // 返回 1 + 2 + 5 = 8

提示：
1 <= nums.length <= 3 * 10^4
-100 <= nums[i] <= 100
0 <= index < nums.length
-100 <= val <= 100
0 <= left <= right < nums.length
调用 update 和 sumRange 方法次数不大于 3 * 10^4

*/

// 构造线段树
struct Node {
	Node *left;
	Node *right;
	int val;
	int add;
	Node() : left(nullptr), right(nullptr), val(0), add(0) {}
};

class NumArray1 {
public:
	NumArray1(vector<int> &nums) {
		len = nums.size();
		for (int i = 0; i < len; ++i) update(root, 0, len - 1, i, i, nums[i]);
	}

	void update(int index, int val) {
		update(root, 0, len - 1, index, index, val);
	}

	int sumRange(int left, int right) {
		return query(root, 0, len - 1, left, right);
	}

private:
	Node *root = new Node();
	int len = 0;
	// start与end表示node节点代表的区间, l与r代表需要操作的节点区间
	void update(Node *node, int start, int end, int l, int r, int val) {
		if (l <= start && r >= end) {
			node->val = (end - start + 1) * val;
			node->add = val;
			return;
		}
		int mi = start + (end - start) / 2;
		pushDown(node, mi - start + 1, end - mi);
		if (l <= mi) update(node->left, start, mi, l, r, val);
		if (r > mi) update(node->right, mi + 1, end, l, r, val);
		pushUp(node);
	}
	int query(Node *node, int start, int end, int l, int r) {
		if (l <= start && r >= end) return node->val;
		int mi = start + (end - start) / 2, ans = 0;
		pushDown(node, mi - start + 1, end - mi);
		if (l <= mi) ans += query(node->left, start, mi, l, r);
		if (r > mi) ans += query(node->right, mi + 1, end, l, r);
		return ans;
	}

	// 这里是求区间和并在更新时进行覆盖操作的情况
	void pushDown(Node *node, int leftNum, int rightNum) {
		if (!node->left) node->left = new Node();
		if (!node->right) node->right = new Node();
		if (node->add == 0) return;
		node->left->val = node->add * leftNum;
		node->right->val = node->add * rightNum;
		node->left->add = node->val;
		node->right->add = node->val;
		node->add = 0;
	}

	void pushUp(Node *node) { node->val = node->left->val + node->right->val; }
};



// 单点更新
class NumArray2 {
public:
	NumArray2(vector<int> &nums) {
		len = nums.size();
		for (int i = 0; i < len; ++i) update(root, 0, len - 1, i, nums[i]);
	}

	void update(int index, int val) { update(root, 0, len - 1, index, val); }

	int sumRange(int left, int right) {
		return query(root, 0, len - 1, left, right);
	}

private:
	Node *root = new Node();
	int len = 0;
	// start与end表示node节点代表的区间, idx代表更新的点
	void update(Node *node, int start, int end, int idx, int val) {
		if (start == end) {
			node->val = (end - start + 1) * val;
			return;
		}
		int mi = start + (end - start) / 2;
		if (idx <= mi) {
			if (!node->left) node->left = new Node();
			update(node->left, start, mi, idx, val);
		} else {
			if (!node->right) node->right = new Node();
			update(node->right, mi + 1, end, idx, val);
		}
		node->val = 0;
		if (node->left) node->val += node->left->val;
		if (node->right) node->val += node->right->val;
	}
	int query(Node *node, int start, int end, int l, int r) {
		if (l <= start && r >= end) return node->val;
		int mi = start + (end - start) / 2, ans = 0;
		if (l <= mi) ans += query(node->left, start, mi, l, r);
		if (r > mi) ans += query(node->right, mi + 1, end, l, r);
		return ans;
	}
};
// 某些题目在其特殊条件下，可以优化单点更新操作
// 参考 LeetCode 327 的提交，优化了pushUp操作



/**
* Your NumArray object will be instantiated and called as such:
* NumArray* obj = new NumArray(nums);
* obj->update(index,val);
* int param_2 = obj->sumRange(left,right);
*/
