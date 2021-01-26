#include "header.h"

/*

ÿ�ε���ʱ���������������Ƴ�һ��Ԫ��,��ԭ�ؽ�����뵽���ź���������С�

*/

class Solution {
public:
	ListNode * insertionSortList(ListNode *head) {
		if (!head) return nullptr;
		ListNode *dummy = new ListNode(-1);//ʵ�����൱�ڴ���һ���µ�����ͷ���������ڵ����β��롣
		ListNode *pre = dummy;
		ListNode *cur = head;
		ListNode *next = nullptr;
		while (cur) {
			next = cur->next;
			if (pre->next&&pre->next->val > cur->val) pre = dummy;
			while (pre->next&&pre->next->val <= cur->val) pre = pre->next;
			cur->next = pre->next;
			pre->next = cur;
			cur = next;
		}
		return dummy->next;
	}
};