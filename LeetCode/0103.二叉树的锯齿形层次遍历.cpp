#include "header.h"

/*

给定一个二叉树，返回其节点值的锯齿形层次遍历。
（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。

例如：

给定二叉树 [3,9,20,null,null,15,7],

	3
   / \
  9  20
    /  \
   15   7
返回锯齿形层次遍历如下：

[
   [3],
   [20,9],
   [15,7]
]

*/

class Solution {
public:
	vector<vector<int>> zigzagLevelOrder(TreeNode* root)
	{
		if (!root) return {};
		vector<vector<int>> res;
		queue<TreeNode *> q;
		q.push(root);
		bool leftToright = true;
		while (!q.empty())
		{
			int len = q.size();
			vector<int> vec(len);
			for (int i = 0; i < len; ++i)
			{
				TreeNode *temp = q.front();
				q.pop();
				int index = leftToright ? i : len - i - 1;
				vec[index] = temp->val;
				if (temp->left)
					q.push(temp->left);
				if (temp->right)
					q.push(temp->right);
			}
			leftToright = !leftToright;
			res.push_back(vec);
		}
		return res;
	}
};