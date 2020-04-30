#include "header.h"

/*

����һ���������������������ڵĽڵ㣬�����ؽ����������
�㲻��ֻ�ǵ����ĸı�ڵ��ڲ���ֵ��������Ҫʵ�ʵĽ��нڵ㽻����

ʾ��:
���� 1->2->3->4, ��Ӧ�÷��� 2->1->4->3.

*/

//�����ķ���
class Solution1 {
public:
	ListNode *swapPairs(ListNode *head)
	{
		ListNode *dummy = new ListNode(-1);
		dummy->next = head;
		ListNode *pre = dummy;
		while (pre->next && pre->next->next)
		{
			ListNode *start = pre->next;
			ListNode *end = start->next;
			pre->next = end;
			start->next = end->next;
			end->next = start;
			pre = start;
		}
		head = dummy->next;
		delete dummy;
		return head;
	}
};

//�ݹ�ķ���
class Solution {
public:
	ListNode *swapPairs(ListNode *head)
	{
		if (!head || !head->next) return head;
		ListNode *node = head->next;
		head->next = swapPairs(head->next->next);
		node->next = head;
		return node;
	}
};