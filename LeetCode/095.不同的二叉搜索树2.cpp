#include "header.h"

/*

给定一个整数 n，生成所有由 1 ... n 为节点所组成的二叉搜索树。

示例:
输入: 3
输出:
[
  [1,null,3,2],
  [3,2,null,1],
  [3,1,null,null,2],
  [2,1,3],
  [1,null,2,null,3]
]

*/

class Solution {
public:
	vector<TreeNode *> generateTrees(int n)
	{
		return generate(1, n);
	}
	vector<TreeNode *> generate(int start, int end)
	{
		vector<TreeNode *> vec;
		if (start > end)
		{
			vec.push_back(nullptr);
			return vec;
		}
		for (int i = start; i <= end; ++i)
		{
			vector<TreeNode *> left = generate(start, i - 1);
			vector<TreeNode *> right = generate(i + 1, end);
			for (auto lNode : left)
				for (auto rNode : right)
				{
					TreeNode *root = new TreeNode(i);
					root->left = lNode;
					root->right = rNode;
					vec.push_back(root);
				}
		}
		return vec;
	}
};