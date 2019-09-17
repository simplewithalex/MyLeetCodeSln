#include "header.h"

/*

给定一个二叉树，返回它的后序遍历。
使用迭代算法完成。

*/

class Solution1 {
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


//使用莫里斯遍历法
class Solution2 {
public:
	vector<int> postorderTraversal(TreeNode *root) 
	{
		vector<int> res;
		TreeNode *dummy = new TreeNode(-1);
		dummy->left = root;
		TreeNode *cur = dummy, *pre = nullptr;
		while (cur)
		{
			if (!cur->left)
			{
				cur = cur->right;
			}
			else
			{
				pre = cur->left;
				while (pre->right&&pre->right != cur)
					pre = pre->right;
				if (!pre->right)
				{
					pre->right = cur;
					cur = cur->left;
				}
				else
				{
					pre->right = nullptr;
					travReverse(res, cur->left);
					cur = cur->right;
				}
			}
		}
		return res;
	}
	void travReverse(vector<int> &res, TreeNode *head)
	{
		TreeNode *end = reverseRight(head);
		TreeNode *node = end;
		while (node)
		{
			res.push_back(node->val);
			node = node->right;
		}
		reverseRight(end);
	}
	//参考链表的翻转
	TreeNode * reverseRight(TreeNode *head)
	{
		TreeNode *pre = nullptr, *cur = head;
		while (cur)
		{
			TreeNode *post = cur->right;
			cur->right = pre;
			pre = cur;
			cur = post;
		}
		return pre;
	}
};