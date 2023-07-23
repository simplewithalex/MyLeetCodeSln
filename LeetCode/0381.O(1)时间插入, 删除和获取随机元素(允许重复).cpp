#include "header.h"

/*

381. O(1) ʱ����롢ɾ���ͻ�ȡ���Ԫ�� - �����ظ�

RandomizedCollection ��һ�ְ������ּ���(�������ظ���)�����ݽṹ����Ӧ��֧�ֲ����ɾ���ض�Ԫ�أ��Լ�ɾ�����Ԫ�ء�

ʵ�� RandomizedCollection ��:
RandomizedCollection()��ʼ���յ� RandomizedCollection ����
bool insert(int val) ��һ�� val ����뵽�����У���ʹ�����Ѿ����ڡ����������ڣ��򷵻� true �����򷵻� false
bool remove(int val) ������ڣ��Ӽ������Ƴ�һ�� val ����������ڣ��򷵻� true�����򷵻� false��ע�⣬���val�ڼ����г��ֶ�Σ�����ֻɾ������һ��
int getRandom() �ӵ�ǰ�Ķ��Ԫ�ؼ����з���һ�����Ԫ�ء�ÿ��Ԫ�ر����صĸ����뼯���а�������ֵͬ�������������

������ʵ����ĺ�����ʹÿ�������� ƽ�� ʱ�临�Ӷ�Ϊ O(1)

ע�⣺���ɲ�������ʱ��ֻ���� RandomizedCollection ��������һ��ʱ���Ż���� getRandom

ʾ�� 1:
����
["RandomizedCollection", "insert", "insert", "insert", "getRandom", "remove", "getRandom"]
[[], [1], [1], [2], [], [1], []]
���
[null, true, false, true, 2, true, 1]
����
RandomizedCollection collection = new RandomizedCollection();// ��ʼ��һ���յļ���
collection.insert(1);   // ���� true����Ϊ���ϲ����� 1
// �� 1 ���뵽������
collection.insert(1);   // ���� false����Ϊ���ϰ��� 1
// ����һ�� 1 ���뵽�����С��������ڰ��� [1,1]
collection.insert(2);   // ���� true����Ϊ���ϲ����� 2
// �� 2 ���뵽�����С��������ڰ��� [1,1,2]
collection.getRandom(); // getRandom Ӧ��:
// �� 2/3 �ĸ��ʷ��� 1,
// 1/3 �ĸ��ʷ��� 2
collection.remove(1);   // ���� true����Ϊ���ϰ��� 1
// �Ӽ������Ƴ� 1���������ڰ��� [1,2]
collection.getRandom(); // getRandom Ӧ�÷��� 1 �� 2�����ߵĿ�������ͬ

��ʾ:
-2^31 <= val <= 2^31 - 1
insert, remove �� getRandom ����ܹ������� 2 * 10^5 ��
������ getRandom ʱ�����ݽṹ��������һ��Ԫ��

*/

class RandomizedCollection1 {
private:
	unordered_map<int, unordered_set<int>> idx;
	vector<int> nums;

public:
	RandomizedCollection1() {}

	bool insert(int val) {
		nums.push_back(val);
		idx[val].insert(nums.size() - 1);
		return idx[val].size() == 1;
	}

	bool remove(int val) {
		if (!idx.count(val)) return false;
		int i = *(idx[val].begin());
		nums[i] = nums.back();
		idx[val].erase(i);
		if (i < nums.size() - 1) {
			idx[nums[i]].erase(nums.size() - 1);
			idx[nums[i]].insert(i);
		}
		if (idx[val].empty()) idx.erase(val);
		nums.pop_back();
		return true;
	}

	int getRandom() { return nums[rand() % nums.size()]; }
};

/**
* Your RandomizedCollection object will be instantiated and called as such:
* RandomizedCollection* obj = new RandomizedCollection();
* bool param_1 = obj->insert(val);
* bool param_2 = obj->remove(val);
* int param_3 = obj->getRandom();
*/

// ʹ�� C++ unordered_multimap
class RandomizedCollection2 {
private:
	unordered_multimap<int, int> idx;
	vector<unordered_multimap<int, int>::iterator> nums;

public:
	RandomizedCollection2() {}

	bool insert(int val) {
		bool ret = !idx.count(val);
		nums.push_back(idx.insert({ val, nums.size() }));
		return ret;
	}

	bool remove(int val) {
		auto it = idx.find(val);
		if (it == idx.end()) return false;
		nums.back()->second = it->second;
		nums[it->second] = nums.back();
		nums.pop_back();
		idx.erase(it);
		return true;
	}

	int getRandom() { return nums[rand() % nums.size()]->first; }
};
// https://leetcode.cn/problems/insert-delete-getrandom-o1-duplicates-allowed/solutions/467892/c-unordered_multimapjie-fa-by-vclip/
// https://leetcode.cn/u/vclip/

/**
* Your RandomizedCollection object will be instantiated and called as such:
* RandomizedCollection* obj = new RandomizedCollection();
* bool param_1 = obj->insert(val);
* bool param_2 = obj->remove(val);
* int param_3 = obj->getRandom();
*/

