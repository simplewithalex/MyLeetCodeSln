#include "header.h"

/*

给定一个二叉搜索树的根节点 root ，和一个整数 k ，请你设计一个算法查找其中第 k 个最小元素（从 1 开始计数）

示例 1：
输入：root = [3,1,4,null,2], k = 1
输出：1

示例 2：
输入：root = [5,3,6,2,4,null,null,1], k = 3
输出：3

提示：
树中的节点数为 n 。
1 <= k <= n <= 10^4
0 <= Node.val <= 10^4
    
进阶：如果二叉搜索树经常被修改（插入/删除操作）并且你需要频繁地查找第 k 小的值，你将如何优化算法？

*/

// 迭代中序遍历，方便处理得到结果就返回
class Solution1 {
public:
	int kthSmallest(TreeNode *root, int k) {
		stack<TreeNode *> s;
		TreeNode *node = root;
		while (!s.empty() || node) {
			if (node) {
				s.push(node);
				node = node->left;
			} else {
				node = s.top();
				s.pop();
				if (--k == 0) break;
				node = node->right;
			}
		}
		return node->val;
	}
};

// 优化频繁查找k的情况
class Bst {
public:
	Bst(TreeNode *root) {
		this->root = root;
		countNodeNum(root);
	}
	int kthSmallest(int k) {
		TreeNode *node = root;
		while (node) {
			int left = getNodeNum(node->left);
			if (left < k - 1) {
				node = node->right;
				k -= left + 1;
			} else if (left == k - 1) {
				break;
			} else {
				node = node->left;
			}
		}
		return node->val;
	}
private:
	TreeNode *root = nullptr;
	unordered_map<TreeNode *, int> nodeNum;
	int countNodeNum(TreeNode *node) {
		if (!node) return 0;
		nodeNum[node] = 1 + countNodeNum(node->left) + countNodeNum(node->right);
		return nodeNum[node];
	}
	int getNodeNum(TreeNode *node) {
		if (node&&nodeNum.count(node)) return nodeNum[node];
		else return 0;
	}
};

class Solution2 {
public:
	int kthSmallest(TreeNode *root, int k) {
		Bst bst(root);
		return bst.kthSmallest(k);
	}
};

// TODO 对于如果二叉搜索树经常被修改（插入/删除操作）的情况，应考虑构造平衡树

// LeetCode 官方题解：
// https://leetcode-cn.com/problems/kth-smallest-element-in-a-bst/solution/er-cha-sou-suo-shu-zhong-di-kxiao-de-yua-8o07/