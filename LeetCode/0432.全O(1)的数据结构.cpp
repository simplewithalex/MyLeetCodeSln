#include "header.h"

/*

432. 全 O(1) 的数据结构

请你设计一个用于存储字符串计数的数据结构，并能够返回计数最小和最大的字符串

实现 AllOne 类：
AllOne() 初始化数据结构的对象
inc(String key) 字符串 key 的计数增加 1 。如果数据结构中尚不存在 key ，那么插入计数为 1 的 key
dec(String key) 字符串 key 的计数减少 1 。如果 key 的计数在减少后为 0 ，那么需要将这个 key 从数据结构中删除。测试用例保证：在减少计数前，key 存在于数据结构中
getMaxKey() 返回任意一个计数最大的字符串。如果没有元素存在，返回一个空字符串 ""
getMinKey() 返回任意一个计数最小的字符串。如果没有元素存在，返回一个空字符串 ""

注意：每个函数都应当满足 O(1) 平均时间复杂度

示例：
输入
["AllOne", "inc", "inc", "getMaxKey", "getMinKey", "inc", "getMaxKey", "getMinKey"]
[[], ["hello"], ["hello"], [], [], ["leet"], [], []]
输出
[null, null, null, "hello", "hello", null, "hello", "leet"]
解释
AllOne allOne = new AllOne();
allOne.inc("hello");
allOne.inc("hello");
allOne.getMaxKey(); // 返回 "hello"
allOne.getMinKey(); // 返回 "hello"
allOne.inc("leet");
allOne.getMaxKey(); // 返回 "hello"
allOne.getMinKey(); // 返回 "leet"


提示：
1 <= key.length <= 10
key 由小写英文字母组成
测试用例保证：在每次调用 dec 时，数据结构中总存在 key
最多调用 inc、dec、getMaxKey 和 getMinKey 方法 5 * 10^4 次

*/


struct Node {
	unordered_set<string> keys;
	int cnt;
	Node *pre;
	Node *next;
	Node() : pre(nullptr), next(nullptr) {}
};

class AllOne {
public:
	unordered_map<string, Node *> map;
	Node *head;
	Node *tail;
	AllOne() {
		head = new Node();
		head->cnt = -1;
		tail = new Node();
		tail->cnt = INT_MAX;
		head->next = tail;
		tail->pre = head;
	}

	void inc(string key) {
		if (map.count(key)) {
			Node *node = map[key];
			node->keys.erase(key);
			int cnt = node->cnt;
			Node *next = nullptr;
			if (node->next->cnt == cnt + 1) {
				next = node->next;
			} else {
				next = new Node();
				next->cnt = cnt + 1;
				add(node, next);
			}
			next->keys.insert(key);
			map[key] = next;
			del(node);
		} else {
			Node *next = nullptr;
			if (head->next->cnt == 1) {
				next = head->next;
			} else {
				next = new Node();
				next->cnt = 1;
				add(head, next);
			}
			next->keys.insert(key);
			map[key] = next;
		}
	}

	void dec(string key) {
		Node *node = map[key];
		node->keys.erase(key);
		int cnt = node->cnt;
		if (cnt == 1) {
			map.erase(key);
		} else {
			Node *pre = nullptr;
			if (node->pre->cnt == cnt - 1) {
				pre = node->pre;
			} else {
				pre = new Node();
				pre->cnt = cnt - 1;
				add(node->pre, pre);
			}
			pre->keys.insert(key);
			map[key] = pre;
		}
		del(node);
	}

	string getMaxKey() {
		Node *node = tail->pre;
		for (string str : node->keys) return str;
		return "";
	}

	string getMinKey() {
		Node *node = head->next;
		for (string str : node->keys) return str;
		return "";
	}

private:
	void add(Node *last, Node *node) {
		node->next = last->next;
		node->pre = last;
		last->next = node;
		node->next->pre = node;
	}

	void del(Node *node) {
		if (node->keys.size() == 0) {
			node->pre->next = node->next;
			node->next->pre = node->pre;
			delete node;
		}
	}
};

/**
* Your AllOne object will be instantiated and called as such:
* AllOne* obj = new AllOne();
* obj->inc(key);
* obj->dec(key);
* string param_3 = obj->getMaxKey();
* string param_4 = obj->getMinKey();
*/


