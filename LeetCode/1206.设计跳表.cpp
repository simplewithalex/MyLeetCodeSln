#include "header.h"

/*

1206. �������

��ʹ���κο⺯�������һ������

���� ���� O(log(n)) ʱ����������ӡ�ɾ�����������������ݽṹ
����������������������书���������൱����������Ĵ��볤������¸��̣������˼������������
�������кܶ�㣬ÿһ����һ���̵������ڵ�һ��������£����ӡ�ɾ��������������ʱ�临�ӶȲ����� O(n)�������ÿһ��������ƽ��ʱ�临�Ӷ��� O(log(n))���ռ临�Ӷ��� O(n)
�˽���� : https://en.wikipedia.org/wiki/Skip_list

�ڱ����У�������Ӧ��Ҫ������Щ������
bool search(int target): ����target�Ƿ�����������С�
void add(int num): ����һ��Ԫ�ص�����
bool erase(int num): ��������ɾ��һ��ֵ����� num �����ڣ�ֱ�ӷ���false. ������ڶ�� num��ɾ����������һ�����ɡ�
ע�⣬�����п��ܴ��ڶ����ͬ��ֵ����Ĵ�����Ҫ�������������

ʾ�� 1:
����
["Skiplist", "add", "add", "add", "search", "add", "search", "erase", "erase", "search"]
[[], [1], [2], [3], [0], [4], [1], [0], [1], [1]]
���
[null, null, null, null, false, null, true, false, true, false]
����
Skiplist skiplist = new Skiplist();
skiplist.add(1);
skiplist.add(2);
skiplist.add(3);
skiplist.search(0);   // ���� false
skiplist.add(4);
skiplist.search(1);   // ���� true
skiplist.erase(0);    // ���� false��0 ����������
skiplist.erase(1);    // ���� true
skiplist.search(1);   // ���� false��1 �ѱ�����

��ʾ:
0 <= num, target <= 2 * 10^4
����search, add, erase�������������� 5 * 10^4


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
			// ÿ���ڵ㹹��level���next�ڵ�ָ��
			// ���ÿ���������������
			p->next[i] = pre[i]->next[i];
			pre[i]->next[i] = p;
			// ÿ����50%���ʲ������½ڵ�
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
