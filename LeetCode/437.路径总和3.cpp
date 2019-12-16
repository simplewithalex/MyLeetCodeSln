#include "header.h"

/*

����һ��������������ÿ����㶼�����һ������ֵ��
�ҳ�·���͵��ڸ�����ֵ��·��������
·������Ҫ�Ӹ��ڵ㿪ʼ��Ҳ����Ҫ��Ҷ�ӽڵ����������·��������������µģ�ֻ�ܴӸ��ڵ㵽�ӽڵ㣩��
������������1000���ڵ㣬�ҽڵ���ֵ��Χ�� [-1000000,1000000] ��������

ʾ����

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

		10
	   /  \
	  5   -3
     / \    \
    3   2	 11
   / \   \
  3  -2   1

����3���͵��� 8 ��·����:
1.  5 -> 3
2.  5 -> 2 -> 1
3.  -3 -> 11

*/

class Solution {
public:
	int pathSum(TreeNode *root, int sum)
	{
		if (!root) return 0;
		return travPre(root, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
	}
	int travPre(TreeNode *node, int sum)
	{
		if (!node) return 0;
		int res = 0;
		if (node->val == sum) res += 1;
		res += travPre(node->left, sum - node->val);
		res += travPre(node->right, sum - node->val);
		return res;
	}
};
//https://leetcode-cn.com/problems/path-sum-iii/solution/leetcode-437-path-sum-iii-by-li-xin-lei/