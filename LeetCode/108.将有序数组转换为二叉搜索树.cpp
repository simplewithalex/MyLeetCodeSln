#include "header.h"

/*

将一个按照升序排列的有序数组，转换为一棵高度平衡二叉搜索树。
本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。

示例:
给定有序数组: [-10,-3,0,5,9],
一个可能的答案是：[0,-3,9,-10,null,5]，它可以表示下面这个高度平衡二叉搜索树：

	 0
	/ \
  -3   9
   /   /
  -10  5

*/

class Solution {
public:
	TreeNode * sortedArrayToBST(vector<int> &num)
	{
		if (num.empty()) return nullptr;
		int len = num.size();
		return findMiddle(num, 0, len);
	}
	TreeNode * findMiddle(vector<int> &num, int start, int end)
	{
		if (start == end) return nullptr;
		int mi = (start + end) >> 1;
		TreeNode *node = new TreeNode(num[mi]);
		node->left = findMiddle(num, start, mi);
		node->right = findMiddle(num, mi + 1, end);
		return node;
	}
};