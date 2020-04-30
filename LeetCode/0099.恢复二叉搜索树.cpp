#include "header.h"

/*

二叉搜索树中的两个节点被错误地交换。

请在不改变其结构的情况下，恢复这棵树。

示例 1:
输入: [1,3,null,null,2]
    1
   /
  3
   \
	2
输出: [3,1,null,null,2]
	3
   /
  1
   \
	2

示例 2:
输入: [3,1,4,null,null,2]
	 3
	/ \
   1   4
	  /
	 2
输出: [2,1,4,null,null,3]

	2
   / \
  1   4
     /
    3
进阶:
使用 O(n) 空间复杂度的解法很容易实现。
你能想出一个只使用常数空间的解决方案吗？

*/

//使用莫里斯中序遍历
class Solution {
public:
	void recoverTree(TreeNode *root)
	{
		TreeNode *cur = root, *pre = nullptr;
		TreeNode *first = nullptr, *second = nullptr, *prev = nullptr;
		while (cur)
		{
			if (!cur->left)
			{
				if (prev&&prev->val > cur->val)
				{
					if (!first) first = prev;
					second = cur;
				}
				prev = cur, cur = cur->right;
			}
			else
			{
				pre = cur->left;
				while (pre->right&&pre->right != cur)
					pre = pre->right;
				if (!pre->right)
				{
					pre->right = cur;
					cur = cur->left;
				}
				else
				{
					pre->right = nullptr;
					if (prev&&prev->val > cur->val)
					{
						if (!first) first = prev;
						second = cur;
					}
					prev = cur, cur = cur->right;
				}
			}
		}
		if (first&&second)
		{
			swap(first->val, second->val);
		}
	}
};
//非递归，不用栈，O(1)空间，需要用到Morris中序遍历。
//参考https://www.cnblogs.com/AnnieKim/archive/2013/06/15/MorrisTraversal.html