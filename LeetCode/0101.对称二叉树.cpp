#include "header.h"

/*

给定一个二叉树，检查它是否是镜像对称的。例如，二叉树 [1,2,2,3,4,4,3] 是对称的。

	1
   / \
  2   2
 / \ / \
3  4 4  3
  
但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:

   1
  / \
 2   2
  \   \
   3    3
   

进阶：
你可以运用递归和迭代两种方法解决这个问题吗？

*/

// 递归
class Solution1 {
public:
	bool isSymmetric(TreeNode *root) {
		if (!root) return true;
		return helper(root->left, root->right);
	}
	bool helper(TreeNode *lc, TreeNode *rc) {
		if (!lc || !rc) return lc == rc;
		else if (lc->val != rc->val) return false;
		else return helper(lc->left, rc->right) && helper(lc->right, rc->left);
	}
};


// 迭代
class Solution2 {
public:
	bool isSymmetric(TreeNode *root) {
		if (!root) return true;
		TreeNode *lc = root, *rc = root;
		queue<TreeNode *> q;
		q.push(lc);
		q.push(rc);
		while (!q.empty()) {
			lc = q.front();
			q.pop();
			rc = q.front();
			q.pop();
			if (!lc && !rc) continue;
			if ((!lc || !rc) || (lc->val != rc->val)) return false;
			q.push(lc->left);
			q.push(rc->right);
			q.push(lc->right);
			q.push(rc->left);
		}
		return true;
	}
};