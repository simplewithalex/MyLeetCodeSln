#include "header.h"

/*

284. ���˵�����

���������һ�����������ڼ������е�����ӵ�е� hasNext �� next �����Ļ����ϣ�������֧�� peek ����

ʵ�� PeekingIterator �ࣺ
PeekingIterator(Iterator<int> nums) ʹ��ָ������������ nums ��ʼ��������
int next() ���������е���һ��Ԫ�أ�����ָ���ƶ����¸�Ԫ�ش�
bool hasNext() ��������д�����һ��Ԫ�أ����� true�����򣬷��� false
int peek() ���������е���һ��Ԫ�أ������ƶ�ָ��
ע�⣺ÿ�����Կ����в�ͬ�Ĺ��캯���͵����� Iterator������֧�� int next() �� boolean hasNext() ����

ʾ�� 1��
���룺
["PeekingIterator", "next", "peek", "next", "next", "hasNext"]
[[[1, 2, 3]], [], [], [], [], []]
�����
[null, 1, 2, 2, 3, false]
���ͣ�
PeekingIterator peekingIterator = new PeekingIterator([1, 2, 3]); // [1,2,3]
peekingIterator.next();    // ���� 1 ��ָ���ƶ�����һ��Ԫ�� [1,2,3]
peekingIterator.peek();    // ���� 2 ��ָ��δ�����ƶ� [1,2,3]
peekingIterator.next();    // ���� 2 ��ָ���ƶ�����һ��Ԫ�� [1,2,3]
peekingIterator.next();    // ���� 3 ��ָ���ƶ�����һ��Ԫ�� [1,2,3]
peekingIterator.hasNext(); // ���� False

��ʾ��
1 <= nums.length <= 1000
1 <= nums[i] <= 1000
�� next �� peek �ĵ��þ���Ч
next��hasNext �� peek ������  1000 ��

���ף��㽫�����չ�����ƣ�ʹ֮���ͨ�û����Ӷ���Ӧ���е����ͣ�����ֻ�������ͣ�

*/

/*
* Below is the interface for Iterator, which is already defined for you.
* **DO NOT** modify the interface for Iterator.
*/
class Iterator {
	struct Data;
	Data *data;

public:
	Iterator(const vector<int> &nums) {}
	Iterator(const Iterator &iter) {}

	// Returns the next element in the iteration.
	int next() {}

	// Returns true if the iteration has more elements.
	bool hasNext() const {}
};

class PeekingIterator : public Iterator {
private:
	int val = 0;
	bool exist = false;

public:
	PeekingIterator(const vector<int> &nums) : Iterator(nums) {
		// Initialize any member here.
		// **DO NOT** save a copy of nums and manipulate it directly.
		// You should only use the Iterator interface methods.
		exist = Iterator::hasNext();
		if (exist) val = Iterator::next();
	}

	// Returns the next element in the iteration without advancing the iterator.
	int peek() { return val; }

	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
		int tmp = val;
		exist = Iterator::hasNext();
		if (exist) val = Iterator::next();
		return tmp;
	}

	bool hasNext() const { return exist; }
};
