#include "header.h"

/*

给定一个排序链表，删除所有含有重复数字的节点，只保留原始链表中没有重复出现的数字。

示例 1:

输入: 1->2->3->3->4->4->5
输出: 1->2->5

示例 2:

输入: 1->1->1->2->3
输出: 2->3

*/

class Solution {
public:
	ListNode * deleteDuplicates(ListNode *head)
	{
		if (!head) return nullptr;
		ListNode *dummy = new ListNode(-1);
		dummy->next = head;
		ListNode *pre = dummy;
		ListNode *cur = head;
		while (cur)
		{
			while (cur->next&&cur->next->val == cur->val)
			{
				ListNode *temp = cur;
				cur = cur->next;
				delete temp;
			}
			if (pre->next == cur)
			{
				pre = cur;
			}
			else
			{
				pre->next = cur->next;
				delete cur;
			}
			cur = pre->next;
		}
		ListNode *pHead = dummy->next;
		delete dummy;
		return pHead;
	}
};