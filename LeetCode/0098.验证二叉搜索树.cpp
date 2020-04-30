#include "header.h"

/*

����һ�����������ж����Ƿ���һ����Ч�Ķ�����������

����һ��������������������������
�ڵ��������ֻ����С�ڵ�ǰ�ڵ������
�ڵ��������ֻ�������ڵ�ǰ�ڵ������
�������������������������Ҳ�Ƕ�����������

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