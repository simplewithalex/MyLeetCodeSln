#include "header.h"

/*

����һ�������һ���ض�ֵ x����������зָ���ʹ������С�� x �Ľڵ㶼�ڴ��ڻ���� x �Ľڵ�֮ǰ��
��Ӧ����������������ÿ���ڵ�ĳ�ʼ���λ�á�

ʾ��:
����: head = 1->4->3->2->5->2, x = 3
���: 1->2->2->4->3->5

*/

class Solution {
public:
	ListNode* partition(ListNode *head, int x)
	{
		if (!head) return nullptr;
		ListNode *dummy1 = new ListNode(-1);
		ListNode *dummy2 = new ListNode(-1);
		ListNode *p1 = dummy1, *p2 = dummy2;
		ListNode *cur = head;
		while (cur)
		{
			if (cur->val < x)
				p1 = p1->next = cur;
			else
				p2 = p2->next = cur;
			cur = cur->next;
		}
		p2->next = nullptr;
		p1->next = dummy2->next;
		ListNode *pHead = dummy1->next;
		delete dummy1;
		delete dummy2;
		return pHead;
	}
};