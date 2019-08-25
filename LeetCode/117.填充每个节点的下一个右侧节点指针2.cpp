#include "header.h"

/*

给定一个二叉树
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


//该方法是一种通用的方法，同样可以解决116题。
class Solution {
public:
	void connect(TreeLinkNode *root)
	{
		TreeLinkNode *pre = nullptr;
		TreeLinkNode *head = nullptr;
		TreeLinkNode *cur = root;
		while (cur)
		{
			while (cur)
			{
				if (cur->left)
				{
					if (pre)
					{
						pre->next = cur->left;
						pre = pre->next;
					}
					else
					{
						head = cur->left;
						pre = head;
					}
				}
				if (cur->right)
				{
					if (pre)
					{
						pre->next = cur->right;
						pre = pre->next;
					}
					else
					{
						head = cur->right;
						pre = head;
					}
				}
				cur = cur->next;
			}
			cur = head;
			head = nullptr;
			pre = nullptr;
		}
	}
};