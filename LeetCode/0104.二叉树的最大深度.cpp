#include "header.h"

/*

给定一个二叉树，找出其最大深度。二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。

说明: 叶子节点是指没有子节点的节点。

示例：

给定二叉树 [3,9,20,null,null,15,7]，

     3
    / \
   9  20
  /  \
 15   7

返回它的最大深度 3 

*/

// 递归
class Solution1 {
public:
	int maxDepth(TreeNode* root) {
		if (root == nullptr) return 0;
		return max(maxDepth(root->left), maxDepth(root->right)) + 1;
	}
};

// 迭代
class Solution2 {
public:
	int maxDepth(TreeNode* root) {
		if (root == nullptr) return 0;
		queue<TreeNode *> q;
		q.push(root);
		int res = 0;
		while (!q.empty()) {
			int len = q.size();
			for (int i = 0; i < len; ++i) {
				TreeNode *temp = q.front();
				q.pop();
				if (temp->left) q.push(temp->left);
				if (temp->right) q.push(temp->right);
			}
			res += 1;
		}
		return res;
	}
};