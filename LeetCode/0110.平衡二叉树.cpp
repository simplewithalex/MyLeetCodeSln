#include "header.h"

/*

给定一个二叉树，判断它是否是高度平衡的二叉树。
本题中，一棵高度平衡二叉树定义为：
一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过1。

*/

class Solution {
public:
	bool isBalanced(TreeNode *root)
	{
		return travpost(root) != -1;
	}
	int travpost(TreeNode *node)
	{
		if (!node) return 0;
		int lheight = 0, rheight = 0;
		lheight = travpost(node->left);
		if (lheight == -1) return -1;
		rheight = travpost(node->right);
		if (rheight == -1) return -1;
		if (abs(lheight - rheight) > 1)
			return -1;
		return 1 + max(lheight, rheight);
	}
};