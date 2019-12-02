#include "header.h"

/*

��תһ��������

ʾ��:

����: 1->2->3->4->5->NULL
���: 5->4->3->2->1->NULL

����:
����Ե�����ݹ�ط�ת�������ܷ������ַ����������⣿

*/

//������
class Solution {
public:
	ListNode * reverseList(ListNode *head)
	{
		if (!head) return nullptr;
		ListNode *dummy = new ListNode(-1);
		dummy->next = head;
		reverse(dummy, nullptr);
		ListNode *newHead = dummy->next;
		delete dummy;
		return newHead;
	}
	void reverse(ListNode *head, ListNode *behind)
	{
		ListNode *start = head->next;
		ListNode *then = start->next;
		ListNode *pre = head;
		while (then != behind)
		{
			start->next = then->next;
			then->next = pre->next;
			pre->next = then;
			then = start->next;
		}
	}
};

//�ݹ鷨
class Solution {
public:
	ListNode * reverseList(ListNode *head) 
	{
		if (!head || !head->next) return head;
		ListNode *preNode = reverseList(head->next);
		head->next->next = head;
		head->next = nullptr;
		return preNode;
	}
};