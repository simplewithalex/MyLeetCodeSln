#include "header.h"

/*

反转从位置 m 到 n 的链表。请使用一趟扫描完成反转。

说明:
1 ≤ m ≤ n ≤ 链表长度。

示例:

输入: 1->2->3->4->5->NULL, m = 2, n = 4
输出: 1->4->3->2->5->NULL

*/

// 头插法
class Solution1 {
public:
	ListNode * reverseBetween(ListNode *head, int m, int n)
	{
		if (!head) return nullptr;
		ListNode *preHead = new ListNode(-1);
		preHead->next = head;
		ListNode *pre = preHead;
		for (int i = 0; i < m - 1; ++i)
			pre = pre->next;
		ListNode *start = pre->next;
		ListNode *then = start->next;
		for (int i = 0; i < n - m; ++i)
		{
			start->next = then->next;
			then->next = pre->next;
			pre->next = then;
			then = start->next;
		}
		head = preHead->next;
		delete preHead;
		return head;
	}
};

// 双指针迭代
class Solution2 {
public:
	ListNode * reverseBetween(ListNode *head, int left, int right) {
		if (!head) return nullptr;
		ListNode *dummy = new ListNode(-1);
		dummy->next = head;
		ListNode *preHead = dummy;
		right -= left;
		while (--left) preHead = preHead->next;

		ListNode *pre = preHead->next;
		ListNode *cur = pre->next;
		while (right--) {
			ListNode *post = cur->next;
			cur->next = pre;
			pre = cur;
			cur = post;
		}
		preHead->next->next = cur;
		preHead->next = pre;
		return dummy->next;
	}
};