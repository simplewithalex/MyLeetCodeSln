#include "header.h"

/*

449. 序列化和反序列化二叉搜索树

序列化是将数据结构或对象转换为一系列位的过程，以便它可以存储在文件或内存缓冲区中，
或通过网络连接链路传输，以便稍后在同一个或另一个计算机环境中重建

设计一个算法来序列化和反序列化 二叉搜索树
对序列化/反序列化算法的工作方式没有限制
您只需确保二叉搜索树可以序列化为字符串，并且可以将该字符串反序列化为最初的二叉搜索树

编码的字符串应尽可能紧凑

示例 1：
输入：root = [2,1,3]
输出：[2,1,3]

示例 2：
输入：root = []
输出：[]

提示：
树中节点数范围是 [0, 10^4]
0 <= Node.val <= 10^4
题目数据 保证 输入的树是一棵二叉搜索树


*/


/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/

// 通用的二叉树序列化方法
class Codec1 {
public:
	// Encodes a tree to a single string.
	string serialize(TreeNode *root) {
		string out;
		serial(root, out);
		return out;
	}

	// Decodes your encoded data to tree.
	TreeNode *deserialize(string data) {
		size_t pos = 0;
		return deserial(data, pos);
	}

	void serial(TreeNode *node, string &out) {
		if (!node) {
			out += "#,";
			return;
		}
		out += to_string(node->val) + ",";
		serial(node->left, out);
		serial(node->right, out);
	}

	TreeNode *deserial(string &in, size_t &pos) {
		pos = in.find(",", pos);
		if (in[pos - 1] == '#') return nullptr;
		int val = 0, mul = 1;
		for (int i = pos - 1; in[i] != ',' && i >= 0; --i) {
			val += (in[i] - '0') * mul;
			mul *= 10;
		}
		TreeNode *node = new TreeNode(val);
		node->left = deserial(in, ++pos);
		node->right = deserial(in, ++pos);
		return node;
	}
};

// 利用BST的性质，不用存空节点
class Codec2 {
public:
	// Encodes a tree to a single string.
	string serialize(TreeNode *root) {
		ostringstream out;
		serial(root, out);
		return out.str();
	}

	// Decodes your encoded data to tree.
	TreeNode *deserialize(string data) {
		istringstream in(data);
		int val = -1;
		return deserial(in, val, INT_MIN, INT_MAX);
	}

	void serial(TreeNode *node, ostringstream &out) {
		if (!node) return;
		out << node->val << ",";
		serial(node->left, out);
		serial(node->right, out);
	}

	TreeNode *deserial(istringstream &in, int &val, int lower, int upper) {
		string val_str;
		if (val == -1) {
			if (!getline(in, val_str, ',')) return nullptr;
			val = stoi(val_str);
		}
		if (val < lower || val > upper) return nullptr;
		TreeNode *node = new TreeNode(val);
		int new_lower = val, new_upper = val;
		val = -1;
		node->left = deserial(in, val, lower, new_upper);
		node->right = deserial(in, val, new_lower, upper);
		return node;
	}
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;
