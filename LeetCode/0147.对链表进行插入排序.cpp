#include "header.h"

/*

每次迭代时，从输入数据中移除一个元素,并原地将其插入到已排好序的链表中。

*/

class Solution {
public:
	ListNode * insertionSortList(ListNode *head)
	{
		if (!head)
			return nullptr;
		ListNode *ahead = new ListNode(-1);//实际上相当于创建一个新的链表头，将后续节点依次插入。
		ListNode *cur = head;
		ListNode *pre = ahead;
		ListNode *next = nullptr;
		while (cur)
		{
			next = cur->next;
			if (!pre || !pre->next || pre->next->val > cur->val)
				pre = ahead;
			while (pre->next&&pre->next->val <= cur->val)
			{
				pre = pre->next;
			}
			cur->next = pre->next;
			pre->next = cur;
			cur = next;
		}
		return ahead->next;
	}
};