#include "header.h"

/*

����һ��������, �ҵ�����������ָ���ڵ������������ȡ�

ʾ�� 1:

����: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
���: 3
����: �ڵ� 5 �ͽڵ� 1 ��������������ǽڵ� 3��
 
ʾ��?2:

����: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
���: 5
����: �ڵ� 5 �ͽڵ� 4 ��������������ǽڵ� 5����Ϊ���ݶ�������������Ƚڵ����Ϊ�ڵ㱾��

˵��:

���нڵ��ֵ����Ψһ�ġ�
p��q Ϊ��ͬ�ڵ��Ҿ������ڸ����Ķ������С�

*/

class Solution {
public:
	TreeNode * lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
	{
		if (!root || root == p || root == q) return root;
		TreeNode *left = lowestCommonAncestor(root->left, p, q);
		TreeNode *right = lowestCommonAncestor(root->right, p, q);
		if (left || right)
		{
			if (left && right)
				return root;
			else
				return left ? left : right;
		}
		else
		{
			return nullptr;
		}
	}
};