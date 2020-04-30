#include "header.h"

/*

给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。

例如，给定如下二叉搜索树:  root = [6,2,8,0,4,7,9,null,null,3,5]

示例 1:

输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
输出: 6
解释: 节点 2 和节点 8 的最近公共祖先是 6。

示例 2:

输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
输出: 2
解释: 节点 2 和节点 4 的最近公共祖先是 2, 因为根据定义最近公共祖先节点可以为节点本身。
  
说明:

所有节点的值都是唯一的。
p、q 为不同节点且均存在于给定的二叉搜索树中。

*/

class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
	{
		while (true)
		{
			if (root->val - p->val > 0 && root->val - q->val > 0)
				root = root->left;
			else if (root->val - p->val < 0 && root->val - q->val < 0)
				root = root->right;
			else
				break;
		}
		return root;
	}
};