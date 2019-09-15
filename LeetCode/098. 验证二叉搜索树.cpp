#include "header.h"

/*

给定一个二叉树，判断其是否是一个有效的二叉搜索树。

假设一个二叉搜索树具有如下特征：
节点的左子树只包含小于当前节点的数。
节点的右子树只包含大于当前节点的数。
所有左子树和右子树自身必须也是二叉搜索树。

*/

class Solution {
public:
	bool isValidBST(TreeNode *root)
	{
		if (!root) return true;
		stack<TreeNode *> s;
		TreeNode *node = root;
		TreeNode *pre = nullptr;
		while (!s.empty() || node)
		{
			if (node)
			{
				s.push(node);
				node = node->left;
			}
			else
			{
				node = s.top();
				s.pop();
				if (pre && node->val <= pre->val)
					return false;
				pre = node;
				node = node->right;
			}
		}
		return true;
	}
};