#include "header.h"

/*

给定一个二叉树，找出其最小深度。
最小深度是从根节点到最近叶子节点的最短路径上的节点数量。

*/

struct TreeNode 
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//层次遍历，效率高一些，遇到第一个叶子节点退出即可
class Solution1 {
public:
	int run(TreeNode* root)
	{
		if (!root) return 0;
		queue<TreeNode *> que;
		que.push(root);
		int count = 0;
		int len = 1;
		while (!que.empty())
		{
			count += 1;
			for (int i = 0; i < len; ++i)
			{
				TreeNode *temp = que.front();
				que.pop();
				if (temp->left)
					que.push(temp->left);
				if (temp->right)
					que.push(temp->right);
				if (!temp->left&&!temp->right)
					return count;
			}
			len = que.size();
		}
		return -1;
	}
};

//递归的方法，后序遍历
class Solution2 {
public:
	int run(TreeNode *root)
	{
		if (!root) return 0;
		int l = 0, r = 0;
		l = run(root->left);
		r = run(root->right);
		return (l == 0 || r == 0) ? l + r + 1 : min(l, r) + 1;
	}
};