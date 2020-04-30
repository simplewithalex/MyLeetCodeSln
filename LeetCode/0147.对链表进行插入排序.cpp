#include "header.h"

/*

ÿ�ε���ʱ���������������Ƴ�һ��Ԫ��,��ԭ�ؽ�����뵽���ź���������С�

*/

class Solution {
public:
	ListNode * insertionSortList(ListNode *head)
	{
		if (!head)
			return nullptr;
		ListNode *ahead = new ListNode(-1);//ʵ�����൱�ڴ���һ���µ�����ͷ���������ڵ����β��롣
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