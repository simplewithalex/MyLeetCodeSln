#include "header.h"

/*

请判断一个链表是否为回文链表。

示例 1:
输入: 1->2
输出: false

示例 2:
输入: 1->2->2->1
输出: true

进阶：
你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？

*/

class Solution {
public:
	bool isPalindrome(ListNode *head)
	{
		if (!head) return true;
		ListNode *slow = head, *fast = head, *pre = slow;
		while (fast&&fast->next)
		{
			pre = slow;
			slow = slow->next;
			fast = fast->next->next;
		}
		pre->next = nullptr;
		ListNode *sndHead = reverse(slow), *fstHead = head;
		while (fstHead)
		{
			if (fstHead->val != sndHead->val) return false;
			fstHead = fstHead->next;
			sndHead = sndHead->next;
		}
		return true;
	}
	ListNode *reverse(ListNode *head)
	{
		ListNode *pre = nullptr, *cur = head;
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