#include "header.h"

/*

给定一个二叉树，返回它的后序遍历。
使用迭代算法完成。

*/

class Solution {
public:
	vector<int> postorderTraversal(TreeNode *root)
	{
		if (!root) return{};
		vector<int> res;
		stack<TreeNode *> s;
		TreeNode *node = root;
		s.push(node);
		while (!s.empty())
		{
			if (s.top()->left != node&&s.top()->right != node)
			{
				while (TreeNode *x = s.top())
				{
					if (x->left)
					{
						if (x->right)
							s.push(x->right);
						s.push(x->left);
					}
					else
						s.push(x->right);
				}
				s.pop();
			}
			node = s.top();
			s.pop();
			res.push_back(node->val);
		}
		return res;
	}
};