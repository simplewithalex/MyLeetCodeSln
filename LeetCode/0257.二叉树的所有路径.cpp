#include "header.h"

/*

给你一个二叉树的根节点root，按任意顺序，返回所有从根节点到叶子节点的路径。叶子节点是指没有子节点的节点。

示例 1：
输入：root = [1,2,3,null,5]
输出：["1->2->5","1->3"]

示例 2：
输入：root = [1]
输出：["1"]

提示：
树中节点的数目在范围 [1, 100] 内
-100 <= Node.val <= 100

*/

// DFS
class Solution1 {
public:
	vector<string> binaryTreePaths(TreeNode *root) {
		vector<string> paths;
		helper(root, "", paths);
		return paths;
	}
private:
	void helper(TreeNode *node, string path, vector<string> &paths) {
		if (node == nullptr) return;
		path += to_string(node->val);
		if (node->left == nullptr&&node->right == nullptr) {
			paths.push_back(path);
		} else {
			path += "->";
			helper(node->left, path, paths);
			helper(node->right, path, paths);
		}
	}
};

// BFS
class Solution2 {
public:
	vector<string> binaryTreePaths(TreeNode *root) {
		if (root == nullptr) return{};
		vector<string> paths;
		queue<TreeNode *> node_queue;
		queue<string> path_queue;
		node_queue.push(root);
		path_queue.push(to_string(root->val));
		while (!node_queue.empty()) {
			TreeNode *node = node_queue.front();
			string path = path_queue.front();
			node_queue.pop();
			path_queue.pop();
			if (node->left == nullptr&&node->right == nullptr) {
				paths.push_back(path);
			} else {
				if (node->left) {
					node_queue.push(node->left);
					path_queue.push(path + "->" + to_string(node->left->val));
				}
				if (node->right) {
					node_queue.push(node->right);
					path_queue.push(path + "->" + to_string(node->right->val));
				}
			}
		}
		return paths;
	}
};
