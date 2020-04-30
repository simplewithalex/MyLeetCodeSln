#include "header.h"

/*

给定两个二叉树，编写一个函数来检验它们是否相同。
如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。

*/
class Solution {
public:
	bool isSameTree(TreeNode *p, TreeNode *q)
	{
		if (!p || !q) return p == q;
		if (p->val == q->val)
			return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
		return false;
	}
};