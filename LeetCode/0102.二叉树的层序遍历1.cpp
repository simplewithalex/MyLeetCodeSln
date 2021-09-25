#include "header.h"

/*

����һ�������������㷵���䰴 ������� �õ��Ľڵ�ֵ���������أ������ҷ������нڵ㣩��

ʾ����

��������[3,9,20,null,null,15,7],

   3
  / \
 9  20
   /  \
  15   7

�����������������
[
 [3],
 [9,20],
 [15,7]
]

*/

class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode *root) {
		vector<vector<int>> res;
		if (!root) return res;
		queue<TreeNode *> q;
		q.push(root);
		while (!q.empty()) {
			int curLen = q.size();
			vector<int> v;
			for (int i = 0; i < curLen; ++i) {
				TreeNode *node = q.front();
				q.pop();
				v.push_back(node->val);
				if (node->left) q.push(node->left);
				if (node->right) q.push(node->right);
			}
			res.push_back(v);
		}
		return res;
	}
};