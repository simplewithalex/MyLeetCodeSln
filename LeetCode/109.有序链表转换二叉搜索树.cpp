#include "header.h"
/*

给定一个单链表，其中的元素按升序排序，将其转换为高度平衡的二叉搜索树。
本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。

示例:

给定的有序链表： [-10, -3, 0, 5, 9],
一个可能的答案是：[0, -3, 9, -10, null, 5], 它可以表示下面这个高度平衡二叉搜索树：

	0
   / \
 -3   9
 /   /
-10  5

*/

class Solution {
public:
	TreeNode * sortedListToBST(ListNode *head)
	{
		return findMiddle(head, nullptr);
	}
	TreeNode * findMiddle(ListNode *hNode, ListNode *tNode)
	{
		if (hNode == tNode) return nullptr;
		ListNode *slow = hNode;
		ListNode *fast = hNode;
		while (fast != tNode&&fast->next != tNode)
		{
			slow = slow->next;
			fast = fast->next->next;
		}
		TreeNode *root = new TreeNode(slow->val);
		root->left = findMiddle(hNode, slow);
		root->right = findMiddle(slow->next, tNode);
		return root;
	}
};