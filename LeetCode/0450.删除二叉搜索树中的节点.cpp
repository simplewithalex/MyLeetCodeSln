#include "header.h"

/*

450. ɾ�������������еĽڵ�

����һ�������������ĸ��ڵ� root ��һ��ֵ key��ɾ�������������е� key ��Ӧ�Ľڵ㣬����֤���������������ʲ���
���ض������������п��ܱ����£��ĸ��ڵ������

һ����˵��ɾ���ڵ�ɷ�Ϊ�������裺
�����ҵ���Ҫɾ���Ľڵ㣻
����ҵ��ˣ�ɾ����

ʾ�� 1:
���룺root = [5,3,6,2,4,null,7], key = 3
�����[5,4,6,2,null,null,7]
���ͣ�������Ҫɾ���Ľڵ�ֵ�� 3���������������ҵ� 3 ����ڵ㣬Ȼ��ɾ����
һ����ȷ�Ĵ��� [5,4,6,2,null,null,7], ����ͼ��ʾ
��һ����ȷ���� [5,2,6,null,4,null,7]

ʾ�� 2:
����: root = [5,3,6,2,4,null,7], key = 0
���: [5,3,6,2,4,null,7]
����: ������������ֵΪ 0 �Ľڵ�

ʾ�� 3:
����: root = [], key = 0
���: []

��ʾ:
�ڵ����ķ�Χ [0, 10^4]
-10^5 <= Node.val <= 10^5
�ڵ�ֵΨһ
root �ǺϷ��Ķ���������
-10^5 <= key <= 10^5

*/

class Solution1 {
public:
	TreeNode *deleteNode(TreeNode *root, int key) {
		if (!root) return root;
		if (root->val < key) {
			root->right = deleteNode(root->right, key);
		}
		else if (root->val > key) {
			root->left = deleteNode(root->left, key);
		}
		else {
			if (!root->left) return root->right;
			if (!root->right) return root->left;
			TreeNode *node = root->left;
			while (node->right) node = node->right;
			root->val = node->val;
			root->left = deleteNode(root->left, root->val);
		}
		return root;
	}
};

// ����
class Solution2 {
public:
	TreeNode *deleteNode(TreeNode *root, int key) {
		TreeNode **node = &root;
		while (*node && (*node)->val != key)
			node = (*node)->val < key ? &(*node)->right : &(*node)->left;
		if (!*node) return root;
		TreeNode **s = &(*node)->right;
		while (*s) s = &(*s)->left;
		*s = (*node)->left;
		*node = (*node)->right;
		return root;
	}
};


