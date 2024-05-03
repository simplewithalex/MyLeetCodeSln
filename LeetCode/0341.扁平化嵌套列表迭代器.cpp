#include "header.h"

/*

����һ��Ƕ�׵������б� nestedList
ÿ��Ԫ��Ҫô��һ��������Ҫô��һ���б����б��Ԫ��Ҳ���������������������б�
����ʵ��һ�������������ƽ����ʹ֮�ܹ���������б��е���������

ʵ�ֱ�ƽ�������� NestedIterator��
NestedIterator(List<NestedInteger> nestedList) ��Ƕ���б� nestedList ��ʼ��������
int next() ����Ƕ���б����һ������
boolean hasNext() �����Ȼ���ڴ����������������� true�����򣬷��� false

��Ĵ��뽫��������α�����⣺
initialize iterator with nestedList
res = []
while iterator.hasNext()
append iterator.next() to the end of res
return res
��� res ��Ԥ�ڵı�ƽ���б�ƥ�䣬��ô��Ĵ��뽫�ᱻ��Ϊ��ȷ

ʾ�� 1��
���룺nestedList = [[1,1],2,[1,1]]
�����[1,1,2,1,1]
���ͣ�ͨ���ظ����� next ֱ�� hasNext ���� false��next ���ص�Ԫ�ص�˳��Ӧ����: [1,1,2,1,1]

ʾ�� 2��
���룺nestedList = [1,[4,[6]]]
�����[1,4,6]
���ͣ�ͨ���ظ����� next ֱ�� hasNext ���� false��next ���ص�Ԫ�ص�˳��Ӧ����: [1,4,6]

��ʾ��
1 <= nestedList.length <= 500
Ƕ���б��е�����ֵ�ڷ�Χ [-10^6, 10^6] ��

*/



// This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation
class NestedInteger {
public:
	// Return true if this NestedInteger holds a single integer, rather than a
	// nested list.
	bool isInteger() const {};

	// Return the single integer that this NestedInteger holds, if it holds a
	// single integer The result is undefined if this NestedInteger holds a
	// nested list
	int getInteger() const {};

	// Return the nested list that this NestedInteger holds, if it holds a
	// nested list The result is undefined if this NestedInteger holds a single
	// integer
	const vector<NestedInteger> &getList() const {};
};

class NestedIterator1 {
private:
	vector<int> res;
	vector<int>::iterator it;

public:
	NestedIterator1(vector<NestedInteger> &nestedList) {
		dfs(nestedList);
		it = res.begin();
	}

	int next() { return *it++; }

	bool hasNext() { return it != res.end(); }

private:
	void dfs(const vector<NestedInteger> &nestedList) {
		for (const auto &v : nestedList) {
			if (v.isInteger()) res.push_back(v.getInteger());
			else dfs(v.getList());
		}
	}
};


class NestedIterator2 {
private:
	stack<NestedInteger> s;

public:
	NestedIterator2(vector<NestedInteger> &nestedList) {
		for (int i = nestedList.size() - 1; i >= 0; --i) s.push(nestedList[i]);
	}

	int next() {
		NestedInteger cur = s.top();
		s.pop();
		return cur.getInteger();
	}

	bool hasNext() {
		while (!s.empty()) {
			NestedInteger cur = s.top();
			if (cur.isInteger()) return true;
			s.pop();
			for (int i = cur.getList().size() - 1; i >= 0; --i) {
				s.push(cur.getList()[i]);
			}
		}
		return false;
	}
};

/**
* Your NestedIterator object will be instantiated and called as such:
* NestedIterator i(nestedList);
* while (i.hasNext()) cout << i.next();
*/

