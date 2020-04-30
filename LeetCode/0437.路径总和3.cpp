#include "header.h"

/*

给定一个二叉树，它的每个结点都存放着一个整数值。
找出路径和等于给定数值的路径总数。
路径不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。
二叉树不超过1000个节点，且节点数值范围是 [-1000000,1000000] 的整数。

示例：

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

		10
	   /  \
	  5   -3
     / \    \
    3   2	 11
   / \   \
  3  -2   1

返回3。和等于 8 的路径有:
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