#include "header.h"

/*

给定一个二叉树，返回它的中序遍历。

示例:
输入: [1,null,2,3]
	1
	 \
	  2
	 /
	3

输出: [1,3,2]

进阶: 递归算法很简单，你可以通过迭代算法完成吗？

*/

class Solution {
public:
	vector<int> inorderTraversal(TreeNode *root)
	{
		if (!root) return{};
		stack<TreeNode *> s;
		vector<int> res;
		TreeNode *node = root;
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
				res.push_back(node->val);
				node = node->right;
			}
		}
		return res;
	}
};