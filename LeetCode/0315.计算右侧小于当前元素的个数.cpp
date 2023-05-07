#include "header.h"

/*

315. �����Ҳ�С�ڵ�ǰԪ�صĸ���

����һ���������� nums����Ҫ�󷵻�һ�������� counts
���� counts �и����ʣ� counts[i] ��ֵ��  nums[i] �Ҳ�С�� nums[i] ��Ԫ�ص�������

ʾ�� 1��
���룺nums = [5,2,6,1]
�����[2,1,1,0]
���ͣ�
5 ���Ҳ��� 2 ����С��Ԫ�� (2 �� 1)
2 ���Ҳ���� 1 ����С��Ԫ�� (1)
6 ���Ҳ��� 1 ����С��Ԫ�� (1)
1 ���Ҳ��� 0 ����С��Ԫ��

ʾ�� 2��
���룺nums = [-1]
�����[0]

ʾ�� 3��
���룺nums = [-1,-1]
�����[0,0]

��ʾ��
1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4

*/

// ������������鲢����
class Solution1 {
public:
	vector<int> countSmaller(vector<int> &nums) {
		int len = nums.size();
		vector<int> count(len);
		// ����һ��ר���ڹ鲢������indexes���������д�ŵ���ԭ���������
		// �������Ϊ������ϣ���е�key������ֵ��С��key��������
		vector<int> indexes(len);
		for (int i = 0; i < len; ++i) indexes[i] = i;
		mergeSort(indexes, 0, len - 1, count, nums);
		return count;
	}

private:
	void merge(vector<int> &indexes, int lo, int hi, int mi, vector<int> &count,
		vector<int> &nums) {
		int leftLen = mi - lo + 1;
		vector<int> ltemp(leftLen);
		for (int idx1 = 0, idx2 = lo; idx1 < leftLen; ++idx1, ++idx2) {
			ltemp[idx1] = indexes[idx2];
		}
		int i = 0, j = mi + 1, k = lo;
		while (i < leftLen && j <= hi) {
			if (nums[ltemp[i]] <= nums[indexes[j]]) {
				indexes[k] = ltemp[i];
				count[indexes[k]] += j - mi - 1;
				++k, ++i;
			}
			else {
				indexes[k++] = indexes[j++];
			}
		}
		while (i < leftLen) {
			indexes[k] = ltemp[i];
			count[indexes[k]] += j - mi - 1;
			++k, ++i;
		}
		while (j <= hi) {
			indexes[k++] = indexes[j++];
		}
	}
	void mergeSort(vector<int> &indexes, int lo, int hi, vector<int> &count,
		vector<int> &nums) {
		if (lo == hi) return;
		int mi = lo + (hi - lo) / 2;
		mergeSort(indexes, lo, mi, count, nums);
		mergeSort(indexes, mi + 1, hi, count, nums);
		if (nums[indexes[mi]] <= nums[indexes[mi + 1]]) return;
		merge(indexes, lo, hi, mi, count, nums);
	}
};

// https://leetcode.cn/problems/count-of-smaller-numbers-after-self/solutions/9082/gui-bing-pai-xu-suo-yin-shu-zu-python-dai-ma-java-/
// @author https://leetcode.cn/u/liweiwei1419/


// �����߶���
struct Node {
	Node *left;
	Node *right;
	int val;
	int add;
	Node() : left(nullptr), right(nullptr), val(0), add(0) {}
};

class Solution2 {
public:
	vector<int> countSmaller(vector<int> &nums) {
		int len = nums.size();
		vector<int> count(len);
		int minNum = nums[0], maxNum = nums[0];
		for (int i = 1; i < len; ++i) {
			minNum = min(minNum, nums[i]);
			maxNum = max(maxNum, nums[i]);
		}
		Node *root = new Node();
		for (int i = len - 1; i >= 0; --i) {
			int cur = nums[i] - 1;
			count[i] = cur >= minNum ? query(root, minNum, maxNum, minNum, cur) : 0;
			update(root, minNum, maxNum, nums[i], nums[i], 1);
		}
		return count;
	}

private:
	void pushUp(Node *node) { node->val = node->left->val + node->right->val; }

	void pushDown(Node *node, int leftNum, int rightNum) {
		if (!node->left) node->left = new Node();
		if (!node->right) node->right = new Node();
		if (node->add == 0) return;
		node->left->val += node->add * leftNum;
		node->right->val += node->add * rightNum;
		node->left->add += node->add;
		node->right->add += node->add;
		node->add = 0;
	}

	void update(Node *node, int start, int end, int l, int r, int val) {
		if (l <= start && r >= end) {
			node->val += val * (end - start + 1);
			node->add += val;
			return;
		}
		int mi = start + (end - start) / 2;
		pushDown(node, mi - start + 1, end - mi);
		if (l <= mi) update(node->left, start, mi, l, r, val);
		if (r > mi) update(node->right, mi + 1, end, l, r, val);
		pushUp(node);
	}

	int query(Node *node, int start, int end, int l, int r) {
		if (l <= start && end <= r) return node->val;
		int mi = start + (end - start) / 2, ans = 0;
		pushDown(node, mi - start + 1, end - mi);
		if (l <= mi) ans = query(node->left, start, mi, l, r);
		if (r > mi) ans += query(node->right, mi + 1, end, l, r);
		return ans;
	}
};

// https://leetcode.cn/problems/my-calendar-i/solutions/1646079/by-lfool-xvpv/
// @author https://leetcode.cn/u/lfool/
// https://leetcode.cn/problems/count-of-smaller-numbers-after-self/solutions/127636/c-xian-duan-shu-jie-fa-by-dufre/
// @author https://leetcode.cn/u/dufre/
