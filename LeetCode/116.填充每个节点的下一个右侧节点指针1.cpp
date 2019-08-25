#include "header.h"

/*

给定一个完美二叉树，其所有叶子节点都在同一层，
每个父节点都有两个子节点。二叉树定义如下：

struct TreeLinkNode 
{
	int val;
	TreeLinkNode *left, *right, *next;
	TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

填充它的每个 next 指针，让这个指针指向其下一个右侧节点。
如果找不到下一个右侧节点，则将 next 指针设置为 NULL。
初始状态下，所有 next 指针都被设置为 NULL。

提示：
你只能使用常量级额外空间。
使用递归解题也符合要求，本题中递归程序占用的栈空间不算做额外的空间复杂度。

*/


struct TreeLinkNode
{
	int val;
	TreeLinkNode *left, *right, *next;
	TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};


class Solution {
public:
	void connect(TreeLinkNode *root)
	{
		if (!root) return;
		TreeLinkNode *pre = root;
		TreeLinkNode *cur = nullptr;
		while (pre->left)
		{
			cur = pre;
			while (cur)
			{
				cur->left->next = cur->right;
				if (cur->next) cur->right->next = cur->next->left;
				cur = cur->next;
			}
			pre = pre->left;
		}
	}
};
