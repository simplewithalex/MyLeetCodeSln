#include "header.h"

/*

给定一个非空二叉树，返回其最大路径和。
本题中，路径被定义为一条从树中任意节点出发，
达到任意节点的序列。该路径至少包含一个节点，且不一定经过根节点。

示例 1:
输入: [1,2,3]

  1
 / \
2   3

输出: 6

示例 2:
输入: [-10,9,20,null,null,15,7]

   -10
   / \
   9  20
     /  \
	15   7

输出: 42

*/

class Solution {
public:
	int maxPathSum(TreeNode *root)
	{
		if (!root) return 0;
		int maxNum = INT_MIN;
		travPost(root, maxNum);
		return maxNum;
	}
	int travPost(TreeNode *node, int &maxNum)
	{
		if (!node) return 0;
		int l = 0, r = 0;
		l = max(0, travPost(node->left, maxNum));
		r = max(0, travPost(node->right, maxNum));
		maxNum = max(maxNum, l + r + node->val);
		return max(l, r) + node->val;
	}
};