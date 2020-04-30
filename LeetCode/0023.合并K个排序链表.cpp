#include "header.h"

/*

合并 k 个排序链表，返回合并后的排序链表。请分析和描述算法的复杂度。

示例:
输入:
[
  1->4->5,
  1->3->4,
  2->6
]
输出: 1->1->2->3->4->4->5->6

*/

class Solution {
public:
	ListNode * mergeKLists(vector<ListNode *> &lists)
	{
		priority_queue<ListNode *, vector<ListNode *>, decltype(compare)*> pq(compare);
		ListNode *dummy = new ListNode(-1);
		ListNode *cur = dummy;
		for (auto node : lists)
		{
			if (node)
				pq.push(node);
		}
		while (!pq.empty())
		{
			cur->next = pq.top();
			pq.pop();
			cur = cur->next;
			if (cur->next)
			{
				pq.push(cur->next);
			}
		}
		ListNode *head = dummy->next;
		delete dummy;
		return head;

	}
	static bool compare(ListNode *node1, ListNode *node2)
	{
		return node1->val > node2->val;
	}
};