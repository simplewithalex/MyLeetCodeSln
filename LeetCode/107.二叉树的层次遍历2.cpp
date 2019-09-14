#include "header.h"

/*

给定一个二叉树，返回其节点值自底向上的层次遍历。 
（即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）

例如：

给定二叉树 [3,9,20,null,null,15,7],

	  3
	 / \
	9  20
   /  \
  15   7
返回其自底向上的层次遍历为：

[
	[15,7],
	[9,20],
	[3]
]

*/

//迭代法
class Solution1 {
public:
	vector<vector<int>> levelOrderBottom(TreeNode *root)
	{
		if (!root) return{};
		stack<vector<int>> s;
		vector<vector<int>> res;
		queue<TreeNode *> q;
		q.push(root);
		while (!q.empty())
		{
			int len = q.size();
			vector<int> vec;
			while (len--)
			{
				TreeNode *temp = q.front();
				q.pop();
				if (temp->left)
					q.push(temp->left);
				if (temp->right)
					q.push(temp->right);
				vec.push_back(temp->val);
			}
			s.push(vec);
		}
		while (!s.empty())
		{
			res.push_back(s.top());
			s.pop();
		}
		return res;
	}
};

//递归法
class Solution2 {
public:
	vector<vector<int>> levelOrderBottom(TreeNode *root)
	{
		if (!root) return{};
		vector<vector<int>> res;
		trav(root, 0, res);
		return res;
	}
	void trav(TreeNode *node, int level, vector<vector<int>> &res)
	{
		if (!node) return;
		int len = res.size();
		if (level == len)
		{
			res.insert(res.begin(), vector<int>());
		}
		trav(node->left, level + 1, res);
		trav(node->right, level + 1, res);
		len = res.size();
		res[len - level - 1].push_back(node->val);
	}

