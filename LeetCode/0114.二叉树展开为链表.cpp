#include "header.h"

/*

给你二叉树的根结点 root ，请你将它展开为一个单链表
展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null
展开后的单链表应该与二叉树 先序遍历 顺序相同。
 
示例 1：
输入：root = [1,2,5,3,4,null,6]
输出：[1,null,2,null,3,null,4,null,5,null,6]

示例 2：
输入：root = []
输出：[]

示例 3：
输入：root = [0]
输出：[0]

提示：
树中结点数在范围 [0, 2000] 内
-100 <= Node.val <= 100

进阶：你可以使用原地算法（O(1) 额外空间）展开这棵树吗？

*/

class Solution1 {
public:
	void flatten(TreeNode* root) {
		TreeNode *node = root;
		while (node != nullptr) {
			if (node->left) {
				TreeNode *pre = node->left;
				while (pre->right != nullptr) {
					pre = pre->right;
				}
				pre->right = node->right;
				node->right = node->left;
				node->left = nullptr;
				node = node->right;
			}
			else {
				node = node->right;
			}
		}
	}
};

// 如果原地算法是指不是创建新的树，而是在原树上修改，则也可以使用递归
class Solution2 {
public:
	void flatten(TreeNode* root) {
		TreeNode *lastNode = nullptr;
		travPost(root, lastNode);
	}

	void travPost(TreeNode *node, TreeNode *&lastNode) {
		if (!node) return;
		travPost(node->right, lastNode);
		travPost(node->left, lastNode);
		node->right = lastNode;
		node->left = nullptr;
		lastNode = node;
	}
};