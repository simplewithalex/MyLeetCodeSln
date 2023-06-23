#include "header.h"

/*

1206. 设计跳表

不使用任何库函数，设计一个跳表

跳表 是在 O(log(n)) 时间内完成增加、删除、搜索操作的数据结构
跳表相比于树堆与红黑树，其功能与性能相当，并且跳表的代码长度相较下更短，其设计思想与链表相似
跳表中有很多层，每一层是一个短的链表。在第一层的作用下，增加、删除和搜索操作的时间复杂度不超过 O(n)。跳表的每一个操作的平均时间复杂度是 O(log(n))，空间复杂度是 O(n)
了解更多 : https://en.wikipedia.org/wiki/Skip_list

在本题中，你的设计应该要包含这些函数：
bool search(int target): 返回target是否存在于跳表中。
void add(int num): 插入一个元素到跳表。
bool erase(int num): 在跳表中删除一个值，如果 num 不存在，直接返回false. 如果存在多个 num，删除其中任意一个即可。
注意，跳表中可能存在多个相同的值，你的代码需要处理这种情况。

示例 1:
输入
["Skiplist", "add", "add", "add", "search", "add", "search", "erase", "erase", "search"]
[[], [1], [2], [3], [0], [4], [1], [0], [1], [1]]
输出
[null, null, null, null, false, null, true, false, true, false]
解释
Skiplist skiplist = new Skiplist();
skiplist.add(1);
skiplist.add(2);
skiplist.add(3);
skiplist.search(0);   // 返回 false
skiplist.add(4);
skiplist.search(1);   // 返回 true
skiplist.erase(0);    // 返回 false，0 不在跳表中
skiplist.erase(1);    // 返回 true
skiplist.search(1);   // 返回 false，1 已被擦除

提示:
0 <= num, target <= 2 * 10^4
调用search, add, erase操作次数不大于 5 * 10^4


*/

#define level 10

struct Node {
	int val;
	vector<Node *> next{ level, nullptr };
	Node(int _val) : val(_val) {}
};

class Skiplist {
private:
	Node *head = nullptr;
	void find(int target, vector<Node *> &pre) {
		Node *cur = head;
		for (int i = level - 1; i >= 0; --i) {
			while (cur->next[i] && cur->next[i]->val < target) cur = cur->next[i];
			pre[i] = cur;
		}
	}

public:
	Skiplist() { head = new Node(-1); }

	~Skiplist() {
		delete head;
		head = nullptr;
	}

	bool search(int target) {
		vector<Node *> pre{ level, nullptr };
		find(target, pre);
		return pre[0]->next[0] && pre[0]->next[0]->val == target;
	}

	void add(int num) {
		vector<Node *> pre{ level, nullptr };
		find(num, pre);
		Node *p = new Node(num);
		for (int i = 0; i < level; ++i) {
			// 每个节点构建level层的next节点指针
			// 针对每层进行链表插入操作
			p->next[i] = pre[i]->next[i];
			pre[i]->next[i] = p;
			// 每层有50%概率不插入新节点
			if (rand() & 1) break;
		}
	}

	bool erase(int num) {
		vector<Node *> pre{ level, nullptr };
		find(num, pre);
		Node *p = pre[0]->next[0];
		if (!p || p->val != num) return false;
		for (int i = 0; i < level && pre[i]->next[i] == p; ++i) {
			pre[i]->next[i] = p->next[i];
		}
		delete p;
		return true;
	}
};

/**
* Your Skiplist object will be instantiated and called as such:
* Skiplist* obj = new Skiplist();
* bool param_1 = obj->search(target);
* obj->add(num);
* bool param_3 = obj->erase(num);
*/

// https://leetcode.cn/problems/design-skiplist/solutions/1699167/by-tonngw-ls2k/
// https://leetcode.cn/u/tonngw/
