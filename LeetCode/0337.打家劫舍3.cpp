#include "header.h"

/*

在上次打劫完一条街道之后和一圈房屋后，小偷又发现了一个新的可行窃的地区。

这个地区只有一个入口，我们称之为“根”。 除了“根”之外，每栋房子有且只有一个“父“房子与之相连。

一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。 如果两个直接相连的房子在同一天晚上被打劫，房屋将自动报警。

计算在不触动警报的情况下，小偷一晚能够盗取的最高金额。

示例 1:
输入: [3,2,3,null,3,null,1]

    3
   / \
  2   3
  \    \
   3    1

输出: 7
解释: 小偷一晚能够盗取的最高金额 = 3 + 3 + 1 = 7.

示例 2:
输入: [3,4,5,1,3,null,1]

      3
	 / \
	4   5
   / \   \
  1   3   1

输出: 9
解释: 小偷一晚能够盗取的最高金额 = 4 + 5 = 9.

*/

//备忘录算法
class Solution1 {
public:
	int rob(TreeNode *root)
	{
		unordered_map<TreeNode *, int> memo;
		return travPre(root, memo);
	}
	int travPre(TreeNode *node, unordered_map<TreeNode *, int> &memo)
	{
		if (!node) return 0;
		if (memo.count(node)) return memo[node];
		int val = 0;
		if (node->left) val += travPre(node->left->left, memo) + travPre(node->left->right, memo);
		if (node->right) val += travPre(node->right->left, memo) + travPre(node->right->right, memo);
		val = max(val + node->val, travPre(node->left, memo) + travPre(node->right, memo));
		memo[node] = val;
		return memo[node];
	}
};

//dp算法
class Solution2 {
public:
	int rob(TreeNode *root)
	{
		vector<int> res = helper(root);
		return max(res[0], res[1]);
	}
	vector<int> helper(TreeNode *node)
	{
		vector<int> res(2, 0);
		if (!node) return res;
		vector<int> left = helper(node->left);
		vector<int> right = helper(node->right);
		//第一个元素表示当前节点未被抢劫
		res[0] = max(left[0], left[1]) + max(right[0], right[1]);
		//第二个元素表示当前节点被抢
		res[1] = node->val + left[0] + right[0];
		return res;
	}
};
//https://leetcode.com/problems/house-robber-iii/discuss/79330/Step-by-step-tackling-of-the-problem