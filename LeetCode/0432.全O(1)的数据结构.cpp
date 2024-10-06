#include "header.h"

/*

432. ȫ O(1) �����ݽṹ

�������һ�����ڴ洢�ַ������������ݽṹ�����ܹ����ؼ�����С�������ַ���

ʵ�� AllOne �ࣺ
AllOne() ��ʼ�����ݽṹ�Ķ���
inc(String key) �ַ��� key �ļ������� 1 ��������ݽṹ���в����� key ����ô�������Ϊ 1 �� key
dec(String key) �ַ��� key �ļ������� 1 ����� key �ļ����ڼ��ٺ�Ϊ 0 ����ô��Ҫ����� key �����ݽṹ��ɾ��������������֤���ڼ��ټ���ǰ��key ���������ݽṹ��
getMaxKey() ��������һ�����������ַ��������û��Ԫ�ش��ڣ�����һ�����ַ��� ""
getMinKey() ��������һ��������С���ַ��������û��Ԫ�ش��ڣ�����һ�����ַ��� ""

ע�⣺ÿ��������Ӧ������ O(1) ƽ��ʱ�临�Ӷ�

ʾ����
����
["AllOne", "inc", "inc", "getMaxKey", "getMinKey", "inc", "getMaxKey", "getMinKey"]
[[], ["hello"], ["hello"], [], [], ["leet"], [], []]
���
[null, null, null, "hello", "hello", null, "hello", "leet"]
����
AllOne allOne = new AllOne();
allOne.inc("hello");
allOne.inc("hello");
allOne.getMaxKey(); // ���� "hello"
allOne.getMinKey(); // ���� "hello"
allOne.inc("leet");
allOne.getMaxKey(); // ���� "hello"
allOne.getMinKey(); // ���� "leet"


��ʾ��
1 <= key.length <= 10
key ��СдӢ����ĸ���
����������֤����ÿ�ε��� dec ʱ�����ݽṹ���ܴ��� key
������ inc��dec��getMaxKey �� getMinKey ���� 5 * 10^4 ��

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


