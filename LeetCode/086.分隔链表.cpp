#include "header.h"

/*

给定一个链表和一个特定值 x，对链表进行分隔，使得所有小于 x 的节点都在大于或等于 x 的节点之前。
你应当保留两个分区中每个节点的初始相对位置。

示例:
输入: head = 1->4->3->2->5->2, x = 3
输出: 1->2->2->4->3->5

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