#include "header.h"

/*

给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random ，该指针可以指向链表中的任何节点或空节点。

构造这个链表的 深拷贝。 深拷贝应该正好由n个全新节点组成，其中每个新节点的值都设为其对应的原节点的值。

新节点的 next 指针和 random 指针也都应指向复制链表中的新节点，并使原链表和复制链表中的这些指针能够表示相同的链表状态。复制链表中的指针都不应指向原链表中的节点 。

例如，如果原链表中有 X 和 Y 两个节点，其中 X.random --> Y 。那么在复制链表中对应的两个节点 x 和 y ，同样有 x.random --> y 。

返回复制链表的头节点。

random随机指针指向的节点索引（范围从 0 到 n-1），如果不指向任何节点，则为null 

你的代码只接受原链表的头节点 head 作为传入参数。

示例 1：
输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]

示例 2：
输入：head = [[1,1],[2,1]]
输出：[[1,1],[2,1]]

示例 3：
输入：head = [[3,null],[3,0],[3,null]]
输出：[[3,null],[3,0],[3,null]]

示例 4：
输入：head = []
输出：[]
解释：给定的链表为空（空指针），因此返回 null
  
提示：
0 <= n <= 1000
-10000 <= Node.val <= 10000
Node.random 为空（null）或指向链表中的节点

*/

class Node {
public:
	int val;
	Node *next;
	Node *random;

	Node(int _val) {
		val = _val;
		next = NULL;
		random = NULL;
	}
};

// 原地复制
class Solution1 {
public:
	Node * copyRandomList(Node *head) {
		if (!head) return nullptr;
		Node *node = head;
		Node *copyNode = nullptr;
		while (node) {
			copyNode = new Node(node->val);
			copyNode->next = node->next;
			node->next = copyNode;
			node = copyNode->next;
		}
		node = head;
		copyNode = node->next;
		while (node) {
			if (node->random) copyNode->random = node->random->next;
			node = copyNode->next;
			if (node) copyNode = node->next;
		}
		node = head;
		copyNode = node->next;
		Node *copyHead = copyNode;
		while (node) {
			node->next = copyNode->next;
			node = node->next;
			if (node) copyNode->next = node->next;
			copyNode = copyNode->next;
		}
		return copyHead;
	}
};

// 哈希
class Solution2 {
public:
	Node * copyRandomList(Node *head) {
		if (!head) return nullptr;
		unordered_map<Node *, Node *> m;
		Node *node = head;
		while (node) {
			Node *copyNode = new Node(node->val);
			m[node] = copyNode;
			node = node->next;
		}
		node = head;
		while (node) {
			m[node]->next = m[node->next];
			m[node]->random = m[node->random];
			node = node->next;
		}
		return m[head];
	}
};