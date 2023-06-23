#include "header.h"

/*

327. ����͵ĸ���

����һ���������� nums �Լ��������� lower �� upper
�������У�ֵλ�ڷ�Χ [lower, upper] ������ lower �� upper��֮�ڵ�����͵ĸ���
����� S(i, j) ��ʾ�� nums �У�λ�ô� i �� j ��Ԫ��֮�ͣ����� i �� j (i �� j)

ʾ�� 1��
���룺nums = [-2,5,-1], lower = -2, upper = 2
�����3
���ͣ������������䣺[0,0]��[2,2] �� [0,2]����Ӧ������ͷֱ��ǣ�-2��-1��2

ʾ�� 2��
���룺nums = [0], lower = 0, upper = 0
�����1

��ʾ��
1 <= nums.length <= 10^5
-2^31 <= nums[i] <= 2^31 - 1
-10^5 <= lower <= upper <= 10^5
��Ŀ���ݱ�֤����һ�� 32 λ ������

*/

// �鲢����
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
	int countRangeSum(vector<int> &nums, int lower, int upper) {
		int len = nums.size();
		int ans = 0;
		long long sum = 0;
		// ��ǰ׺����Ϊ�߶����������䣬ȷ�����������䣬��ʼǰ׺��Ϊ0
		// ǰ׺����������ÿ��Ԫ�������ж�ȷ�����յ����䷶Χ
		long long start = 0, end = 0;
		for (int n : nums) {
			sum += n;
			start = min(min(start, sum), min(sum - lower, sum - upper));
			end = max(max(end, sum), max(sum - lower, sum - upper));
		}

		sum = 0;
		Node *root = new Node();
		// ǰ׺��Ϊ0�������Ϊ�׸�����
		update(root, start, end, 0, 0, 1);
		for (int n : nums) {
			sum += n;
			ans += query(root, start, end, sum - upper, sum - lower);
			update(root, start, end, sum, sum, 1);
		}
		return ans;
	}

private:
	// start��end��ʾnode�ڵ���������, l��r������Ҫ�����Ľڵ�����
	void update(Node *node, long long start, long long end, long long l,
		long long r, int val) {
		// ������Ż�
		node->val += val;
		if (l <= start && r >= end) return;
		long long mi = start + (end - start) / 2;
		// ��Ը����⣬��Ҫ�ǵ���²���
		// ���ﲻִ��pushDown���Ż�ʱ�临�Ӷ�
		// pushDown(node, mi - start + 1, end - mi);
		if (l <= mi) {
			if (!node->left) node->left = new Node();
			update(node->left, start, mi, l, r, val);
		}
		if (r > mi) {
			if (!node->right) node->right = new Node();
			update(node->right, mi + 1, end, l, r, val);
		}
		// ����¿��Բ�ʹ��pushUp�ķ�ʽ
		// pushUp(node);
	}
	int query(Node *node, long long start, long long end, long long l,
		long long r) {
		if (!node) return 0;
		if (l <= start && r >= end) return node->val;
		long long mi = start + (end - start) / 2;
		int ans = 0;
		// ��Ը����⣬��Ҫ�ǵ���²���
		// ���ﲻִ��pushDown���Ż�ʱ�临�Ӷ�
		// pushDown(node, mi - start + 1, end - mi);
		if (l <= mi) ans += query(node->left, start, mi, l, r);
		if (r > mi) ans += query(node->right, mi + 1, end, l, r);
		return ans;
	}
	// �����൱��������Ͳ��ڸ���ʱ���мӼ����������
	void pushDown(Node *node, long long leftNum, long long rightNum) {
		if (!node->left) node->left = new Node();
		if (!node->right) node->right = new Node();
		if (node->add == 0) return;
		// ��������Ҫ�ǵ���²��������´���һ�㲻��ִ��
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
