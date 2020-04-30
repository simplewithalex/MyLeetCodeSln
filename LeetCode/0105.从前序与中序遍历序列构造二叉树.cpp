#include "header.h"

/*

根据一棵树的前序遍历与中序遍历构造二叉树。
注意:
你可以假设树中没有重复的元素。

例如，给出

前序遍历 preorder = [3,9,20,15,7]
中序遍历 inorder = [9,3,15,20,7]
返回如下的二叉树：

	3
   / \
  9  20
    /  \
   15   7

*/

class Solution {
public:
	TreeNode * buildTree(vector<int> &preorder, vector<int> &inorder)
	{
		int len = preorder.size();
		if (len == 0) return nullptr;
		return findMiddle(preorder, 0, len - 1, inorder, 0, len - 1);
	}
	TreeNode * findMiddle(vector<int> &preorder, int ps, int pe, vector<int> &inorder, int is, int ie)
	{
		if (ps > pe) return nullptr;
		TreeNode *root = new TreeNode(preorder[ps]);
		int lcnum = 0;
		for (int i = is; inorder[i] != root->val; ++i)
		{
			++lcnum;
		}
		root->left = findMiddle(preorder, ps + 1, ps + lcnum, inorder, is, is + lcnum - 1);
		root->right = findMiddle(preorder, ps + lcnum + 1, pe, inorder, is + lcnum + 1, ie);
		return root;
	}
};