#include "header.h"

/*

449. ���л��ͷ����л�����������

���л��ǽ����ݽṹ�����ת��Ϊһϵ��λ�Ĺ��̣��Ա������Դ洢���ļ����ڴ滺�����У�
��ͨ������������·���䣬�Ա��Ժ���ͬһ������һ��������������ؽ�

���һ���㷨�����л��ͷ����л� ����������
�����л�/�����л��㷨�Ĺ�����ʽû������
��ֻ��ȷ�������������������л�Ϊ�ַ��������ҿ��Խ����ַ��������л�Ϊ����Ķ���������

������ַ���Ӧ�����ܽ���

ʾ�� 1��
���룺root = [2,1,3]
�����[2,1,3]

ʾ�� 2��
���룺root = []
�����[]

��ʾ��
���нڵ�����Χ�� [0, 10^4]
0 <= Node.val <= 10^4
��Ŀ���� ��֤ ���������һ�ö���������


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

// ͨ�õĶ��������л�����
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

// ����BST�����ʣ����ô�սڵ�
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
