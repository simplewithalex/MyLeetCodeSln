#include "header.h"

/*

����һ������������������ǰ�����,ͨ�������㷨���

*/

class Solution1 {
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

//ʹ��Ī��˹������
class Solution2 {
public:
	vector<int> preorderTraversal(TreeNode *root) 
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
					res.push_back(cur->val);
					cur = cur->left;
				}
				else
				{
					pre->right = nullptr;
					cur = cur->right;
				}
			}
		}
		return res;
	}
};