#include "header.h"

/*

反转一个单链表。

示例:

输入: 1->2->3->4->5->NULL
输出: 5->4->3->2->1->NULL

进阶:
你可以迭代或递归地反转链表。你能否用两种方法解决这道题？

*/

//迭代法
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

//递归法
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