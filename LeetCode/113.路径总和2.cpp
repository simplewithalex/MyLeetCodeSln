﻿#include "header.h"

/*

给定一个二叉树和一个目标和，找到所有从根节点到叶子节点路径总和等于给定目标和的路径。
说明: 叶子节点是指没有子节点的节点。

示例:
给定如下二叉树，以及目标和 sum = 22，

		5
       / \
      4   8
     /   / \
    11  13  4
   /  \    / \
  7    2  5   1


返回:
[
	[5,4,11,2],
	[5,8,4,5]
]

*/

class Solution {
public:
	vector<vector<int>> pathSum(TreeNode *root, int sum)
	{
		if (!root) return {};
		vector<vector<int>> res;
		vector<int> vec;
		pretrav(root, vec, res, sum);
		return res;
	}
	void pretrav(TreeNode *node, vector<int> &vec, vector<vector<int>> &res, int sum)
	{
		if (!node) return;
		vec.push_back(node->val);
		if (!node->left&&!node->right&&node->val == sum)
			res.push_back(vec);
		pretrav(node->left, vec, res, sum - node->val);
		pretrav(node->right, vec, res, sum - node->val);
		vec.pop_back();
	}
};