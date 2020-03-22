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

class Solution1 {
public:
	vector<int> inorderTraversal(TreeNode *root)
	{
		if (!root) return {};
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

//使用莫里斯遍历法
class Solution2 {
public:
	vector<int> inorderTraversal(TreeNode* root)
	{
		vector<int> res;
		TreeNode *cur = root, *pre = nullptr;
		while (cur)
		{
			if (!cur->left)
			{
				res.push_back(cur->val);
				cur = cur->right;
			}
			else
			{
				pre = cur->left;
				while (pre->right&&pre->right != cur)
				{
					pre = pre->right;
				}
				if (!pre->right)
				{
					pre->right = cur;
					cur = cur->left;
				}
				else
				{
					pre->right = nullptr;
					res.push_back(cur->val);
					cur = cur->right;
				}
			}
		}
		return res;
	}
};
//非递归，不用栈，O(1)空间，需要用到Morris中序遍历。
//参考https://www.cnblogs.com/AnnieKim/archive/2013/06/15/MorrisTraversal.html