#include "header.h"

/*

给定一个单链表 L：L0→L1→…→Ln-1→Ln ，
将其重新排列后变为： L0→Ln→L1→Ln-1→L2→Ln-2→…
你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

给定链表 1->2->3->4, 重新排列为 1->4->2->3.

给定链表 1->2->3->4->5, 重新排列为 1->5->2->4->3.

*/

class Solution {
public:
	void reorderList(ListNode *head)
	{
		if (!head) return;
		//找到中间节点。
		ListNode *slow = head;
		ListNode *fast = head->next;
		while (fast&&fast->next)
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		//翻转后半部分节点，将链表一分为二。
		ListNode *premiddle = slow;
		ListNode *middle = reverse(premiddle->next);
		premiddle->next = nullptr;
		//将后半部分节点依次插入到前半部分链表合适的位置中。
		ListNode *p1 = head;
		ListNode *p2 = middle;
		while (p1&&p2)
		{
			ListNode *postp1 = p1->next;
			ListNode *postp2 = p2->next;
			p1->next = p2;
			p2->next = postp1;
			p1 = postp1;
			p2 = postp2;
		}
	}
	//翻转操作。
	ListNode * reverse(ListNode *head)
	{
		ListNode *pre = nullptr;
		ListNode *cur = head;
		while (cur)
		{
			ListNode *post = cur->next;
			cur->next = pre;
			pre = cur;
			cur = post;
		}
		return pre;
	}
};