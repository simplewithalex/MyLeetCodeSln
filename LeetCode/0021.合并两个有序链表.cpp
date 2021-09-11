#include "header.h"

/*

将两个升序链表合并为一个新的升序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

示例 1：
输入：l1 = [1,2,4], l2 = [1,3,4]
输出：[1,1,2,3,4,4]
 
示例 2：
输入：l1 = [], l2 = []
输出：[]
 
示例 3：
输入：l1 = [], l2 = [0]
输出：[0]
  
提示：
两个链表的节点数目范围是 [0, 50]
-100 <= Node.val <= 100
l1 和 l2 均按非递减顺序排列

*/

// 迭代法
class Solution1 {
public:
	ListNode * mergeTwoLists(ListNode *l1, ListNode *l2) {
		if (!l1) return l2;
		if (!l2) return l1;
		ListNode *dummy = new ListNode(-1);
		ListNode *p1 = l1;
		ListNode *p2 = l2;
		ListNode *pre = dummy;
		while (p1&&p2) {
			if (p1->val <= p2->val) {
				pre->next = p1;
				p1 = p1->next;
			}
			else {
				pre->next = p2;
				p2 = p2->next;
			}
			pre = pre->next;
		}
		if (p1) pre->next = p1;
		else pre->next = p2;
		p1 = dummy->next;
		delete dummy;
		return p1;
	}
};

// 递归法
class Solution2 {
public:
	ListNode * mergeTwoLists(ListNode *l1, ListNode *l2) {
		if (!l1) return l2;
		if (!l2) return l1;
		ListNode *pMergedHead = nullptr;
		if (l1->val <= l2->val) {
			pMergedHead = l1;
			pMergedHead->next = mergeTwoLists(l1->next, l2);
		}
		else {
			pMergedHead = l2;
			pMergedHead->next = mergeTwoLists(l1, l2->next);
		}
		return pMergedHead;
	}
};
