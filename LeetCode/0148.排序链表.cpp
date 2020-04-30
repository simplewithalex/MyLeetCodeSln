#include "header.h"

/*

在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序。

示例：
输入: 4->2->1->3
输出: 1->2->3->4

*/


//这个题目要求O(1)空间复杂度，所以这里使用的传统归并不能满足要求，需要自底向上归并排序，具体见leetcode
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
