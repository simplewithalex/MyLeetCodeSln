#include "header.h"

/*

430. ��ƽ���༶˫������

���õ�һ��˫�������а����Ľڵ���һ����һ��ָ�롢һ��ǰһ��ָ���һ������� ��ָ�� �������ָ�����ָ��һ��������˫������Ҳ������Щ����Ľڵ�
��Щ���б������һ�������Լ������б��Դ����ƣ��������������ʾ����ʾ�� ������ݽṹ

���������ͷ�ڵ� head �������� ��ƽ�� ���Ա����нڵ㶼�����ڵ���˫������
�� curr ��һ���������б�Ľڵ㡣���б��еĽڵ�Ӧ�ó����ڱ�ƽ���б��е� curr ֮�� �� curr.next ֮ǰ

���� ��ƽ�б�� head���б��еĽڵ���뽫�� ���� ��ָ������Ϊ null 

ʾ�� 1��
���룺head = [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
�����[1,2,3,7,8,11,12,9,10,4,5,6]
���ͣ�����Ķ༶�б�����ͼ��ʾ
��ƽ�������������ͼ��

ʾ�� 2��
���룺head = [1,2,null,3]
�����[1,3,2]
���ͣ�����Ķ༶�б�����ͼ��ʾ
��ƽ�������������ͼ��

ʾ�� 3��
���룺head = []
�����[]
˵���������п��ܴ��ڿ��б�

��ʾ��
�ڵ���Ŀ������ 1000
1 <= Node.val <= 10^5

��α�ʾ���������еĶ༶����

�� ʾ�� 1 Ϊ����
1---2---3---4---5---6--NULL
        |
        7---8---9---10--NULL
            |
            11--12--NULL

���л����е�ÿһ��֮��
[1,2,3,4,5,6,null]
[7,8,9,10,null]
[11,12,null]

Ϊ�˽�ÿһ�������л���һ��������Ҫÿһ�������ֵΪ null ��Ԫ�أ��Ա�ʾû�нڵ����ӵ���һ�����ϼ��ڵ�
[1,2,3,4,5,6,null]
[null,null,7,8,9,10,null]
[null,11,12,null]

�ϲ��������л��������ȥ��ĩβ�� null
[1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]

*/


// Definition for a Node.
class Node {
public:
	int val;
	Node* prev;
	Node* next;
	Node* child;
};

// �ݹ�
class Solution1 {
public:
	Node* flatten(Node* head) {
		helper(head);
		return head;
	}
	Node* helper(Node* node) {
		Node* last = node;
		while (node) {
			if (!node->child) {
				last = node;
				node = node->next;
			} else {
				Node* tmp = node->next;
				Node* lastChild = helper(node->child);
				node->next = node->child;
				node->child->prev = node;
				node->child = nullptr;
				lastChild->next = tmp;
				if (tmp) tmp->prev = lastChild;
				last = lastChild;
				node = tmp;
			}
		}
		return last;
	}
};

// ����
class Solution2 {
public:
	Node* flatten(Node* head) {
		Node* node = head;
		while (node) {
			if (node->child) {
				Node* tmp = node->next;
				Node* child = node->child;
				node->next = child;
				child->prev = node;
				node->child = nullptr;
				Node* last = node;
				while (last->next) last = last->next;
				last->next = tmp;
				if (tmp) tmp->prev = last;
			}
			node = node->next;
		}
		return head;
	}
};

