#include "header.h"

/*

������������������дһ�����������������Ƿ���ͬ��
����������ڽṹ����ͬ�����ҽڵ������ͬ��ֵ������Ϊ��������ͬ�ġ�

*/
class Solution {
public:
	bool isSameTree(TreeNode *p, TreeNode *q)
	{
		if (!p || !q) return p == q;
		if (p->val == q->val)
			return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
		return false;
	}
};