#include "header.h"

/*

�� O(n log n) ʱ�临�ӶȺͳ������ռ临�Ӷ��£��������������

ʾ����
����: 4->2->1->3
���: 1->2->3->4

*/


//�����ĿҪ��O(1)�ռ临�Ӷȣ���������ʹ�õĴ�ͳ�鲢��������Ҫ����Ҫ�Ե����Ϲ鲢���򣬾����leetcode
class Solution {
public:
	ListNode * sortList(ListNode *head)
	{
		if (!head || !head->next)
			return head;
		ListNode *pre = nullptr, *slow = head, *fast = head;
		while (fast&&fast->next)
		{
			pre = slow;
			slow = slow->next;
			fast = fast->next->next;
		}
		pre->next = nullptr;
		ListNode *l = nullptr, *r = nullptr;
		l = sortList(head);
		r = sortList(slow);
		return merge(l, r);
	}
	ListNode * merge(ListNode *l, ListNode *r)
	{
		ListNode *preNode = new ListNode(-1);
		ListNode *temp = preNode;
		while (l&&r)
		{
			if (l->val <= r->val)
			{
				temp->next = l;
				temp = temp->next;
				l = l->next;
			}
			else
			{
				temp->next = r;
				temp = temp->next;
				r = r->next;
			}
		}
		if (l)
			temp->next = l;
		if (r)
			temp->next = r;
		temp = preNode->next;
		delete preNode;
		return temp;
	}
};
