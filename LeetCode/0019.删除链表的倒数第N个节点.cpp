#include "header.h"

/*

给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。

示例：
给定一个链表: 1->2->3->4->5, 和 n = 2.
当删除了倒数第二个节点后，链表变为 1->2->3->5.

说明：
给定的 n 保证是有效的。

进阶：
你能尝试使用一趟扫描实现吗？

*/

class Solution {
public:
	ListNode *removeNthFromEnd(ListNode *head, int n)
	{
		if (!head) return nullptr;
		if (n <= 0) return head;
		ListNode *dummy = new ListNode(-1);
		dummy->next = head;
		ListNode *front = dummy, *behind = dummy;
		int gap = n + 1;
		while (gap--)
		{
			front = front->next;
		}
		while (front)
		{
			front = front->next;
			behind = behind->next;
		}
		ListNode *temp = behind->next;
		behind->next = temp->next;
		delete temp;

		temp = dummy;
		head = dummy->next;
		delete temp;
		return head;
	}
};