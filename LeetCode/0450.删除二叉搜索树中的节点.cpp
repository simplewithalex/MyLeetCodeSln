#include "header.h"

/*

450. 删除二叉搜索树中的节点

给定一个二叉搜索树的根节点 root 和一个值 key，删除二叉搜索树中的 key 对应的节点，并保证二叉搜索树的性质不变
返回二叉搜索树（有可能被更新）的根节点的引用

一般来说，删除节点可分为两个步骤：
首先找到需要删除的节点；
如果找到了，删除它

示例 1:
输入：root = [5,3,6,2,4,null,7], key = 3
输出：[5,4,6,2,null,null,7]
解释：给定需要删除的节点值是 3，所以我们首先找到 3 这个节点，然后删除它
一个正确的答案是 [5,4,6,2,null,null,7], 如下图所示
另一个正确答案是 [5,2,6,null,4,null,7]

示例 2:
输入: root = [5,3,6,2,4,null,7], key = 0
输出: [5,3,6,2,4,null,7]
解释: 二叉树不包含值为 0 的节点

示例 3:
输入: root = [], key = 0
输出: []

提示:
节点数的范围 [0, 10^4]
-10^5 <= Node.val <= 10^5
节点值唯一
root 是合法的二叉搜索树
-10^5 <= key <= 10^5

*/

class Solution1 {
public:
	TreeNode *deleteNode(TreeNode *root, int key) {
		if (!root) return root;
		if (root->val < key) {
			root->right = deleteNode(root->right, key);
		}
		else if (root->val > key) {
			root->left = deleteNode(root->left, key);
		}
		else {
			if (!root->left) return root->right;
			if (!root->right) return root->left;
			TreeNode *node = root->left;
			while (node->right) node = node->right;
			root->val = node->val;
			root->left = deleteNode(root->left, root->val);
		}
		return root;
	}
};

// 迭代
class Solution2 {
public:
	TreeNode *deleteNode(TreeNode *root, int key) {
		TreeNode **node = &root;
		while (*node && (*node)->val != key)
			node = (*node)->val < key ? &(*node)->right : &(*node)->left;
		if (!*node) return root;
		TreeNode **s = &(*node)->right;
		while (*s) s = &(*s)->left;
		*s = (*node)->left;
		*node = (*node)->right;
		return root;
	}
};


