#include "header.h"

/*

����һ�����������ҳ�����С��ȡ�
��С����ǴӸ��ڵ㵽���Ҷ�ӽڵ�����·���ϵĽڵ�������

*/



//��α�����Ч�ʸ�һЩ��������һ��Ҷ�ӽڵ��˳�����
class Solution1 {
public:
	int run(TreeNode* root)
	{
		if (!root) return 0;
		queue<TreeNode *> que;
		que.push(root);
		int count = 0;
		int len = 1;
		while (!que.empty())
		{
			count += 1;
			for (int i = 0; i < len; ++i)
			{
				TreeNode *temp = que.front();
				que.pop();
				if (temp->left)
					que.push(temp->left);
				if (temp->right)
					que.push(temp->right);
				if (!temp->left&&!temp->right)
					return count;
			}
			len = que.size();
		}
		return -1;
	}
};

//�ݹ�ķ������������
class Solution2 {
public:
	int run(TreeNode *root)
	{
		if (!root) return 0;
		int l = 0, r = 0;
		l = run(root->left);
		r = run(root->right);
		return (l == 0 || r == 0) ? l + r + 1 : min(l, r) + 1;
	}
};