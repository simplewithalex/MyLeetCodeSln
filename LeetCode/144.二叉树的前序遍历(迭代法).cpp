#include "header.h"

/*

给定一个二叉树，返回它的前序遍历,通过迭代算法完成

*/

class Solution {
public:
	vector<int> preorderTraversal(TreeNode *root)
	{
		if (!root) return{};
		vector<int> res;
		stack<TreeNode *> s;
		TreeNode *node = root;
		while (!s.empty() || node)
		{
			if (node)
			{
				res.push_back(node->val);
				if (node->right)
					s.push(node->right);
				node = node->left;
			}
			else
			{
				node = s.top();
				s.pop();
			}
		}
		return res;
	}
};
