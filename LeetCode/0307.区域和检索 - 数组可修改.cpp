#include "header.h"

/*

307. ����ͼ��� - ������޸�

����һ������nums��������������ѯ
����һ���ѯҪ�� ���� ���� nums �±��Ӧ��ֵ
��һ���ѯҪ�󷵻����� nums ������ left ������ right ֮�䣨 ���� ����numsԪ�ص� �� ������ left <= right

ʵ�� NumArray �ࣺ
NumArray(int[] nums) ���������� nums ��ʼ������
void update(int index, int val) �� nums[index] ��ֵ ���� Ϊ val
int sumRange(int left, int right) �������� nums ������ left ������ right ֮�䣨��������numsԪ�ص� �� ���� nums[left] + nums[left + 1], ..., nums[right]��

ʾ�� 1��
���룺
["NumArray", "sumRange", "update", "sumRange"]
[[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
�����
[null, 9, null, 8]
���ͣ�
NumArray numArray = new NumArray([1, 3, 5]);
numArray.sumRange(0, 2); // ���� 1 + 3 + 5 = 9
numArray.update(1, 2);   // nums = [1,2,5]
numArray.sumRange(0, 2); // ���� 1 + 2 + 5 = 8

��ʾ��
1 <= nums.length <= 3 * 10^4
-100 <= nums[i] <= 100
0 <= index < nums.length
-100 <= val <= 100
0 <= left <= right < nums.length
���� update �� sumRange �������������� 3 * 10^4

*/

// �����߶���
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
	// start��end��ʾnode�ڵ���������, l��r������Ҫ�����Ľڵ�����
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

	// ������������Ͳ��ڸ���ʱ���и��ǲ��������
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



// �������
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
	// start��end��ʾnode�ڵ���������, idx������µĵ�
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
// ĳЩ��Ŀ�������������£������Ż�������²���
// �ο� LeetCode 327 ���ύ���Ż���pushUp����



/**
* Your NumArray object will be instantiated and called as such:
* NumArray* obj = new NumArray(nums);
* obj->update(index,val);
* int param_2 = obj->sumRange(left,right);
*/
