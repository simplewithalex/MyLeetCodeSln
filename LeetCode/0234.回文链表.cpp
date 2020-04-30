#include "header.h"

/*

���ж�һ�������Ƿ�Ϊ��������

ʾ�� 1:
����: 1->2
���: false

ʾ�� 2:
����: 1->2->2->1
���: true

���ף�
���ܷ��� O(n) ʱ�临�ӶȺ� O(1) �ռ临�ӶȽ�����⣿

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