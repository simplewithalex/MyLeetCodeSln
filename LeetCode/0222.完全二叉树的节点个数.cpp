#include "header.h"

/*

给你一棵 完全二叉树 的根节点 root ，求出该树的节点个数。

完全二叉树的定义如下：

在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。
若最底层为第 h 层，则该层包含 1 ~ 2^h 个节点。

示例 1：
输入：root = [1,2,3,4,5,6]
输出：6

示例 2：
输入：root = []
输出：0

示例 3：
输入：root = [1]
输出：1
  
提示：
树中节点的数目范围是[0, 5 * 10^4]
0 <= Node.val <= 5 * 10^4
题目数据保证输入的树是 完全二叉树
   
进阶：遍历树来统计节点是一种时间复杂度为 O(n) 的简单解决方案。你可以设计一个更快的算法吗？

*/

// 进阶方法：完全二叉树性质 + 二分查找
class Solution {
public:
	int countNodes(TreeNode *root) {
		if (!root) return 0;
		int level = 0;
		TreeNode *node = root;
		while (node->left) {
			++level;
			node = node->left;
		}
		int lo = 1 << level, hi = (1 << (level + 1)) - 1;
		while (lo < hi) {
			int mi = lo + (hi - lo + 1) / 2;
			if (exists(root, level, mi)) lo = mi;
			else hi = mi - 1;
		}
		return lo;
	}

private:
	bool exists(TreeNode *root, int level, int k) {
		int bits = 1 << (level - 1);
		TreeNode *node = root;
		while (node && bits > 0) {
			if (bits & k) node = node->right;
			else node = node->left;
			bits >>= 1;
		}
		return node != nullptr;
	}
};
// LeetCode官方题解：
// https://leetcode-cn.com/problems/count-complete-tree-nodes/solution/wan-quan-er-cha-shu-de-jie-dian-ge-shu-by-leetco-2/ 