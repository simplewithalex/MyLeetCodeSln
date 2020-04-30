#include "header.h"

/*

����һ�����������ж����Ƿ��Ǹ߶�ƽ��Ķ�������
�����У�һ�ø߶�ƽ�����������Ϊ��
һ��������ÿ���ڵ� ���������������ĸ߶Ȳ�ľ���ֵ������1��

*/

class Solution {
public:
	bool isBalanced(TreeNode *root)
	{
		return travpost(root) != -1;
	}
	int travpost(TreeNode *Node)
	{
		if (!Node) return 0;
		int lheight = 0, rheight = 0;
		lheight = travpost(Node->left);
		if (lheight == -1) return -1;
		rheight = travpost(Node->right);
		if (rheight == -1) return -1;
		if (abs(lheight - rheight)>1)
			return -1;
		return 1 + max(lheight, rheight);
	}
};