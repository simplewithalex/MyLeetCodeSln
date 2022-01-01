#include "header.h"

/*

给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

示例 1:
输入: [1,2,3,null,5,null,4]
输出: [1,3,4]

示例 2:
输入: [1,null,3]
输出: [1,3]

示例 3:
输入: []
输出: []
  
提示:
二叉树的节点个数的范围是 [0,100]
-100 <= Node.val <= 100 

*/

// DFS
class Solution1 {
public:
	vector<int> rightSideView(TreeNode *root) {
		if (!root) return{};
		vector<int> res;
		helper(root, 0, res);
		return res;
	}
	void helper(TreeNode *node, int depth, vector<int> &res) {
		if (!node) return;
		if (depth == res.size()) res.push_back(node->val);
		helper(node->right, depth + 1, res);
		helper(node->left, depth + 1, res);
	}
};

// 层次遍历
class Solution2 {
public:
	vector<int> rightSideView(TreeNode *root) {
		if (!root) return{};
		vector<int> res;
		queue<TreeNode *> q;
		q.push(root);
		while (!q.empty()) {
			int len = q.size();
			for (int i = 0; i < len; ++i) {
				TreeNode *node = q.front();
				q.pop();
				if (node->left) q.push(node->left);
				if (node->right) q.push(node->right);
				if (i == len - 1) res.push_back(node->val);
			}
		}
		return res;
	}
};