#include "header.h"

/*

给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。
你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

示例:
给定 1->2->3->4, 你应该返回 2->1->4->3.

*/

//迭代的方法
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

//递归的方法
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